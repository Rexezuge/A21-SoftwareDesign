#ifndef SDD_EASYCONTACT_APIROUTER
#define SDD_EASYCONTACT_APIROUTER

#include "DATABASE_INCLUDE.h"
#include "hv/HttpService.h"

class APIRouter {
   public:
    static int pre(HttpRequest* req, HttpResponse* resp) {
        resp->content_type = APPLICATION_JSON;
        req->ParseBody();
        printf("==APIS== Received from %s:%d\n", req->client_addr.ip.c_str(),
               req->client_addr.port);
#if DEBUG
        printf("==APIS== %s\n", req->Dump(true, true).c_str());
#endif
        printf("==APIS== %s", req->Dump(false, false).c_str());
        return 0;
    };

    static int post(HttpRequest* req, HttpResponse* resp) {
        BYPASSUNUSED(req);
        printf("==APIS== Returned %d\n", resp->status_code);
        return 0;
    };

    static void register_router(HttpService& router) {
        router.preprocessor = pre;
        router.postprocessor = post;
        router.GET("/contacts/:groupName",
                   [](HttpRequest* req, HttpResponse* resp) {
                       // Parse the query URL
                       std::string groupName = req->GetParam("groupName");

                       // Error check
                       if (groupName == "" || groupName == "NULL") return 400;

                       // Specify the group, and give a list of contacts
                       std::vector<Contact> tmp = getGroup(groupName);
                       for (int i = 0; i < (int)tmp.size(); i++)
                           resp->json.push_back(
                               {{"id", i},
                                {"name", tmp[i].getName()},
                                {"phone", tmp[i].getPhone()},
                                {"email", tmp[i].getAddress()},
                                {"mostRecent", tmp[i]._Weight.getMail()},
                                {"received", tmp[i]._Weight.getLatestTime()}});

                       return 200;
                   });
        /**
         * GET /contacts/:groupName/:contactName
         * Get the specific contact, or a list of contacts in one group
         * with order.
         */
        router.GET("/contacts/:groupName/:contactName", [](HttpRequest* req,
                                                           HttpResponse* resp) {
            // Parse the query URL
            std::string groupName = req->GetParam("groupName");
            std::string contactName = req->GetParam("contactName");

            // Error check
            if (groupName == "" || contactName == "" || groupName == "NULL")
                return 400;

            std::vector<Contact> currentCntcts = getGroup(groupName);
            if (currentCntcts.size() == 0) return 404;
            for (int i = 0; i < (int)currentCntcts.size(); i++) {
                if (currentCntcts[i].getName() == contactName) break;
                if (i == (int)currentCntcts.size() - 1) return 404;
            }

            // Retrieve the specific contact
            Contact* q = getContact(contactName);
            if (q == nullptr) return 404;
            resp->json["name"] = q->getName();
            resp->json["phone"] = q->getPhone();
            resp->json["email"] = q->getAddress();
            resp->json["mostRecent"] = q->_Weight.getMail();
            resp->json["received"] = q->_Weight.getLatestTime();

            return 200;
        });
        /**
         * POST /contacts/:groupName/:contactName
         * Create a new contact.  Queries should contain a data payload
         * `application/json` with phone (int) and email (str).
         */
        router.POST("/contacts/:groupName/:contactName",
                    [](HttpRequest* req, HttpResponse* resp) {
                        // Check the request content type
                        if (req->content_type != APPLICATION_JSON) return 400;
                        // Parse the query
                        std::string groupName = req->GetParam("groupName");
                        std::string contactName = req->GetParam("contactName");

                        // Parse the data payload
                        int phone = req->Get<int64_t>("phone");
                        std::string email = req->GetString("email");

                        // Error checking
                        if (groupName == "" || contactName == "") return 400;

                        // Check a group's existence
                        std::vector<std::string> currentGrps = getGroups();
                        if (currentGrps.size() == 0) return 406;
                        for (int i = 0; i < (int)currentGrps.size(); i++) {
                            if (currentGrps[i] == groupName) break;
                            if (i == (int)currentGrps.size() - 1) return 406;
                        }

                        // Insert the contact into the group
                        Contact insert(contactName, phone, email);
                        if (!addContact(groupName, insert)) return 410;
                        resp->json["msg"] = "Created";
                        return 201;
                    });
        /**
         * PUT /contacts/:groupName/:contactName
         * Modify a contact.  Same requirement as above.
         */
        router.PUT("/contacts/:groupName/:contactName",
                   [](HttpRequest* req, HttpResponse* resp) {
                       // Check the request type and parse the query
                       if (req->content_type != APPLICATION_JSON) return 400;
                       std::string groupName = req->GetParam("groupName");
                       std::string contactName = req->GetParam("contactName");

                       int phone = req->Get<int64_t>("phone");
                       std::string email = req->GetString("email");

                       if (groupName == "" || contactName == "") return 400;

                       std::vector<std::string> currentGrps = getGroups();
                       if (currentGrps.size() == 0) return 406;
                       for (int i = 0; i < (int)currentGrps.size(); i++) {
                           if (currentGrps[i] == groupName) break;
                           if (i == (int)currentGrps.size() - 1) return 406;
                       }

                       // Check the contact's existence
                       std::vector<Contact> tmp = getGroup(groupName);
                       if (tmp.size() == 0) return 404;
                       for (int i = 0; i < (int)tmp.size(); i++) {
                           if (tmp[i].getName() == contactName) break;
                           if (i == (int)tmp.size() - 1) return 404;
                       }

                       // Create new contact object,
                       // remove from and add to the original group.
                       Contact insert(contactName, phone, email);
                       if (!removeContact(contactName)) return 500;
                       if (!addContact(groupName, insert)) return 410;
                       resp->json["msg"] = "OK";
                       return 200;
                   });
        /**
         * DELETE /contacts/:groupName/:contactName
         * Delete a contact, in any group.
         */
        router.Delete("/contacts/:groupName/:contactName",
                      [](HttpRequest* req, HttpResponse* resp) {
                          std::string contactName =
                              req->GetParam("contactName");
                          if (contactName == "") return 400;
                          if (!removeContact(contactName)) return 404;
                          resp->json["msg"] = "OK";
                          return 200;
                      });

        /**
         * GET /groups
         * Get all groups' order and name.
         */
        router.GET("/groups", [](HttpRequest* req, HttpResponse* resp) {
            BYPASSUNUSED(req);
            std::vector<std::string> groups = getGroups();
            for (int i = 0; i < (int)groups.size(); i++) {
                std::string group = groups[i];
                resp->json.push_back({
                    {"id", i},
                    {"name", group},
                });
            }
            return 200;
        });
        /**
         * POST /groups/:groupName
         * Create a new group.
         */
        router.POST("/groups/:groupName",
                    [](HttpRequest* req, HttpResponse* resp) {
                        std::string groupName = req->GetParam("groupName");
                        if (groupName == "") return 400;
                        if (!addGroup(groupName)) return 410;
                        resp->json["msg"] = "Created";
                        return 201;
                    });
        /**
         * PATCH /groups/:groupName/:contactName/:newGroupName
         * Move a contact from the group to a new group.
         */
        router.PATCH(
            "/groups/:groupName/:contactName/:newGroupName",
            [](HttpRequest* req, HttpResponse* resp) {
                std::string groupName = req->GetParam("groupName");
                std::string contactName = req->GetParam("contactName");
                std::string newGroupName = req->GetParam("newGroupName");

                if (groupName == newGroupName) return 400;

                // Check this group's existence
                std::vector<std::string> currentGrps = getGroups();
                if (currentGrps.size() == 0) return 406;
                for (int i = 0; i < (int)currentGrps.size(); i++) {
                    if (currentGrps[i] == groupName) break;
                    if (i == (int)currentGrps.size() - 1) return 406;
                }

                // Check the new group's existence
                std::vector<std::string> newGrps = getGroups();
                if (newGrps.size() == 0) return 406;
                for (int i = 0; i < (int)newGrps.size(); i++) {
                    if (newGrps[i] == newGroupName) break;
                    if (i == (int)newGrps.size() - 1) return 406;
                }

                // Check the current contact's existence
                std::vector<Contact> currentCntcts = getGroup(groupName);
                if (currentCntcts.size() == 0) return 406;
                for (int i = 0; i < (int)currentCntcts.size(); i++) {
                    if (currentCntcts[i].getName() == contactName) break;
                    if (i == (int)currentCntcts.size() - 1) return 406;
                }

                // Create new object
                Contact* ready = getContact(contactName);
                if (ready->getName() == "NULL") return 404;

                // Delete, then add to the new group
                if (!removeContact(contactName)) return 500;
                Contact insert(ready->getName(), ready->getPhone(),
                               ready->getAddress());
                insert._Weight = ready->_Weight;
                if (!addContact(newGroupName, insert)) return 500;
                resp->json["msg"] = "OK";
                return 200;
            });

        router.POST("/tops/:group", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("group");

            if (groupName == "" || groupName == "NULL") return 400;

            // Check if topped already
            if (hasAlwaysTop()) return 403;
            // Check this group's existence
            std::vector<std::string> currentGrps = getGroups();
            if (currentGrps.size() == 0) return 404;
            for (int i = 0; i < (int)currentGrps.size(); i++) {
                if (currentGrps[i] == groupName) break;
                if (i == (int)currentGrps.size() - 1) return 404;
            }
            AlwaysTop(groupName);

            resp->json["msg"] = "Created";
            return 201;
        });
        router.POST(
            "/tops/:group/:contact", [](HttpRequest* req, HttpResponse* resp) {
                std::string groupName = req->GetParam("group");
                std::string contactName = req->GetParam("contact");

                if (groupName == "" || groupName == "NULL") return 400;

                if (hasAlwaysTop(groupName)) return 403;
                // Check this group's existence
                std::vector<std::string> currentGrps = getGroups();
                if (currentGrps.size() == 0) return 404;
                for (int i = 0; i < (int)currentGrps.size(); i++) {
                    if (currentGrps[i] == groupName) break;
                    if (i == (int)currentGrps.size() - 1) return 404;
                }
                // Check the current contact's existence
                std::vector<Contact> currentCntcts = getGroup(groupName);
                if (currentCntcts.size() == 0) return 404;
                for (int i = 0; i < (int)currentCntcts.size(); i++) {
                    if (currentCntcts[i].getName() == contactName) break;
                    if (i == (int)currentCntcts.size() - 1) return 404;
                }
                AlwaysTop(groupName, contactName);

                resp->json["msg"] = "Created";
                return 201;
            });

