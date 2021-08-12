#include"DATABASE_INCLUDE.h"
#include"hv/hv.h"
#include"APIAccess.h"
#include"APIRouter.h"
#include"hv/HttpServer.h"
using namespace hv;
pthread_mutex_t REP_INUSE;
pthread_mutex_t EMAIL_INUSE;
ContactWithGroup* _Rep;
pthread_t PID_ER;
pthread_t PID_PR;
http_server_t   g_http_server;
HttpService     g_http_service;

void SIGupdateEmail(){
  FILE* EM=fopen("newMail.txt","r");
  char _TIME[32];
  char _RECEIVER[128];
  char _CONTEXT[2048];
  fgets(_TIME,32,EM);
  fgets(_RECEIVER,128,EM);
  fgets(_CONTEXT,2048,EM);
  fclose(EM);
  FILE* CLEAR_EM=fopen("newMail.txt","w");
  fclose(CLEAR_EM);
  _Rep->updateEmail(_RECEIVER,atoi(_TIME),_CONTEXT);
  _Rep->PrioritySort();
}

void Signal_Handler(int SIG){
  if(SIG==SIGINT){
    #ifdef DEBUG
      printf("==MAIN== Received Signal [SIGINT], Terminating ALL PS\n");
    #endif
    printf("==EZCT== Sending Signal [SIGTERM] to ALL Background Processes...\n");
    kill(PID_ER,SIGTERM);
    kill(PID_PR,SIGTERM);
    http_server_stop(&g_http_server);
    printf("==EZCT== Saving ALL Contact Information to Local Hard Drive...\n");
    printf("==EZCT== ALL Termination Tasks Successfully Finished, Exiting Easy Contact.\n");
    exit(EXIT_FAILURE);
  }
  if(SIG==SIGUSR1){
    #ifdef DEBUG
      printf("==MAIN== Received Signal [SIGUSR1], Just Received New Email\n");
    #endif
    pthread_mutex_lock(&EMAIL_INUSE);
    {
      SIGupdateEmail();
    }
    pthread_mutex_unlock(&EMAIL_INUSE);
  }
  if(SIG==SIGUSR2){
    #ifdef DEBUG
      printf("==MAIN== Received Signal [SIGUSR2], DataBase Just Sorted\n");
    #endif
  }
}

int main(int numArgs,char** Argv){
  BYPASSUNUSED(Argv);
  if(numArgs!=1) { return EXIT_FAILURE; }
  signal(SIGINT,SIG_IGN);
  REP_INUSE=PTHREAD_MUTEX_INITIALIZER;
  EMAIL_INUSE=PTHREAD_MUTEX_INITIALIZER;
  #ifdef DEBUG
    setvbuf(stdout,NULL,_IONBF,0);
    printf("==MAIN== PS<DB_MAIN> Running In [DEBUG] Mode\n");
  #endif
  #ifdef PRESENT
    printf("==MAIN== PS<DB_MAIN> Running In [PRESENTATION] Mode\n");
  #endif
  printf("==EZCT== Restoring Contact Information From Local Hard Drive...\n");
  printf("==EZCT== Easy Contact BackEnd DataBase is Now Running...\n");
  printf("==EZCT== To Terminate, Press \"Ctrl+C\"\n");
  _Rep=(ContactWithGroup*)malloc(sizeof(ContactWithGroup));
  pthread_create(&PID_ER,0,StartEmailReader,_Rep);
  pthread_create(&PID_PR,0,StartPrioritySort,_Rep);

  g_http_server.port = 3001;
  g_http_service.base_url = "";
  APIRouter::register_router(g_http_service);
  g_http_server.service = &g_http_service;
  http_server_run(&g_http_server, 0);

  signal(SIGUSR1,Signal_Handler);
  signal(SIGUSR2,Signal_Handler);
  signal(SIGINT,Signal_Handler);
  // *_Rep=DB_Import("ECDB.txt").extract();
  while(1){ sleep(10); }
  return EXIT_SUCCESS;
}
