#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>

#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>

#else

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#endif

using namespace std;

int main(int argc, char const *argv[]) {

    int server_fd;
    int new_server_fd;
    int valread;
    int opt = 1;
    int port = 9999;
    struct sockaddr_in socket_address;
    int addrlen = sizeof(socket_address);
    char buffer[1024] = {0};
    string server_message;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

#ifdef _WIN32
#else
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
#endif

    // Set socket options
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    socket_address.sin_port = htons(port);

    // Binding 
    if (bind(server_fd, (struct sockaddr *) &socket_address, sizeof(socket_address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Accept
    if ((new_server_fd = accept(server_fd, (struct sockaddr *) &socket_address, (socklen_t *) &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Chat
    bool connection = true;
    while (connection) {

        // Read
        if ((read(new_server_fd, buffer, 1024)) < 0) {
            printf("\nRead Failed \n");
            return -1;
        }
        cout << "Client Message: " << buffer << endl;

        // Send
        cout << "Enter the message: ";
        cin >> server_message;
        int sizeOfServerMsg = server_message.length() + 1;
        char msgAsChArr[sizeOfServerMsg];
        strcpy(msgAsChArr, server_message.c_str()); // string to char
        if ((send(new_server_fd, msgAsChArr, sizeOfServerMsg, 0)) < 0) {
            printf("\nSend Failed \n");
            return -1;
        }

        // Loop Execute
        if (strcmp(msgAsChArr, "con=false") == 0) {
            connection = false;
        }
    }

    // closing the connected socket
    close(new_server_fd);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);

    return EXIT_SUCCESS;
    return 0;
}
