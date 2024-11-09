#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main() {
    int sockfd, new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[1024];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Set server address information
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Bind socket to the specified IP and port
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        close(sockfd);
        return 1;
    }

    // Listen for incoming connections
    listen(sockfd, 5);
    printf("Server listening on port 8080...\n");

    // Accept a connection from a client
    client_len = sizeof(client_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
    if (new_sock < 0) {
        perror("Client connection failed");
        close(sockfd);
        return 1;
    }

    printf("Client connected\n");

    // Handle client requests in a loop
    while (1) {
        // Clear the buffer for each new message
        memset(buffer, 0, sizeof(buffer));

        // Receive message from client
        int recv_len = recv(new_sock, buffer, sizeof(buffer) - 1, 0);
        if (recv_len <= 0) {
            printf("Client disconnected or error occurred\n");
            break;
        }

        // Check if the message is "ping"
        if (strcmp(buffer, "ping") == 0) {
            time_t now = time(NULL);
            char *timestamp = ctime(&now);

            // Send the current timestamp back to the client
            if (send(new_sock, timestamp, strlen(timestamp), 0) < 0) {
                perror("Error sending timestamp");
                break;
            }
        } else {
            printf("Received unexpected message: %s\n", buffer);
        }
    }

    // Clean up
    close(new_sock);
    close(sockfd);
    printf("Server shut down\n");

    return 0;
}
