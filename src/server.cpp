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
<<<<<<< HEAD
    try {
        throw SocketException("try");
        cout << "me" << endl;
        ServerSocket serverSocket(PORT);
        serverSocket.listen();

        while (1) {
            ClientSocket clientSocket = serverSocket.accept();
            clientSocket.handle(handler);
        }

        serverSocket.close();

        //    QueryParser::parse("SELECT f1,  f2,f3,   f4    ,f5,f6,f7   FROM t;");
    } catch (SocketException & ex) {
        cout << ex.what() << endl;
    }
     
=======
    // ServerSocket serverSocket(PORT);
    // serverSocket.listen();

    // while (1) {
    //     ClientSocket clientSocket = serverSocket.accept();
    //     clientSocket.handle(handler);
    // }

    // serverSocket.close();

    QueryParser::parseQuery("SELECT f1,  f2,f3   ,   f4    ,f5,f6,f7   FROM t  WHERE f3= 5 AND f2='a';");
>>>>>>> 51b58d10fa1aed77767bc7ff65a9dbd29cccb939

    return 0;
}
