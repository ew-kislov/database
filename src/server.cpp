#include <iostream>
#include <string>

#include "socket/ServerSocket.cpp"
#include "socket/ClientSocket.cpp"
#include "socket/SocketException.cpp"

#include "query_parser/QueryParser.cpp"
#include "query_parser/QueryParserException.cpp"

#include "query_processor/QueryObject.cpp"
#include "query_processor/SelectObject.cpp"
#include "query_processor/QueryProcessor.cpp"

using namespace std;

#define PORT 3000

void handler(ClientSocket clientSocket) {
    try {
        while (1) {
            string message = clientSocket.read();
            message = "Replying: " + message;
            cout << message << endl;
            clientSocket.write(message); 
        }
    } catch (const SocketException &ex) {
        cout << "Socket exception:\n\t" << ex.what() << endl;
        exit(0);
    }
}

int main() {
    // try {
    //    ServerSocket serverSocket(PORT);
    //    serverSocket.listen();

    //    while (1) {
    //         ClientSocket clientSocket = serverSocket.accept();
    //         clientSocket.handle(handler);
    //    }

    //    serverSocket.close();
    // } catch (const SocketException &ex) {
    //         cout << "Socket exception:\n\t" << ex.what() << endl;
    // }

    while (true) {
        string query;
        getline(cin, query);

        try {
            QueryObject* queryObject = QueryParser::parseQuery(query);
            string result = QueryProcessor::executeQuery(queryObject);
            cout << result << endl;
        } catch(const exception &ex) {
            cout << ex.what() << endl;
        }
    }
    
    return 0;
}
