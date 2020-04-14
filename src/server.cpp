#include <iostream>
#include <string>

#include "socket/ServerSocket.cpp"
#include "socket/ClientSocket.cpp"

#include "socket/SocketException.cpp"
#include "query_parser/QueryParserException.cpp"

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
    try {
//        ServerSocket serverSocket(PORT);
//        serverSocket.listen();
//
//        while (1) {
//             ClientSocket clientSocket = serverSocket.accept();
//             clientSocket.handle(handler);
//        }
//
//        serverSocket.close();

//        QueryParser::parseQuery("SELECT f1, f2 FROM t WHERE f2 IN ('as','d') AND f1 NOT IN (1,2);");
        
//        QueryParser::parseQuery("SELECT f1, f2 FROM t;");

        QueryParser::parseQuery("SELECT f1, f2, f3, f4, f5, f6, f7 FROM t WHERE f1=5 OR f2 = 'a' AND (f3 IN ('1' , '2' , '3') OR f1=2) OR f3 LIKE 'b%';");
//        QueryParser::parseQuery("select f1,f2 from t where ((f1 in (1,2,3) or f2=5) and (f3=0)) and (f4 like 'b%');");
    } catch (const SocketException & ex) {
        cout << "Socket exception:\n\t" << ex.what() << endl;
    } catch (const QueryException & ex) {
        cout << "Query exception:\n\t" << ex.what() << endl;
    }
    
     
     


    return 0;
}
