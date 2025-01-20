#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>

double money_array[1000];

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO */
                            /* (Linux-specific) */
 };

 struct User {
   char username[512];
   double money;
 };


 int user_handler() { // Returns the index of the money array that corresponds to the user
     FILE* fp = fopen("usernames.txt", "a+");
     if (!fp) {
         perror("Failed to open file");
         return -1;
     }
     struct User user;
     printf("Please enter a username (usernames are case-sensitive):\n");
     fgets(user.username, sizeof(user.username), stdin);
     size_t len = strlen(user.username);
     if (len > 0 && user.username[len - 1] == '\n') {
         user.username[len - 1] = '\0';
     }
     int placeholder = -1;
     int hasUser = 0;
     char line[512];
     rewind(fp);
     for (int i = 0; i < 150; i++) {
         if (fgets(line, sizeof(line), fp) != NULL) {
             len = strlen(line);
             if (len > 0 && line[len - 1] == '\n') {
                 line[len - 1] = '\0';
            }
             if (strcmp(line, user.username) == 0) {
                 printf("Welcome back, %s!\n", user.username);
                 hasUser = 1;
                 placeholder = i;
         }
         } else {
             placeholder = i;
             break;
         }
     }
     if (!hasUser) {
         fprintf(fp, "%s\n", user.username);
         fflush(fp);
         printf("New user detected! Welcome, %s!\n", user.username);
     }
     fclose(fp);
     printf("PLACEHOLDER: %d\n", placeholder);
     return placeholder;
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
void handle_decision(char decisionA[50], char decisionB[50], double prize, int whoAmI, int place){
    decisionA[strlen(decisionA) - 1] = '\0';
    decisionB[strlen(decisionB) - 1] = '\0';
  if(strcmp(decisionA, decisionB) == 0){
    printf("decisonA: %s\n", decisionB);
    printf("decisonB: %s\n", decisionB);
    prize /= 2;
    if(strcmp(decisionA, "split") == 0){
      printf("You both split! You both won $%.2f\n", prize);
      money_array[place] += prize;
      printf("Your new balance is: $%.2f\n", money_array[place]);
    }else{
      printf("You both stole! You both lost $%.2f\n", prize);
      money_array[place] -= prize;
      printf("Your new balance is: $%.2f\n", money_array[place]);
    }
  }else{
    if(strcmp(decisionA, "split")){
      if(whoAmI == 1){
        printf("You split but your opponent stole! You were robbed of $%.2f\n", prize);
        printf("Your balance is: $%.2f\n", money_array[place]);
      }
      else{
        printf("You stole and your opponent split! You robbed $%.2f\n", prize);
        money_array[place] += prize;
        printf("Your new balance is: $%.2f\n", money_array[place]);
      }
    }
      else{
        if(whoAmI == 1){
          printf("You stole and your opponent split! You robbed $%.2f\n", prize);
          money_array[place] += prize;
          printf("Your new balance is: $%.2f\n", money_array[place]);
        } else{
          printf("You split but your opponent stole! You were robbed of $%.2f\n", prize);
          printf("Your balance is: $%.2f\n", money_array[place]);
        }
    }
  }
}

//debug
