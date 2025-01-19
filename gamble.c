#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>

struct User {
  char username[512];
  char password[512];
};
union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO */
                            /* (Linux-specific) */
 };

 void user_handler(){
   int fd = open("usernames.txt", O_CREAT | O_RDWR | O_APPEND, 0440);
   printf("Please enter a username: (Please note that usernames and passwords are case sensitive)\n");
   struct User activeplayers[150];
   struct User user;
   fgets(user.username, sizeof(user.username), stdin);
   int placeholder;
   for(int i = 0; i < 150; i++){ //Go through to see if username has been taken
     if(activeplayers[i].username != NULL){
       placeholder = i;
       if(strcmp(activeplayers[i].username, user.username) == 0){
         printf("Please enter the password for %s: ", user.username);
         fgets(user.password, sizeof(user.password), stdin);
         while(1){
           if(strcmp(user.password, activeplayers[i].password)){
             printf("Incorrect password, please try again (if you typed the wrong username crl + c)\n");
           }
           else{
             break;
           }
         }
         if(strcmp(user.password, activeplayers[i].password) == 0){
           printf("\nLogin successful! Welcome back %s\n", user.username);
           break;
         }
       }
     }
   }

 }

void redraw_prompt() {
    printf("\rYou: ");
    fflush(stdout);
}

void clear_stdin() {
    printf("\nTimes up! Clearing previous messages...press enter to continue");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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
void handle_decision(char decisionA[50], char decisionB[50], double prize, int whoAmI){
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
      if(whoAmI == 1){
        printf("You split but your opponent stole! You were robbed of $%.2f\n", prize);
      }
      else{
        printf("You stole and your opponent split! You robbed $%.2f\n", prize);
      }
    }
      else{
        if(whoAmI == 1){
          printf("You stole and your opponent split! You robbed $%.2f\n", prize);
        } else{
          printf("You split but your opponent stole! You were robbed of $%.2f\n", prize);
        }
    }
  }
}

//debug
