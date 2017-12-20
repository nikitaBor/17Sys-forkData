#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

int main() {
  // Handle interruption signals
  signal(SIGINT, sighandler);
  
  while(1){
    int fdWKP = server_setup();

    int child = fork();
    if(child == 0){
      /* Child process as subserver */
      subserver(fdWKP);
      exit(0);
    } else {
      /* Parent needs not do anything */
    }
  }
  return 0;
}

void subserver(int from_client) {

  /* Subserver handshake handled */
  int to_client = server_connect(from_client);  

  /* Subserver operation */
  char response[256];
  while(read(from_client, response, sizeof(response))){    
    process(response); // CURRENTLY DOES NOTHING
    write(to_client, response, sizeof(response));
    printf("[subserver %d] Sent modified text\n", getpid());
  }
}

void process(char *s) {
  s = s;
}