        router.PUT("/tops/:group/:contact",
                   [](HttpRequest* req, HttpResponse* resp) {
                       std::string groupName = req->GetParam("group");
                       std::string contactName = req->GetParam("contact");

                       if (groupName == "" || groupName == "NULL") return 400;
                       // Check this group's existence
                       std::vector<std::string> currentGrps = getGroups();
                       if (currentGrps.size() == 0) return 404;
                       for (int i = 0; i < (int)currentGrps.size(); i++) {
                           if (currentGrps[i] == groupName) break;
                           if (i == (int)currentGrps.size() - 1) return 404;
                       }
                       // Check the current contact's existence
                       std::vector<Contact> currentCntcts = getGroup(groupName);
                       if (currentCntcts.size() == 0) return 406;
                       for (int i = 0; i < (int)currentCntcts.size(); i++) {
                           if (currentCntcts[i].getName() == contactName) break;
                           if (i == (int)currentCntcts.size() - 1) return 404;
                       }
                       CancelTop(groupName);
                       AlwaysTop(groupName, contactName);

                       resp->json["msg"] = "OK";
                       return 200;
                   });
        router.PUT("/tops/:group", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("group");

            if (groupName == "" || groupName == "NULL") return 400;

            // Check this group's existence
            std::vector<std::string> currentGrps = getGroups();
            if (currentGrps.size() == 0) return 404;
            for (int i = 0; i < (int)currentGrps.size(); i++) {
                if (currentGrps[i] == groupName) break;
                if (i == (int)currentGrps.size() - 1) return 404;
            }
            CancelTop();
            AlwaysTop(groupName);
            resp->json["msg"] = "OK";
            return 200;
        });
        router.Delete("/tops/:group",
                      [](HttpRequest* req, HttpResponse* resp) {
                          std::string groupName = req->GetParam("group");

                          if (groupName == "" || groupName == "NULL")
                              return 400;

                          // Check this group's existence
                          std::vector<std::string> currentGrps = getGroups();
                          if (currentGrps.size() == 0) return 404;
                          for (int i = 0; i < (int)currentGrps.size(); i++) {
                              if (currentGrps[i] == groupName) break;
                              if (i == (int)currentGrps.size() - 1) return 404;
                          }
                          CancelTop(groupName);

                          resp->json["msg"] = "OK";
                          return 200;
                      });
        router.Delete("/tops", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("group");

            if (groupName == "" || groupName == "NULL") return 400;

            CancelTop();

            resp->json["msg"] = "OK";
            return 200;
        });
    }
};

#endif
