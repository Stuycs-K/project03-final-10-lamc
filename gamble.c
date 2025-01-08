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

//#include "gamble.h"

///
  if(!(strcmp(argv[1], "create"))){
    int r;
    int fd = open("story.txt", O_TRUNC | O_RDWR | O_CREAT, 0660); //change
/* Create the segment (happens once) - shmget */
/* Access the segment (happens once per process) - shmget */
		shmd = shmget(KEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0660);
		if(shmd == -1){
			//printf("adfhiadshadf\n");
			printf("Error: %s\n", strerror(errno));
			//printf("adfhiadshadf\n");
			//exit(1);
		}
		semaphor_id = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0660);
		if(semaphor_id == -1){
			//printf("why semaphore why \n");
			printf("Error: %s\n", strerror(errno));
			exit(1);
		}
		//printf("Semaphore: %d\n", semaphor_id);
		union semun us;
		us.val = 1;
		r = semctl(semaphor_id, 0, SETVAL, us);
		//printf("semctl returned: %d\n", r);
		//printf("shmd: %d\n", shmd);

// Attach the segment to a variable (once per process)
		data = shmat(shmd, 0, 0);

		*data = 0;
		//printf("data: %d\n", *data);

// Detach the segment from a variable (once per process) - shmdt
/*
		shmdt(data);
		printf("data: %d\n", *data);
    */
	close(fd);
		//printf("Semaphore: %d\n", semaphor_id);
	}
  else if(!(strcmp(argv[1], "view"))){
    FILE *fd = fopen("story.txt", "r"); //change later
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fd)) {
        printf("%s", buffer); // Print each line
    }
  }
  else if(!(strcmp(argv[1], "write"))){
	shmd = shmget(KEY, sizeof(int), IPC_EXCL | 0660);
    semaphor_id = semget(KEY, 1, 0660);
    printf("Attempting to write to file\n");
	/*struct sembuf {
		short sem_op;
		short sem_num;
		short sem_flag;
	};*/
	struct sembuf sb;
	sb.sem_op = -1;
	sb.sem_num = 0;
	sb.sem_flg = SEM_UNDO;
	semop(semaphor_id, &sb, 1);
	data = shmat(shmd, 0, 0);
	char line_buff[256];
	//printf("data: %d \n", *data);
	if(*data == 0){
		printf("Congrats! You will start this epic tale. Please write the first line:\n" );
		fgets(line_buff,255,stdin);
		int bytes_of_line = strlen(line_buff);
		int fd = open("story.txt", O_WRONLY, 0660);
		*data = bytes_of_line;
		write(fd, line_buff, bytes_of_line);
		close(fd);
	}else{
		int fd = open("story.txt", O_RDWR, 0660);
		int bytes_of_line = *data;
		lseek(fd, -bytes_of_line, SEEK_END);
		int bytes_read = read(fd, line_buff, bytes_of_line);
		line_buff[bytes_read] = '\0';
		printf("Previous Line: %s\nPlease write the next line:\n", line_buff);
		fgets(line_buff,255,stdin);
		*data = strlen(line_buff);
		lseek(fd, 0, SEEK_END);
		write(fd, line_buff, *data);
		close(fd);

	}

	sb.sem_op = 1;
	semop(semaphor_id, &sb, 1);
	int *data = shmat(shmd, 0, 0);
  }
}

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
