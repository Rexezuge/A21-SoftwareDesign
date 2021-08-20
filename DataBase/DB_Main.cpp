#include "DATABASE_INCLUDE.h"
#include "APIAccess.h"
#include "APIRouter.h"
#include "hv/HttpServer.h"
#include "hv/hv.h"
using namespace hv;
// mutex lock for contact book vector
pthread_mutex_t REP_INUSE;
// mutex lock for email representation
pthread_mutex_t EMAIL_INUSE;
// pointer to the contact book representation
ContactWithGroup* _REP;
// email reader pid
pthread_t PID_ER;
// sorting program pid
pthread_t PID_PR;
// API http server
http_server_t g_http_server;
// API http services (routes) of the http server
HttpService g_http_service;

/**
 * Email updater
 *
 * It reads the `newMail.txt` to extract new email for different users.
 */
void SIGupdateEmail() {
    FILE* EM = fopen("newMail.txt", "r");
    char _TIME[32];
    char _RECEIVER[128];
    char _CONTEXT[2048];
    fgets(_TIME, 32, EM);
    _TIME[strlen(_TIME) - 1] = 0;
    fgets(_RECEIVER, 128, EM);
    _RECEIVER[strlen(_RECEIVER) - 1] = 0;
    fgets(_CONTEXT, 2048, EM);
    _CONTEXT[strlen(_CONTEXT) - 1] = 0;
    fclose(EM);
    FILE* CLEAR_EM = fopen("newMail.txt", "w");
    fclose(CLEAR_EM);
    pthread_mutex_lock(&REP_INUSE);
    {
        _REP->updateEmail(_RECEIVER, atoi(_TIME), _CONTEXT);
        _REP->PrioritySort();
    }
    pthread_mutex_unlock(&REP_INUSE);
}

/**
 * Handles the signals.
 *
 * SIGINT: stop all the services and exit
 * SIGUSR1: update emails
 * SIGUSR2: sort the database contacts
 *
 * @param SIG Signal ID
 */
void Signal_Handler(int SIG) {
    if (SIG == SIGINT) {
#ifdef DEBUG
        printf("==MAIN== Received Signal [SIGINT], Terminating ALL PS\n");
#endif
        printf(
            "==EZCT== Sending Signal [SIGTERM] to ALL Background "
            "Processes...\n");
        kill(PID_ER, SIGTERM);
        kill(PID_PR, SIGTERM);
        http_server_stop(&g_http_server);
        printf(
            "==EZCT== Saving ALL Contact Information to Local Hard Drive...\n");
        printf(
            "==EZCT== ALL Termination Tasks Successfully Finished, Exiting "
            "Easy "
            "Contact.\n");
        exit(EXIT_FAILURE);
    }
    if (SIG == SIGUSR1) {
#ifdef DEBUG
        printf("==MAIN== Received Signal [SIGUSR1], Just Received New Email\n");
#endif
        pthread_mutex_lock(&EMAIL_INUSE);
        { SIGupdateEmail(); }
        pthread_mutex_unlock(&EMAIL_INUSE);
    }
    if (SIG == SIGUSR2) {
#ifdef DEBUG
        printf("==MAIN== Received Signal [SIGUSR2], DataBase Just Sorted\n");
#endif
    }
}

int main(int numArgs, char** Argv) {
    BYPASSUNUSED(Argv);
    if (numArgs != 1) {
        return EXIT_FAILURE;
    }
    // ignore signals for initializing
    signal(SIGINT, SIG_IGN);
    signal(SIGUSR1, SIG_IGN);
    signal(SIGUSR2, SIG_IGN);
    // pthread mutex init
    REP_INUSE = PTHREAD_MUTEX_INITIALIZER;
    EMAIL_INUSE = PTHREAD_MUTEX_INITIALIZER;
#ifdef DEBUG
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("==MAIN== PS<DB_MAIN> Running In [DEBUG] Mode\n");
#endif
    printf("==EZCT== Restoring Contact Information From Local Hard Drive...\n");
    _REP = DB_Import("ECDB.csv").extract();
    Import_Email_From_Local("ECDB_EM.csv", _REP);
    printf("==EZCT== Easy Contact BackEnd DataBase is Now Running...\n");
    printf("==EZCT== To Terminate, Press \"Ctrl+C\"\n");
    // create email reader thread
    pthread_create(&PID_ER, 0, StartEmailReader, _REP);
    // create priority sort thread
    pthread_create(&PID_PR, 0, StartPrioritySort, _REP);
    // configure the API HTTP server
    g_http_server.port = 3001;
    g_http_service.base_url = "";
    // register all API RESTful routes
    APIRouter::register_router(g_http_service);
    g_http_server.service = &g_http_service;
    // start HTTP server without blocking
    http_server_run(&g_http_server, 0);
    // register the signals
    signal(SIGUSR1, Signal_Handler);
    signal(SIGUSR2, Signal_Handler);
    signal(SIGINT, Signal_Handler);

    while (1) {
        pause();
    }

    return EXIT_SUCCESS;
}
