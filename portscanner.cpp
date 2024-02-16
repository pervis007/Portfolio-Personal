#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_PORT 65535
#define TIMEOUT_SEC 1

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <hostname>" << std::endl;
        return 1;
    }

    const char *hostname = argv[1];

    int sockfd;
    struct sockaddr_in server_addr;
    struct timeval timeout;
    fd_set fds;

    for (int port = 1; port <= MAX_PORT; ++port) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            std::cerr << "Error: Could not create socket." << std::endl;
            return 1;
        }

        timeout.tv_sec = TIMEOUT_SEC;
        timeout.tv_usec = 0;
        FD_ZERO(&fds);
        FD_SET(sockfd, &fds);

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        inet_pton(AF_INET, hostname, &server_addr.sin_addr);

        if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            // Port is closed or unreachable
            close(sockfd);
        } else {
            // Port is open
            std::cout << "Port " << port << " is open" << std::endl;
            close(sockfd);
        }
    }

    return 0;
}