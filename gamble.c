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
  data = abs(data) % 10001;
  return data;
}

//void handle_decision(char decisionA[50], char decisionB[50], double prize, int whoAmI){
  void handle_decision(char decisionA[50], char decisionB[50], double prize){
  decisionA[strlen(decisionA) - 1] = '\0';
  decisionB[strlen(decisionB) - 1] = '\0';
  if(strcmp(decisionA, decisionB) == 0){
    printf("decisonA: %s\n", decisionB);
    printf("decisonB: %s\n", decisionB);
    prize /= 2;
    if(strcmp(decisionA, "split") == 0){
      printf("You both split! You both won $%.2f\n", prize);
    }else{
      printf("You both stole! You both lost $%.2f\n", prize);
    }
  }else{
    if(strcmp(decisionA, "split")){
      printf("You split but your opponent stole! You were robbed of $%.2f\n", prize);
    }else{
      printf("You stole and your opponent split! You robbed of $%.2f\n", prize);
    }
  }
}

//debug
