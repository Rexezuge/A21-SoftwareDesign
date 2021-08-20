#include "DATABASE_INCLUDE.h"
#define _SLEEPTIMER 10
extern pthread_mutex_t REP_INUSE;

/**
 * Signal handler for priority sort
 */
void PR_SignalMain() { kill(getpid(), SIGUSR2); }

/**
 * Sort the database
 */
int UpdateDatabase(ContactWithGroup* DB) {
#ifdef DEBUG
    printf("==PRST== Now Sorting the DataBase\n");
#endif
    DB->PrioritySort();
    PR_SignalMain();
    return EXIT_SUCCESS;
}

/**
 * Main entrypoint for priority sort, will loop to sort DB in a time period
 */
void* StartPrioritySort(void* ARGV) {
    ContactWithGroup* DB = (ContactWithGroup*)ARGV;
    pthread_detach(pthread_self());
#ifdef DEBUG
    printf("==PRST== PTHREAD<PrioritySort> Running In [DEBUG] Mode\n");
#endif
    while (1) {
        pthread_mutex_lock(&REP_INUSE);
        { UpdateDatabase(DB); }
        pthread_mutex_unlock(&REP_INUSE);
#ifdef DEBUG
        sleep(_SLEEPTIMER * 10);
#else
        sleep(_SLEEPTIMER * 60);
#endif
    }
    return EXIT_SUCCESS;
}
