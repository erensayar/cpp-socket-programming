#include <iostream>
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

    int client_fd;
    string server_ip = "127.0.0.1";
    int server_port = 9999;
    struct sockaddr_in server_socket_addr;
    char buffer[1024] = {0};
    string client_message;

    // Creating socket file descriptor
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    cout << "Server Ip: " << server_ip << endl;
    cout << "Server Port: " << server_port << endl;

    // Set socket options
    server_socket_addr.sin_family = AF_INET;
    server_socket_addr.sin_port = htons(server_port);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    char serverIpAsChar[server_ip.length() + 1];
    strcpy(serverIpAsChar, server_ip.c_str()); // string to char
    if (inet_pton(AF_INET, serverIpAsChar, &server_socket_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((connect(client_fd, (struct sockaddr *) &server_socket_addr, sizeof(server_socket_addr))) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Chat
    bool connection = true;
    while (connection) {


        // Send
        cout << "Enter the message: ";
        cin >> client_message;
        int sizeOfClientMsg = client_message.length() + 1;
        char msgAsChArr[sizeOfClientMsg];
        strcpy(msgAsChArr, client_message.c_str()); // string to char
        if ((send(client_fd, msgAsChArr, sizeOfClientMsg, 0)) < 0) {
            printf("\nSend Failed \n");
            return -1;
        }

        // Read
        if ((read(client_fd, buffer, 1024)) < 0) {
            printf("\nRead Failed \n");
            return -1;
        }
        cout << "Server Message: " << buffer << endl;


        // Loop Execute
        if (strcmp(msgAsChArr, "con=false") == 0) {
            connection = false;
        }
    }

    // closing the connected socket
    close(client_fd);
    return 0;
}