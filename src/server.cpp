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

//        QueryParser::parseQuery("SELECT f1, f2 FROM t WHERE f1 >= 5 OR f2 IN ('as','d') AND f1 NOT IN (1,2);");
        cout << endl;
//         QueryParser::parseQuery("SELECT f1, f2 FROM t WHERE f1 = 'fuck';");
//        cout << endl;
//        QueryParser::parseQuery("SELECT f1, f2 FROM t WHERE f2 LIKE 'ab_' OR f2 IN ('as','d') AND f1 NOT IN (1,2);");
//        cout << endl;
//        QueryParser::parseQuery("SELECT f1, f2 FROM t WHERE f1 = 5 OR NOT f2 = 'a' AND ( f3 NOT IN ( '1','2','3' ) OR f1 = 2 ) OR f3 NOT LIKE 'b%';");
//        cout << endl;
//        QueryParser::parseQuery("SELECT f1, f2, f3, f4, f5, f6, f7 FROM t WHERE f1=5 OR NOT f2 = 'a' AND (f3 NOT IN ('1' , '2' , '3') OR f1=2) OR f3 NOT LIKE 'b%';");
//        cout << endl;
//        QueryParser::parseQuery("select f1,f2 from t where (f1 IN (1,2,3) OR f2=5) AND (f3=0) AND (f4 LIKE 'b%');");
//        QueryParser::parseQuery("select f1,f2 from t where ( f1 in ( 1,2,3 ) or f2 = 5 ) and ( f3 = 0 )  and ( f4 like 'b%' );");
//        QueryParser::parseQuery("DROP TABLE table;");
//        QueryParser::parseQuery("INSERT INTO table ('qwerty', 12, 'adv');");
//        QueryParser::parseQuery("DELETE FROM table WHERE f1=6;");
//        QueryParser::parseQuery("CREATE TABLE table (cat TEXT (12), doggo NUMBER, lama TEXT (14));");
    } catch (const SocketException & ex) {
        cout << "Socket exception:\n\t" << ex.what() << endl;
    } catch (const QueryException & ex) {
        cout << "Query exception:\n\t" << ex.what() << endl;
    }
    
    return 0;
}
