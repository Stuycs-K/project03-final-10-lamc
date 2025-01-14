#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
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
    // Address address
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }
    // Connect to server
    if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }
    printf("Connected to server. Please wait for another player...\n");

    //Handshake w/ server to ensure connection with another client
    char bufferServer[10];
    if(read(client_fd, bufferServer, sizeof(bufferServer) - 1) <= 0){
      //error handling
    }
    printf("Client found! You will have 10 seconds to to discuss! \n");
    redraw_prompt();
    // Dicussion time
    time_t end = time(NULL) + 10;
    while (time(NULL) < end) {
        FD_ZERO(&read_fds);
        FD_SET(client_fd, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        int max_fd = (client_fd > STDIN_FILENO) ? client_fd : STDIN_FILENO;
        // Wait for activity on socket or stdin
        int activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (activity < 0) {
            perror("select error");
            break;
        }

        // debug CODE *********************************************************
        printf("%ld, %ld \n", time(NULL), end);

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
          //IF TIME IS UP BREAK OUT OF LOOP
          if(time(NULL) > end){
            break;
          }
            bzero(buffer, sizeof(buffer));
            if (fgets(buffer, sizeof(buffer), std in) == NULL) {
                printf("Error reading input.\n");
                break;
            }
            // Send user input to the server
            if (send(client_fd, buffer, strlen(buffer), 0) <= 0) {
                perror("Failed to send message");
                break;
            }
            redraw_prompt();
        }
    }

    // Close the socket
    close(client_fd);
    return 0;
}
