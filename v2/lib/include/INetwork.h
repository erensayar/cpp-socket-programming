
#ifndef I_NETWORK_H
#define I_NETWORK_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
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

namespace socketChatApp {

    class INetwork {

    protected:

        // properties
        int socketFD;
        struct sockaddr_in socketInstance;
        int socketAddrLen = sizeof(socketInstance);
        char buffer[2048] = {0};

        // methods
        void createSocketFD();
        void setSocketOptions(int port);
        string consumeMessage();
        void produceMessage(string msg);

    public:

        // getters & setter
        int getSocketFD() const;
        void setSocketFD(int socketFD);
        sockaddr_in getSocketInstance() const;
        void setSocketInstance(sockaddr_in socketInstance);
        int getSocketAddrLen() const;

    };

}

#endif /* I_NETWORK_H */