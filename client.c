#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    //Create buffer, get user input
    char user_input[1024];
    char* hello = "Hello from client";
while(1){
  bzero(user_input,1024);
  fgets(user_input,1024,stdin);
  printf("USER_INPUT: %s\n", user_input);
  send(client_fd, user_input, strlen(user_input), 0);
  //memset(user_input, '\0',strlen(user_input));
}

    valread = read(client_fd, buffer, 1024 - 1); // subtract 1 for the null
    // terminator at the end
    //printf("%s\n", user_input);

    // closing the connected socket
    close(client_fd);
    return 0;
}
