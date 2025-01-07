#include "gamble.h"

int server_running = 1;
static void sighandler(int signo) {
    if (signo == SIGINT) {
        remove(WKP);
        server_running = 0;
    } else if (signo == SIGPIPE) {
        printf("pipe broken \n");
    }
}
int main() {
    srand(time(NULL));
    signal(SIGINT, sighandler);
    signal(SIGPIPE, SIG_IGN);

    while (server_running) {
        int to_client, from_client;
        printf("Created WKP pipe and waiting for a client...\n");
        from_client = server_setup();
        if (from_client == -1) {
            perror("server setup");
            continue;
        }
        if (server_handshake(&to_client) == -1) {
            perror("handshake");
            close(from_client);
            continue;
        }
        printf("Handshake \n");
        pid_t pid = fork();
        if (pid == -1) {
            perror("Failed to fork");
            continue;
        }
        if (pid == 0) {
        while (server_running) {

            play_game();

            sleep(1);  // Wait 1 second before sending the next number
        }

        // Clean up file descriptors after client disconnects
        printf("dced \n");
        close(to_client);
        close(from_client);
		exit(0);
        } else {
        }
  }
    return 0;
}
