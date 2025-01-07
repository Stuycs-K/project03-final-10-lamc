#include "gamble.h"
int client_running = 1;

static void sighandler(int signo) {
    if ( signo == SIGINT ){
		client_running = 0;
  }
		exit(0);
    else if ( signo == SIGPIPE ){
	}
}

int main() {


  signal(SIGINT, sighandler);

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  int data;
  while(client_running){
	if(read(from_server, &data, sizeof(data)) > 0){
		read(from_server, &data, sizeof(data));
		printf("%d\n", data);
	}else{
	client_running = 0;
		exit(0);
	}

  }
}
