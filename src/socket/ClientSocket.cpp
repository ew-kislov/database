#pragma once

#include "ClientSocket.h"

ClientSocket::ClientSocket(string host, int port) {
    struct sockaddr_in serverParams;

    this->socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketFd < 0) {
        // TODO: throw SocketException("Couldn't create socket");
        exit(0);
    }

    serverParams.sin_family = AF_INET;
    serverParams.sin_port = htons(port);
    serverParams.sin_addr.s_addr = inet_addr(host.c_str());

    int connectResult = connect(this->socketFd, (struct sockaddr *)&serverParams, sizeof(serverParams));

    if (connectResult < 0) {
        // TODO: throw SocketException("Couldn't create socket");
        exit(0);
    }
}

ClientSocket::ClientSocket(int socketFd, string host, int port) {
    this->socketFd = socketFd;
    this->host = host;
    this->port = port;
}

void ClientSocket::handle(void (*handler)(ClientSocket clientSocket), bool shouldCreateProcess) {
    if (shouldCreateProcess) {
        if (fork() == 0) {
            handler(*this);
        }
    } else {
        handler(*this);
    }    
}