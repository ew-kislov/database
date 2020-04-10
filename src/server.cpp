#include <iostream>
#include <string>

#include "socket/ServerSocket.cpp"
#include "socket/ClientSocket.cpp"

#include "socket/SocketException.cpp"

#include "query_parser/QueryParser.cpp"

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
    // ServerSocket serverSocket(PORT);
    // serverSocket.listen();

    // while (1) {
    //     ClientSocket clientSocket = serverSocket.accept();
    //     clientSocket.handle(handler);
    // }

    // serverSocket.close();

    QueryParser::parseQuery("SELECT f1, f2, f3, f4, f5, f6, f7 FROM t WHERE f1=5 OR f2='a' AND (f3 IN (1,2,3) OR f1=2) OR f3 LIKE 'b%';");


    return 0;
}
