#include"DATABASE_INCLUDE.h"

class APIRouter {
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
                return 400;

            // Set response type
            resp->content_type = APPLICATION_JSON;

            if (contactName == "NULL") {
                // Specify the group, and give a list of contacts
                std::vector<Contact> tmp = getGroup(groupName);
                for (int i = 0; i < tmp.size(); i++)
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
                std::vector<std::string> q = getContact(contactName);
                if (q[0] == "NULL")  return 404;
                resp->json["name"] = q[0];
                resp->json["phone"] = q[1];
                resp->json["email"] = q[2];
                resp->json["mostRecent"] = q[3];
                resp->json["received"] = q[4];
            }

            return 200;
        });
        /**
         * POST /contacts/:groupName/:contactName
         * Create a new contact.  Queries should contain a data payload
         * `application/json` with phone (int) and email (str).
         */
        router.POST("/contacts/:groupName/:contactName", [](HttpRequest* req, HttpResponse* resp) {
            // Check the request content type
            if (req->content_type != APPLICATION_JSON)  return 400;
            // Parse the query
            std::string groupName = req->GetParam("groupName");
            std::string contactName = req->GetParam("contactName");

            // Parse the data payload
            int phone = req->GetInt("phone");
            std::string email = req->GetString("email");

            // Error checking
            if (groupName == "" || contactName == "")  return 400;

            // Check a group's existence
            std::vector<std::string> currentGrps = getGroups();
            for (int i = 0; i < currentGrps.size(); i++) {
                if (currentGrps[i] == groupName)  break;
                if (i == currentGrps.size() - 1)  return 406;
            }

            // Insert the contact into the group
            Contact insert(contactName, phone, email);
            if (!addContact(groupName, insert))  return 410;

            return 201;
        });
        /**
         * PUT /contacts/:groupName/:contactName
         * Modify a contact.  Same requirement as above.
         */
        router.PUT("/contacts/:groupName/:contactName", [](HttpRequest* req, HttpResponse* resp) {
            // Check the request type and parse the query
            if (req->content_type != APPLICATION_JSON)  return 400;
            std::string groupName = req->GetParam("groupName");
            std::string contactName = req->GetParam("contactName");

            int phone = req->GetInt("phone");
            std::string email = req->GetString("email");

            if (groupName == "" || contactName == "")  return 400;

            std::vector<std::string> currentGrps = getGroups();
            for (int i = 0; i < currentGrps.size(); i++) {
                if (currentGrps[i] == groupName)  break;
                if (i == currentGrps.size() - 1)  return 406;
            }

            // Check the contact's existence
            std::vector<Contact> tmp = getGroup(groupName);
            for (int i = 0; i < tmp.size(); i++) {
                if (tmp[i].getName() == contactName)  break;
                if (i == tmp.size() - 1)              return 404;
            }

            // Create new contact object,
            // remove from and add to the original group.
            Contact insert(contactName, phone, email);
            if (!removeContact(contactName))     return 500;
            if (!addContact(groupName, insert))  return 410;

            return 200;
        });
        /**
         * DELETE /contacts/:groupName/:contactName
         * Delete a contact, in any group.
         */
        router.Delete("/contacts/:groupName/:contactName", [](HttpRequest* req, HttpResponse* resp) {
            std::string contactName = req->GetParam("contactName");
            if (contactName == "")            return 400;
            if (!removeContact(contactName))  return 404;
            return 200;
        });

        /**
         * GET /groups
         * Get all groups' order and name.
         */
        router.GET("/groups/:groupName/:contactName/:newGroupName", [](HttpRequest* req, HttpResponse* resp) {
            resp->content_type = APPLICATION_JSON;
            std::vector<std::string> groups = getGroups();
            for (int i = 0; i < groups.size(); i++) {
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
        router.POST("/groups/:groupName/:contactName/:newGroupName", [](HttpRequest* req, HttpResponse* resp) {
            if (req->content_type != APPLICATION_JSON)  return 400;
            std::string groupName = req->GetParam("groupName");

            std::string topContact = req->GetString("top");

            if (groupName == "")       return 400;
            if (!addGroup(groupName))  return 410;

            // Check always top
            if (topContact != "")
                if (!AlwaysTop(groupName, topContact))  return 500;

            return 201;
        });
        /**
         * PUT /groups/:groupName
         * Modify a group.
         */
        router.PUT("/groups/:groupName/:contactName/:newGroupName", [](HttpRequest* req, HttpResponse* resp) {
            if (req->content_type != APPLICATION_JSON)  return 400;
            std::string groupName = req->GetParam("groupName");

            std::string topContact = req->GetString("top");

            if (groupName == "")  return 400;

            if (topContact != "") {
                if (!CancelTop(groupName))              return 500;
                if (!AlwaysTop(groupName, topContact))  return 500;
            }

            return 200;
        });
        /**
         * PATCH /groups/:groupName/:contactName/:newGroupName
         * Move a contact from the group to a new group.
         */
        router.PATCH("/groups/:groupName/:contactName/:newGroupName", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("groupName");
            std::string contactName = req->GetParam("contactName");
            std::string newGroupName = req->GetParam("newGroupName");

            if (groupName == newGroupName)        return 400;

            // Check this group's existence
            std::vector<std::string> currentGrps = getGroups();
            for (int i = 0; i < currentGrps.size(); i++) {
                if (currentGrps[i] == groupName)  break;
                if (i == currentGrps.size() - 1)  return 406;
            }

            // Check the new group's existence
            std::vector<std::string> newGrps = getGroups();
            for (int i = 0; i < newGrps.size(); i++) {
                if (newGrps[i] == newGroupName)   break;
                if (i == newGrps.size() - 1)      return 406;
            }

            // Check the current contact's existence
            std::vector<Contact> currentCntcts = getGroup(currentGrps);
            for (int i = 0; i < currentCntcts.size(); i++) {
                if (currentCntcts[i].getName() == contactName)  break;
                if (i == currentCntcts.size() - 1)              return 406;
            }

            // Create new object
            Contact ready = getContact(contactName);
            if (ready.getName() == "NULL")          return 404;

            // Delete, then add to the new group
            if (!removeContact(contactName))        return 500;
            Contact insert(ready.getName(), ready.getPhone(), ready.getAddress());
            insert._Weight = ready._Weight;
            if (!addContact(newGroupName, insert))  return 500;

            return 200;
        });
    }
};
