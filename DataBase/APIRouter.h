#ifndef SDD_EASYCONTACT_API_ROUTER
#define SDD_EASYCONTACT_API_ROUTER

#include "hv/HttpService.h"

class APIRouter {
    public:
    static void register_router(HttpService& router) {
        router.GET("/contacts", [](HttpRequest* req, HttpResponse* resp) {
            return 200;
        });
        router.POST("/contacts", [](HttpRequest* req, HttpResponse* resp) {
            return 201;
        });
        router.PUT("/contacts", [](HttpRequest* req, HttpResponse* resp) {
            return 200;
        });

        router.GET("/groups", [](HttpRequest* req, HttpResponse* resp) {
            return 200;
        });
        router.POST("/groups", [](HttpRequest* req, HttpResponse* resp) {
            return 201;
        });
        router.PUT("/groups", [](HttpRequest* req, HttpResponse* resp) {
            return 200;
        });
        router.PATCH("/groups", [](HttpRequest* req, HttpResponse* resp) {
            return 200;
        });
    }
};

#endif
