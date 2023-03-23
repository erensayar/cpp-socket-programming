#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
    char* server_ip = "127.0.0.1";
    int server_port = 9999;
    struct sockaddr_in serv_addr;
    char* client_message;
    char buffer[1024] = {0};

    // Creating socket file descriptor
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    //cout << "Enter Server Ip: ";
    //cin >> server_ip;
    //cout << "Enter Server Bind Port: ";
    //cin >> server_port;
    cout << "\nserver_ip: " << server_ip << endl;
    cout << "server_port: " << server_port << endl;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Chat
    bool connection = true;
    while(connection = true){
        
        printf("Enter The Message: ");
        scanf("%s", &client_message);
        printf("%s\n", client_message);
        
        // Send
        if((send(client_fd, client_message, strlen(client_message), 0)) < 0) {
            printf("\nSend Failed \n");
            return -1;
        }
        // Read
        if((read(client_fd, buffer, 1024)) < 0) {
            printf("\nRead Failed \n");
            return -1;
        }
        cout << "Server Message: " << buffer << endl;

        // Loop execute
        if(client_message == "con=false") {
            connection = false;
        }
    }

    // closing the connected socket
    close(client_fd);
    return 0;
}