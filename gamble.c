#include gamble.c

int create_prize(){
  int data = open("arraydata.dat", O_CREAT | O_RDWR, 0640);
  if(read(data, &data, sizeof(data)) < 0){
    perror("mkfifo");
    exit(1);
  }
  return data;
}

void play_game(){
  int prize = create_prize();
  printf("Total prize: %d \n", prize);
  printf("You will have the next 10 seconds to discuss")
}
