#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>
//#include "gamble.h"

int create_prize(){
  int fd = open("/dev/random", O_RDONLY, 0440);
  int data;
  if(read(fd, &data, sizeof(data)) < 0){
    perror("mkfifo");
    exit(1);
  }
  close(fd);
  return data;
}

void discussion_time(){
  printf("You will have the next 10 seconds to discuss whether to steal or split the prize");
  char *player_A[BUFFER_SIZE];
  char *player_B[BUFFER_SIZE];
  
  //fork for 10 seconds and then call wait in play_game??
}

void decision_time(){
  printf("You will have the next 5 seconds to steal or split the prize");
}

void play_game(){
  int prize = create_prize();
  prize = abs(prize) % 100;
  printf("Total prize: $%d \n", prize);

  discussion_time();

}
  /*

discussion_time() - also how

  */

  /*

  decision_time()

  */

// Debug
int main(){
  play_game();
}
