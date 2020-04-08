#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include <vector>
#include <iostream>
#include <string>

#include "socket/ServerSocket.cpp"
#include "socket/ClientSocket.cpp"

#define PORT 8080

using namespace std;

void handler(ClientSocket clientSocket) {
    string message;
    
    while (1) {
        getline(cin, message);
        clientSocket.write(message);
        message = clientSocket.read();
        cout << message << endl;
    }
}

int main() {
    ClientSocket clientSocket("127.0.0.1", PORT);
    clientSocket.handle(handler, false);

    return 0;
}
