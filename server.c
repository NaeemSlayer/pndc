#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main() {
    int sockfd, new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    
    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(sockfd, 5);

    printf("Server waiting for connections...\n");
    addr_size = sizeof(client_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&client_addr, &addr_size);
    
    printf("Client connected.\n");

    while (1) {
        recv(new_sock, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "ping") == 0) {
            time_t now = time(NULL);
            char *timestamp = ctime(&now);
            send(new_sock, timestamp, strlen(timestamp), 0);
        }
    }
    close(new_sock);
    close(sockfd);
    return 0;
}
