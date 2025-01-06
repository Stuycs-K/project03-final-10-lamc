#include gamble.c

int create_prize(){
  int data = open("arraydata.dat", O_CREAT | O_RDWR, 0640);
  if(read(data, &data, sizeof(data)) < 0){
    perror("mkfifo");
    exit(1);
  }
  return data;
}

void discussion_time(){

}

void play_game(){
  int prize = create_prize();
  prize = abs(prize) % 100
  printf("Total prize: $%d \n", prize);
  printf("You will have the next 10 seconds to discuss whether to steal or split the prize");
  /*

  Discussion code

  */
}
