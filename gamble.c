#include "gamble.h"

int create_prize(){
  int data = open("arraydata.dat", O_CREAT | O_RDWR, 0640);
  if(read(data, &data, sizeof(data)) < 0){
    perror("mkfifo");
    exit(1);
  }
  return data;
}

void discussion_time(){
  printf("You will have the next 10 seconds to discuss whether to steal or split the prize");

  //fork for 10 seconds and then call wait in play_game??
}

void decision_time(){
  printf("You will have the next 5 seconds to steal or split the prize");
}

void play_game(){
  int prize = create_prize();
  prize = abs(prize) % 100
  printf("Total prize: $%d \n", prize);
  /*

discussion_time() - also how

  */

  /*

  decision_time()

  */

}
