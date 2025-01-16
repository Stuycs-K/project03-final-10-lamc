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

//debug
