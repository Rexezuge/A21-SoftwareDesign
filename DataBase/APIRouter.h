#ifndef SDD_EASYCONTACT_APIROUTER
#define SDD_EASYCONTACT_APIROUTER

#include"DATABASE_INCLUDE.h"

class APIRouter {
    private:
    static int response_status(HttpResponse* resp, int code = 200, const char* message = NULL) {
        resp->Set("code", code);
        if (message == NULL) message = http_status_str((enum http_status)code);
        resp->Set("message", message);
        resp->DumpBody();
        return code;
    }

    public:
    static void register_router(HttpService& router) {
        /**
         * GET /contacts/:groupName/:contactName
         * Get the specific contact, or a list of contacts in one group
         * with order.
         */
        router.GET("/contacts/:groupName/:contactName", [](HttpRequest* req, HttpResponse* resp) {
            // Parse the query URL
            std::string groupName = req->GetParam("groupName");
            std::string contactName = req->GetParam("contactName");

            // Error check
            if (groupName == "" || contactName == "" || groupName == "NULL")
                return response_status(resp, 400, "Bad Request");

            // Set response type
            resp->content_type = APPLICATION_JSON;

            if (contactName == "NULL") {
                // Specify the group, and give a list of contacts
                std::vector<Contact> tmp = getGroup(groupName);
                for (int i = 0; i < (int) tmp.size(); i++)
                    resp->json.push_back({
                        {"id", i},
                        {"name", tmp[i].getName()},
                        {"phone", tmp[i].getPhone()},
                        {"email", tmp[i].getAddress()},
                        {"mostRecent", tmp[i]._Weight.getMail()},
                        {"received", tmp[i]._Weight.getLatestTime()}
                    });
            } else {
                // Retrieve the specific contact
                Contact q = getContact(contactName);
                if (q.getName() == "NULL")  return 404;
                resp->json["name"] = q.getName();
                resp->json["phone"] = q.getPhone();
                resp->json["email"] = q.getAddress();
                resp->json["mostRecent"] = q._Weight.getMail();
                resp->json["received"] = q._Weight.getLatestTime();
            }

            return response_status(resp, 200, "OK");
        });
        /**
         * POST /contacts/:groupName/:contactName
         * Create a new contact.  Queries should contain a data payload
         * `application/json` with phone (int) and email (str).
         */
        router.POST("/contacts/:groupName/:contactName", [](HttpRequest* req, HttpResponse* resp) {
            // Check the request content type
            if (req->content_type != APPLICATION_JSON)
                return response_status(resp, 400, "Bad Request");
            // Parse the query
            std::string groupName = req->GetParam("groupName");
            std::string contactName = req->GetParam("contactName");

            // Parse the data payload
            int phone = req->GetInt("phone");
            std::string email = req->GetString("email");

            // Error checking
            if (groupName == "" || contactName == "")
                return response_status(resp, 400, "Bad Request");

            // Check a group's existence
            std::vector<std::string> currentGrps = getGroups();
            for (int i = 0; i < (int) currentGrps.size(); i++) {
                if (currentGrps[i] == groupName)        break;
                if (i == (int) currentGrps.size() - 1)
                    return response_status(resp, 406, "Not Acceptable");
            }

            // Insert the contact into the group
            Contact insert(contactName, phone, email);
            if (!addContact(groupName, insert))
                return response_status(resp, 410, "Conflict");

            return response_status(resp, 201, "Created");
        });
        /**
         * PUT /contacts/:groupName/:contactName
         * Modify a contact.  Same requirement as above.
         */
        router.PUT("/contacts/:groupName/:contactName", [](HttpRequest* req, HttpResponse* resp) {
            // Check the request type and parse the query
            if (req->content_type != APPLICATION_JSON)
                return response_status(resp, 400, "Bad Request");
            std::string groupName = req->GetParam("groupName");
            std::string contactName = req->GetParam("contactName");

            int phone = req->GetInt("phone");
            std::string email = req->GetString("email");

            if (groupName == "" || contactName == "")
                return response_status(resp, 400, "Bad Request");

            std::vector<std::string> currentGrps = getGroups();
            for (int i = 0; i < (int) currentGrps.size(); i++) {
                if (currentGrps[i] == groupName)        break;
                if (i == (int) currentGrps.size() - 1)
                    return response_status(resp, 406, "Not Acceptable");
            }

            // Check the contact's existence
            std::vector<Contact> tmp = getGroup(groupName);
            for (int i = 0; i < (int) tmp.size(); i++) {
                if (tmp[i].getName() == contactName)  break;
                if (i == (int) tmp.size() - 1)
                    return response_status(resp, 404, "Not Found");
            }

            // Create new contact object,
            // remove from and add to the original group.
            Contact insert(contactName, phone, email);
            if (!removeContact(contactName))
                return response_status(resp, 500, "Internal Error");
            if (!addContact(groupName, insert))
                return response_status(resp, 410, "Conflict");

            return response_status(resp, 200, "OK");
        });
        /**
         * DELETE /contacts/:groupName/:contactName
         * Delete a contact, in any group.
         */
        router.Delete("/contacts/:groupName/:contactName", [](HttpRequest* req, HttpResponse* resp) {
            std::string contactName = req->GetParam("contactName");
            if (contactName == "")
                return response_status(resp, 400, "Bad Request");
            if (!removeContact(contactName))
                return response_status(resp, 404, "Not Found");
            return response_status(resp, 200, "OK");
        });

        /**
         * GET /groups
         * Get all groups' order and name.
         */
        router.GET("/groups/:groupName/:contactName/:newGroupName", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("groupName");
            resp->content_type = APPLICATION_JSON;
            std::vector<std::string> groups = getGroups();
            for (int i = 0; i < (int) groups.size(); i++) {
                std::string group = groups[i];
                resp->json.push_back({
                    {"id", i},
                    {"name", group},
                });
            }
            return response_status(resp, 200, "OK");
        });
        /**
         * POST /groups/:groupName
         * Create a new group.
         */
        router.POST("/groups/:groupName/:contactName/:newGroupName", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("groupName");

            if (groupName == "")
                return response_status(resp, 400, "Bad Request");
            if (!addGroup(groupName))
                return response_status(resp, 410, "Conflict");

            return response_status(resp, 201, "Created");
        });
        /**
         * PATCH /groups/:groupName/:contactName/:newGroupName
         * Move a contact from the group to a new group.
         */
        router.PATCH("/groups/:groupName/:contactName/:newGroupName", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("groupName");
            std::string contactName = req->GetParam("contactName");
            std::string newGroupName = req->GetParam("newGroupName");

            if (groupName == newGroupName)
                return response_status(resp, 400, "Bad Request");

            // Check this group's existence
            std::vector<std::string> currentGrps = getGroups();
            for (int i = 0; i < (int) currentGrps.size(); i++) {
                if (currentGrps[i] == groupName)        break;
                if (i == (int) currentGrps.size() - 1)
                    return response_status(resp, 406, "Not Acceptable");
            }

            // Check the new group's existence
            std::vector<std::string> newGrps = getGroups();
            for (int i = 0; i < (int) newGrps.size(); i++) {
                if (newGrps[i] == newGroupName)         break;
                if (i == (int) newGrps.size() - 1)
                    return response_status(resp, 406, "Not Acceptable");
            }

            // Check the current contact's existence
            std::vector<Contact> currentCntcts = getGroup(groupName);
            for (int i = 0; i < (int) currentCntcts.size(); i++) {
                if (currentCntcts[i].getName() == contactName)  break;
                if (i == (int) currentCntcts.size() - 1)
                    return response_status(resp, 406, "Not Acceptable");
            }

            // Create new object
            Contact ready = getContact(contactName);
            if (ready.getName() == "NULL")
                return response_status(resp, 404, "Not Found");

            // Delete, then add to the new group
            if (!removeContact(contactName))
                return response_status(resp, 500, "Internal Error");
            Contact insert(ready.getName(), ready.getPhone(), ready.getAddress());
            insert._Weight = ready._Weight;
            if (!addContact(newGroupName, insert))
                return response_status(resp, 500, "Internal Error");

            return response_status(resp, 200, "OK");
        });

        router.POST("/tops/:group/:contact", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("group");
            std::string contactName = req->GetParam("contact");

            if (groupName == "" || groupName == "NULL")
                return response_status(resp, 400, "Bad Request");

            if (contactName == "") {
                // Check if topped already
                if (hasAlwaysTop())
                    return response_status(resp, 403, "Forbidden");
                // Check this group's existence
                std::vector<std::string> currentGrps = getGroups();
                for (int i = 0; i < (int) currentGrps.size(); i++) {
                    if (currentGrps[i] == groupName)        break;
                    if (i == (int) currentGrps.size() - 1)
                        return response_status(resp, 404, "Not Found");
                }
                AlwaysTop(groupName);
            } else {
                if (hasAlwaysTop(groupName))
                    return response_status(resp, 403, "Forbidden");
                // Check this group's existence
                std::vector<std::string> currentGrps = getGroups();
                for (int i = 0; i < (int) currentGrps.size(); i++) {
                    if (currentGrps[i] == groupName)        break;
                    if (i == (int) currentGrps.size() - 1)
                        return response_status(resp, 404, "Not Found");
                }
                // Check the current contact's existence
                std::vector<Contact> currentCntcts = getGroup(groupName);
                for (int i = 0; i < (int) currentCntcts.size(); i++) {
                    if (currentCntcts[i].getName() == contactName)  break;
                    if (i == (int) currentCntcts.size() - 1)
                        return response_status(resp, 404, "Not Found");
                }
                AlwaysTop(groupName, contactName);
            }

            return response_status(resp, 201, "Created");
        });
        router.PUT("/tops/:group/:contact", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("group");
            std::string contactName = req->GetParam("contact");

            if (groupName == "" || groupName == "NULL")
                return response_status(resp, 400, "Bad Request");

            if (contactName == "") {
                // Check this group's existence
                std::vector<std::string> currentGrps = getGroups();
                for (int i = 0; i < (int) currentGrps.size(); i++) {
                    if (currentGrps[i] == groupName)  break;
                    if (i == (int) currentGrps.size() - 1)
                        return response_status(resp, 404, "Not Found");
                }
                CancelTop();
                AlwaysTop(groupName);
            } else {
                // Check this group's existence
                std::vector<std::string> currentGrps = getGroups();
                for (int i = 0; i < (int) currentGrps.size(); i++) {
                    if (currentGrps[i] == groupName)        break;
                    if (i == (int) currentGrps.size() - 1)
                        return response_status(resp, 404, "Not Found");
                }
                // Check the current contact's existence
                std::vector<Contact> currentCntcts = getGroup(groupName);
                for (int i = 0; i < (int) currentCntcts.size(); i++) {
                    if (currentCntcts[i].getName() == contactName)  break;
                    if (i == (int) currentCntcts.size() - 1)
                        return response_status(resp, 404, "Not Found");
                }
                CancelTop(groupName);
                AlwaysTop(groupName, contactName);
            }

            return response_status(resp, 200, "OK");
        });
        router.Delete("/tops/:group/:contact", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("group");
            std::string contactName = req->GetParam("contact");

            if (groupName == "" || groupName == "NULL")
                return response_status(resp, 400, "Bad Request");

            if (contactName == "") {
                CancelTop();
            } else {
                // Check this group's existence
                std::vector<std::string> currentGrps = getGroups();
                for (int i = 0; i < (int) currentGrps.size(); i++) {
                    if (currentGrps[i] == groupName)        break;
                    if (i == (int) currentGrps.size() - 1)
                        return response_status(resp, 404, "Not Found");
                }
                CancelTop(groupName);
            }

            return response_status(resp, 200, "OK");
        });
    }
};

#endif
