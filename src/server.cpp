#include <iostream>
#include <string>

#include "socket/ServerSocket.cpp"
#include "socket/ClientSocket.cpp"

using namespace std;

#define PORT 8080

void handler(ClientSocket clientSocket) {
    while (1) {
        string message = clientSocket.read();
        message = "Replying: " + message;
        cout << message << endl;
        clientSocket.write(message); 
    }
}

int main() {
    ServerSocket serverSocket(PORT);
    serverSocket.listen();

    while (1) {
        ClientSocket clientSocket = serverSocket.accept();
        clientSocket.handle(handler);
    }

    serverSocket.close();
    return 0;
}