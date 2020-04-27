#include <iostream>
#include <string>

#include "socket/ServerSocket.cpp"
#include "socket/ClientSocket.cpp"

#include "socket/SocketException.cpp"

#include "query_parser/QueryParser.cpp"

#include "query_parser/QueryParserException.cpp"

#include "query_processor/QueryObject.cpp"
#include "query_processor/SelectObject.cpp"

using namespace std;

#define PORT 8080

// void handler(ClientSocket clientSocket) {
//     while (1) {
//         string message = clientSocket.read();
//         message = "Replying: " + message;
//         cout << message << endl;
//         clientSocket.write(message); 
//     }
// }

int main() {
    // try {
    //    ServerSocket serverSocket(PORT);
    //    serverSocket.listen();

    //    while (1) {
    //         ClientSocket clientSocket = serverSocket.accept();
    //         clientSocket.handle(handler);
    //    }

    //    serverSocket.close();
    // } catch (const QueryException &ex) {
    //         cout << "Query exception:\n\t" << ex.what() << endl;
    // }

    while (true) {
        string query;
        getline(cin, query);

        try {
            QueryObject* queryObject = QueryParser::parseQuery(query);
            cout << queryObject->toString() << endl;
        } catch(const QueryException &ex) {
            cout << ex.what() << endl;
        }
    }
    
    return 0;
}
