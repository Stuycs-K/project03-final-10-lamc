#include "gamble.h"

int server_setup() {
  int from_client = 0;
  //Create WKP
  if (mkfifo(WKP, 0660) == -1 && errno != EEXIST) {
    perror("mkfifo");
    exit(1);
  }
  if ((from_client = open(WKP, O_RDONLY)) == -1) {
    perror("open");
    exit(1);
   }
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client;
  srand(time(NULL));
  if ((from_client = open(WKP, O_RDONLY)) == -1) {
      perror("open");
      exit(1);
   }
  char pp[HANDSHAKE_BUFFER_SIZE];
  memset(pp, 0, sizeof(pp));
  int bytesread = read(from_client, pp, sizeof(pp));

     remove(WKP);

   printf("Recieved SYN (%s)\n", pp);
  if ((*to_client = open(pp, O_WRONLY)) == -1) {
    perror("open");
    exit(1);
  }
   int random_syn = rand();
   printf("Sending SYN_ACK (%d)\n", random_syn);
   write(*to_client, &random_syn, sizeof(random_syn));
   int ackno;
   if (read(from_client, &ackno, sizeof(ackno)) <= 0){
	   perror("read");
        exit(1);
    }
   printf("Recieved ACK (%d)\n", ackno);
  close(from_client);
  return from_client;
}

/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
  char pp[HANDSHAKE_BUFFER_SIZE];
  snprintf(pp, sizeof(pp), "%d", getpid());
  //from_server = pp;
  //snprintf this;
  if (mkfifo(pp, 0660) == -1 && errno != EEXIST) {
      perror("mkfifo");
      exit(1);
  }else {
    printf("Private pipe '%s' created successfully\n", pp);
}
  if ((*to_server = open(WKP, O_WRONLY)) == -1) {
      perror("open");
      exit(1);
   }
 //*to_server = fd_fifo;
  printf("Sending SYN (%s) to server\n", pp);
  write(*to_server, pp, sizeof(pp));
  from_server = open(pp, O_RDONLY);
  int acknowledgement;
  read(from_server, &acknowledgement, sizeof(acknowledgement));
  acknowledgement = acknowledgement + 1;
  printf("Recieved SYN_ACK (%d), sending ACK (%d) to server \n", acknowledgement - 1, acknowledgement);
  int byteswritten = write(*to_server, &acknowledgement, sizeof(acknowledgement));
  remove(pp);
  printf("bytes written %d\n", byteswritten);
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
    int to_client = 0;

    // Complete the communication by reading and writing messages
    char buffer[BUFFER_SIZE];
    while (1) {
        memset(buffer, 0, sizeof(buffer));  // Clear buffer before use

        int bytes_read = read(from_client, buffer, sizeof(buffer) - 1);  // Read message, leaving room for null terminator
        if (bytes_read <= 0) {
            perror("Error reading from client");
            break;
        }

        printf("Received from client: %s\n", buffer);

        // Ensure buffer does not overflow when adding the "Server received: " prefix
        int max_len = sizeof(buffer) - strlen("Server received: ") - 1;  // Reserve space for the prefix and null terminator
        snprintf(buffer, max_len, "Server received: %s", buffer);  // Format safely into buffer

        if (write(from_client, buffer, strlen(buffer)) == -1) {
            perror("Error writing to client");
            break;
        }

        sleep(1);  // Simulate ongoing communication every second
    }

    close(from_client);  // Close the connection after communication is done
    return to_client;
}
