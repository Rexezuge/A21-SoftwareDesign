#include "DATABASE_INCLUDE.h"
#define _EMAILTIMER 5
extern pthread_mutex_t REP_INUSE;
extern pthread_mutex_t EMAIL_INUSE;

int NoNewEmail(FILE* FP) {
    fseek(FP, 0, SEEK_END);
    if (!ftell(FP)) {
        return 1;
    }
    fseek(FP, 0, SEEK_SET);
    return 0;
}

void ER_SignalMain() { kill(getpid(), SIGUSR1); }

int ReadLocalEmail() {
    FILE* EM = fopen("newMail.txt", "r");
    if (NoNewEmail(EM)) {
        fclose(EM);
        return EXIT_SUCCESS;
    }
    char _TIME[32];
    char _RECEIVER[128];
    char _CONTEXT[2048];
    fgets(_TIME, 32, EM);
    _TIME[strlen(_TIME) - 1] = 0;
    fgets(_RECEIVER, 128, EM);
    _RECEIVER[strlen(_RECEIVER) - 1] = 0;
    fgets(_CONTEXT, 2048, EM);
    _CONTEXT[strlen(_CONTEXT) - 1] = 0;
#ifdef DEBUG
    printf("==EMRD== Received New Email\n");
    printf("==EMRD== _TIME\n%s\n", _TIME);
    printf("==EMRD== _RECEIVER\n%s\n", _RECEIVER);
    printf("==EMRD== _CONTEXT\n%s\n", _CONTEXT);
#endif
    fclose(EM);
    ER_SignalMain();
    return EXIT_SUCCESS;
}

void* StartEmailReader(void* ARGV) {
    BYPASSUNUSED(ARGV);
    pthread_detach(pthread_self());
#ifdef DEBUG
    printf("==EMRD== PTHREAD<EmailReader> Running In [DEBUG] Mode\n");
#endif
    while (1) {
        pthread_mutex_lock(&REP_INUSE);
        {
            pthread_mutex_lock(&EMAIL_INUSE);
            { ReadLocalEmail(); }
            pthread_mutex_unlock(&EMAIL_INUSE);
        }
        pthread_mutex_unlock(&REP_INUSE);
#ifdef DEBUG
        sleep(_EMAILTIMER * 10);
#else
        sleep(_EMAILTIMER * 60);
#endif
    }
    return EXIT_SUCCESS;
}
