#include "../include/INetwork.h"

namespace socketChatApp {

    // methods

    void INetwork::createSocketFD() {
        // Create socket file descriptor
        if ((this->socketFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
        }
    }

    void INetwork::setSocketOptions(int port) {
        this->socketInstance.sin_family = AF_INET;
        this->socketInstance.sin_port = htons(port);
        this->socketInstance.sin_addr.s_addr = INADDR_ANY; // TODO : kontrol
    }

    string INetwork::consumeMessage() {
        if ((read(this->socketFD, this->buffer, sizeof(this->buffer))) < 0) {
            printf("\nRead Failed \n");
        }
        return buffer;
    }

    void INetwork::produceMessage(string msgAsString) {
        int msgLength = msgAsString.length() + 1;
        char msgAsCharArray[msgLength];
        strcpy(msgAsCharArray, msgAsString.c_str());
        if ((send(this->socketFD, msgAsCharArray, msgLength, 0)) < 0) {
            printf("\nSend Failed \n");
        }
    }

    // getters & setters
    int INetwork::getSocketFD() const {
        return this->socketFD;
    }

    void INetwork::setSocketFD(int sckFD) {
        this->socketFD = sckFD;
    }

    sockaddr_in INetwork::getSocketInstance() const {
        return this->socketInstance;
    }

    void INetwork::setSocketInstance(sockaddr_in sckInstance) {
        this->socketInstance = sckInstance;
    }

    int INetwork::getSocketAddrLen() const {
        return this->socketAddrLen;
    }

}