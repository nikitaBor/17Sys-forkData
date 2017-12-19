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
  while(1){
    int fdWKP = server_setup();
    int childPID = fork();
    if(childPID == 0){//child
      subserver(fdWKP);
      return 0;
    }
  }
  return 0;
}

void subserver(int from_client) {
}

void process(char * s) {
}
