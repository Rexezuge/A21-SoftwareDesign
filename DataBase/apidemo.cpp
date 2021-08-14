#include"DATABASE_INCLUDE.h"

#include"hv/HttpServer.h"

#include "APIAccess.h"
#include "APIRouter.h"

pthread_mutex_t REP_INUSE;
ContactWithGroup* _Rep;
http_server_t   g_http_server;
HttpService     g_http_service;

int main() {
    REP_INUSE=PTHREAD_MUTEX_INITIALIZER;
    _Rep=(ContactWithGroup*)malloc(sizeof(ContactWithGroup));
    g_http_server.port = 3001;
    g_http_service.base_url = "";
    APIRouter::register_router(g_http_service);
    g_http_server.service = &g_http_service;
    http_server_run(&g_http_server);

    return EXIT_SUCCESS;
}
