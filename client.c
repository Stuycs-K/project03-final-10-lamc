//GROUP ID = 32
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include "gamble.c"
#define PORT 8080

void redraw_prompt() {
    printf("\rYou: ");
    fflush(stdout);
}

int main() {
    int client_fd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    fd_set read_fds;
    // Create socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // Address gibberish
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        return -1;
    }
    // Connect to server
    if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }
    printf("Connected to server. Please wait for another player...\n");

    //Handshake w/ server to ensure connection with another client
    int prize;
    if(read(client_fd, &prize, sizeof(prize)) <= 0){
      perror("Hankshake failed");
      return -1;
    }
    printf("The total prize pool is: %d\n", prize);
    /*char bufferServer[10];
    if(read(client_fd, bufferServer, sizeof(bufferServer) - 1) <= 0){
      perror("Hankshake failed");
      return -1;
    } */
    printf("Client found! \n");
    printf("Welcome to multiplayer gambling! You will have 10 seconds to discuss! \n");

    redraw_prompt();
    // Dicussion time
    time_t end = time(NULL) + 10;
    while (time(NULL) < end) {
        FD_ZERO(&read_fds);
        FD_SET(client_fd, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        int max_fd = (client_fd > STDIN_FILENO) ? client_fd : STDIN_FILENO;
        // Wait for activity on socket or stdin
        struct timeval timeout;
        timeout.tv_sec = end - time(NULL);
        timeout.tv_usec = 0;
        int activity = select(max_fd + 1, &read_fds, NULL, NULL, &timeout);
        if (activity < 0) {
            perror("select error");
            break;
        }

        // debug CODE *********************************************************
      //  printf("%ld, %ld \n", time(NULL), end);

        // Handle input from the socket (incoming messages)
        if (FD_ISSET(client_fd, &read_fds)) {
          //IF TIME IS UP BREAK OUT OF LOOP
          if(time(NULL) > end){
            break;
          }
            bzero(buffer, sizeof(buffer));
            ssize_t valread = read(client_fd, buffer, sizeof(buffer) - 1);
            if (valread <= 0) {
                printf("Disconnected from server.\n");
                break;
            }
        printf("\nThem: %s", buffer); // Print message
        redraw_prompt();
        }
        // Handle input from stdin (user input)
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            bzero(buffer, sizeof(buffer));
            ssize_t valread = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
            if (valread){
              buffer[valread] = '\0';
              if (send(client_fd, buffer, strlen(buffer), 0) <= 0) {
                  perror("Failed to send message");
                  break;
              }
              redraw_prompt();
            }
            /*
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                printf("Error reading input.\n");
                break;
            }
            */
            // Send user input to the server

        }
    }

    //FINAL DECISION HERE
    char buffer_decision[100];
    char other_buffer_decision[100];
    printf("Times up! Now make your decision (type steal/split)\n");
    if(read(STDIN_FILENO, buffer_decision, sizeof(buffer_decision)) <= 0){
      perror("Decision failed");
      return -1;
    }
    if (send(client_fd, buffer_decision, strlen(buffer_decision), 0) <= 0) {
        perror("Failed to send message");
    }
    ;
    if(read(client_fd, other_buffer_decision, sizeof(other_buffer_decision)) <= 0){
      perror("Other decision failed");
      return -1;
    }
    printf("Other buffer decision: %s\n", other_buffer_decision);
    //READ
    handle_decision(buffer_decision, other_buffer_decision, prize);
    printf("DEBUG STRING LINE 127\n");
    //final_decision();
    close(client_fd);
    // Close the socket
    return 0;
}
