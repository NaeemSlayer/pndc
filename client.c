#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Set server address information
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "10.0.2.6", &server_addr.sin_addr);  // Use the server's IP address here

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        return 1;
    }

    // Send a "ping" message to the server
    strcpy(buffer, "ping");
    send(sockfd, buffer, strlen(buffer), 0);
    
    // Receive the timestamp from the server
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("Server time: %s\n", buffer);

    // Close the connection
    close(sockfd);
    return 0;
}
