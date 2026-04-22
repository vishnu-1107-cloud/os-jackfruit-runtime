
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/mini_runtime.sock"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: engine <start|ps|logs>\n");
        return 1;
    }

    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr = {0};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("connect");
        return 1;
    }

    char buffer[256] = {0};
    snprintf(buffer, sizeof(buffer), "%s %s %s",
             argv[1],
             argc > 2 ? argv[2] : "",
             argc > 3 ? argv[3] : "");

    write(sock, buffer, strlen(buffer));

    int n = read(sock, buffer, sizeof(buffer));
    if (n > 0) {
        buffer[n] = '\0';
        printf("%s\n", buffer);
    }

    close(sock);
    return 0;
}
