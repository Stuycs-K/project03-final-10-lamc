#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>
double money_array[100] = {0.0};
 struct User {
   char username[512];
   double money;
 };

 void update_line(double value, int index, int lineLength) {
    int fd = open("money.txt", O_RDWR);
    if (fd < 0) {
        perror("open file");
        return;
    }
    off_t offset = index * lineLength;
    if (lseek(fd, offset, SEEK_SET) == (off_t)-1) {
        perror("seek file");
        close(fd);
        return;
    }
    char buffer[100];
    int formattedLength = snprintf(buffer, sizeof(buffer), "%-14.6f\n", value);
    if (formattedLength > lineLength) {
        fprintf(stderr, "exceeds line length\n");
        close(fd);
        return;
    }
    if (write(fd, buffer, lineLength) != lineLength) {
        perror("write file");
        close(fd);
        return;
    }
    close(fd);
    //printf("Line %d updated successfully in the file.\n", index);
}


int user_handler() {
   FILE *fp = fopen("usernames.txt", "a+");
   FILE *moneyfile = fopen("money.txt", "r+");
   if (!fp || !moneyfile) {
       perror("failes did not open");
       return -1;
   }
   double num;
   int count = 0;
   while (fscanf(moneyfile, "%lf", &num) == 1) {
       if (count >= sizeof(money_array) / sizeof(money_array[0])) {
           break;
       }
       money_array[count++] = num;
   }
   for (int i = count; i < 100; i++) {
       money_array[i] = 0.0;
   }
   fclose(moneyfile);
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
               printf("Hello again, %s!\n", user.username);
               hasUser = 1;
               placeholder = i;
               break;
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
      update_line(money_array[place], place, 15);
    }else{
      printf("You both stole! You both lost $%.2f\n", prize);
      money_array[place] -= prize;
      printf("Your new balance is: $%.2f\n", money_array[place]);
      update_line(money_array[place], place, 15);
    }
  }else{
    if(strcmp(decisionA, "split")){
      if(whoAmI == 1){
        printf("You split but your opponent stole! You were robbed of $%.2f\n", prize);
        printf("Your balance is: $%.2f\n", money_array[place]);
        update_line(money_array[place], place, 15);
      }
      else{
        printf("You stole and your opponent split! You robbed $%.2f\n", prize);
        money_array[place] += prize;
        printf("Your new balance is: $%.2f\n", money_array[place]);
        update_line(money_array[place], place, 15);
      }
    }
      else{
        if(whoAmI == 1){
          printf("You stole and your opponent split! You robbed $%.2f\n", prize);
          money_array[place] += prize;
          printf("Your new balance is: $%.2f\n", money_array[place]);
          update_line(money_array[place], place, 15);
        } else{
          printf("You split but your opponent stole! You were robbed of $%.2f\n", prize);
          printf("Your balance is: $%.2f\n", money_array[place]);
          update_line(money_array[place], place, 15);
        }
    }
  }
}
