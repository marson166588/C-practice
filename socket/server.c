#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ctype.h>

#define BIND_IP         "127.0.0.1"
#define BIND_PORT       "12345"
#define BUF_SIZE        100
#define LISTEN_BACKLOG  10

int main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sockfd, connfd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int s = getaddrinfo(BIND_IP, BIND_PORT, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return 1;
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sockfd = socket(rp->ai_family, rp->ai_socktype, 0);
        if (sockfd == -1) {
            printf("socket continue.\n");
            continue;
        }
        if (bind(sockfd, rp->ai_addr, rp->ai_addrlen) == 0) {
            break;
        }

        close(sockfd);
    }

    if (rp == NULL) {
        fprintf(stderr, "Cannot create passive socket on %s:%s\n", BIND_IP, BIND_PORT);
        return 1;
    }

    if (listen(sockfd, LISTEN_BACKLOG) == -1) {
        printf("listen error.\n");
    }

    freeaddrinfo(result);

    printf("Accepting connections ...\n");
    int i, n;
    char buf[BUF_SIZE];
    while (1) {
        connfd = accept(sockfd, NULL, NULL);
        if (connfd == -1) {
            printf("accept error.\n");
            break;
        }

        memset(buf, 0, sizeof(buf));

        n = read(connfd, buf, BUF_SIZE);
        printf("received msg: %s\n", buf);

        for (i = 0; i < n; i++) {
            buf[i] = toupper(buf[i]);
        }
        write(connfd, buf, n);

        close(connfd);
    }

    return 0;
}
