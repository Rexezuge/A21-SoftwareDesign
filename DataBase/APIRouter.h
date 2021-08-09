#ifndef SDD_EASYCONTACT_API_ROUTER
#define SDD_EASYCONTACT_API_ROUTER

#include <string>

#include "APIAccess.h"
#include "Contact.h"
#include "libhv/HttpService.h"

class APIRouter {
    public:
    static void register_router(HttpService& router) {
        router.GET("/contacts/:groupName/:contactName", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("groupName");
            std::string contactName = req->GetParam("contactName");

            if (groupName == "" || contactName == "")  return 400;

            resp->content_type = APPLICATION_JSON;

            if (groupName == "NULL") {

            } else if (contactName == "NULL") {
                std::list<Contact> tmp = getGroup(groupName);

            } else {
                std::vector<std::string> q = getContact(contactName);
                if (q[0] == "NULL")  return 404;
                resp->json["name"] = q[0];
                resp->json["phone"] = q[1];
                resp->json["email"] = q[2];
                resp->json["mostRecent"];
                resp->json["received"];
            }

            return 200;
        });
        router.POST("/contacts/:groupName/:contactName", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("groupName");
            std::string contactName = req->GetParam("contactName");
            return 201;
        });
        router.PUT("/contacts/:groupName/:contactName", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("groupName");
            std::string contactName = req->GetParam("contactName");
            return 200;
        });

        router.GET("/groups/:groupName/:contactName/:newGroupName", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("groupName");
            resp->content_type = APPLICATION_JSON;
            std::vector<std::string> groups = getGroups();
            for (int i = 0; i < groups.size(); i++) {
                std::string group = groups[i];
                resp->json.push_back(group);
            }
            return 200;
        });
        router.POST("/groups/:groupName/:contactName/:newGroupName", [](HttpRequest* req, HttpResponse* resp) {
            if (req->content_type != APPLICATION_JSON)  return 400;
            std::string groupName = req->GetParam("groupName");

            std::string topContact = req->GetString("topContact");
            std::string topGroup = req->GetString("topGroup");

            if (groupName == "")       return 400;
            if (!addGroup(groupName))  return 410;



            return 201;
        });
        router.PUT("/groups/:groupName/:contactName/:newGroupName", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("groupName");

            return 200;
        });
        router.PATCH("/groups/:groupName/:contactName/:newGroupName", [](HttpRequest* req, HttpResponse* resp) {
            std::string groupName = req->GetParam("groupName");
            std::string contactName = req->GetParam("contactName");
            std::string newGroupName = req->GetParam("newGroupName");
            return 200;
        });
    }
};

#endif
