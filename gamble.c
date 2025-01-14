#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>
union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO */
                            /* (Linux-specific) */
 };
////

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
  //char *player_A[BUFFER_SIZE];
  //char *player_B[BUFFER_SIZE];

  time_t end_time = time(NULL) + 10;
  while(time(NULL) < end_time){
    printf("i");
    sleep(1);
  }
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
