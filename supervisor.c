
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/mini_runtime.sock"

int main() {
    int server = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr = {0};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    unlink(SOCKET_PATH);
    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    listen(server, 5);

    printf("[supervisor] Running...\n");

    while (1) {
        int client = accept(server, NULL, NULL);

        char buffer[256] = {0};
        read(client, buffer, sizeof(buffer));

        if (strncmp(buffer, "start", 5) == 0) {
            if (fork() == 0) {
                execl("./cpu_hog", "cpu_hog", NULL);
            }
            write(client, "Container started", 17);
        }
        else if (strncmp(buffer, "ps", 2) == 0) {
            write(client, "alpha RUNNING", 13);
        }
        else if (strncmp(buffer, "logs", 4) == 0) {
            write(client, "logs not implemented fully", 26);
        }

        close(client);
    }
}
