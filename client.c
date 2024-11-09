#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "192.168.56.101", &server_addr.sin_addr); // Server IP

    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    strcpy(buffer, "ping");
    send(sockfd, buffer, strlen(buffer), 0);
    
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("Server time: %s\n", buffer);

    close(sockfd);
    return 0;
}
