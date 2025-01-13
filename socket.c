#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#define PORT 8080

int main() {
    int socket_descriptors[100][2] = {0}; // Initialize to 0
    int server_fd, client_socket, max_sd, sd, activity;
    struct sockaddr_in address;
    fd_set read_fds;
    socklen_t addrlen = sizeof(address);   
    // Create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // Set socket options
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d\n", PORT);
    // Start of the loooooooooooOOOOOOOp
    while (1) {
       FD_ZERO(&read_fds);
       FD_SET(server_fd, &read_fds);
       max_sd = server_fd;
        // Add active client sockets to `read_fds`
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 2; j++) {
                sd = socket_descriptors[i][j];
                if (sd > 0) FD_SET(sd, &read_fds);
                if (sd > max_sd) max_sd = sd;
            }
        }
 // Select
        activity = select(max_sd + 1, &read_fds, NULL, NULL, NULL);
      if (activity < 0) {
           perror("select error");
           exit(EXIT_FAILURE);
       }
        // Handle new connection
        if (FD_ISSET(server_fd, &read_fds)) {
            client_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
            if (client_socket < 0) {
                perror("accept error");
                exit(EXIT_FAILURE);
            }

            printf("New client connected: socket %d\n", client_socket);

            // Add client to the first available slot in `socket_descriptors`
            for (int i = 0; i < 100; i++) {
                if (socket_descriptors[i][0] == 0) {
                    socket_descriptors[i][0] = client_socket;
                    break;
                } else if (socket_descriptors[i][1] == 0) {
                    socket_descriptors[i][1] = client_socket;
                    //Fork subserver when there is a pair
					pid_t p = fork();
                    if (p == 0) { //child
                        close(server_fd); // Child doesn't need the listening socket
                        int client1 = socket_descriptors[i][0];
                        int client2 = socket_descriptors[i][1];
                        char buffer[1024];
                        printf("Subserver created for clients %d and %d\n", client1, client2);
						while (1) {
                            FD_ZERO(&read_fds);
                            FD_SET(client1, &read_fds);
                            FD_SET(client2, &read_fds);
							//I need this refrence for ternary operators (select the smallest and add one to it)
                            select((client1 > client2 ? client1 : client2) + 1, &read_fds, NULL, NULL, NULL);
                            if (FD_ISSET(client1, &read_fds)) {
                                bzero(buffer, 1024);
                                if (read(client1, buffer, 1024) <= 0){
									break;
								}
                                send(client2, buffer, strlen(buffer), 0);
                            }
                            if (FD_ISSET(client2, &read_fds)) {
                                bzero(buffer, 1024);
                                if (read(client2, buffer, 1024) <= 0){
									break;
								}									
                                send(client1, buffer, strlen(buffer), 0);
                            }
                        }
                        close(client1);
                        close(client2);
						//Done with game
                        exit(0);
                    }
					if(p == 1){ //Parent
						break;
					}
                    
                }
            }
        }
    }

    return 0;
}