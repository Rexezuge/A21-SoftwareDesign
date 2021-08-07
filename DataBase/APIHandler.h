#include"DATABASE_INCLUDE.h"

class APIServer {
    http_server_t   g_http_server;
    HttpService     g_http_service;
    public:
    void run() {
        // Start basic configuration
        g_http_server.port = 3001;
        g_http_service.base_url = "localhost";
        APIRouter::register_router(g_http_service);
        g_http_server.service = &g_http_service;
        http_server_run(&g_http_server);
    }
};
