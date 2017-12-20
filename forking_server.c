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

      // Close well known pipe
      close(fdWKP);      
    }
  }

  return 0;
}

void subserver(int from_client) {

  /* Subserver handshake handled */
  int to_client = server_connect(from_client);  

  /* Subserver operation */
  char response[BUFFER_SIZE];  
  
  while(read(from_client, response, BUFFER_SIZE)){
    process(response);
    write(to_client, response, BUFFER_SIZE);
    printf("[subserver %d]: Sent modified text: [%s]\n", getpid(), response);    
  }
}

/* Reverses the string s */
void process(char *s) {
  int a = strlen(s) - 1, b=0;

  char c;

  while(a > b){
    c = s[a];
    s[a] = s[b];
    s[b] = c;
    a--; b++;
  }
}
