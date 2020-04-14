#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "12345"
#define BUF_SIZE 100

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./client msg\n");
        return 1;
    }

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sockfd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int s = getaddrinfo(SERVER_IP, SERVER_PORT, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return 1;
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sockfd = socket(rp->ai_family, rp->ai_socktype, 0);
        if (sockfd == -1) {
            continue;
        }

        if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1) {
            break;
        }

        close(sockfd);
    }

    if (rp == NULL) {
        fprintf(stderr, "Could not connect.\n");
        return 1;
    }

    freeaddrinfo(result);

    int len = strlen(argv[1]);
    if (len > BUF_SIZE) {
        printf("Msg too long.\n");
        return 1;
    }

    if (write(sockfd, argv[1], len) != len) {
        fprintf(stderr, "write failed.\n");
        return 1;
    }

    char buf[BUF_SIZE];
    int n = read(sockfd, buf, BUF_SIZE);
    if (n == -1) {
        fprintf(stderr, "read error.\n");
        return 1;
    }

    fprintf(stdout, "Response from server: %s\n", buf);

    close(sockfd);

    return 0;

}
