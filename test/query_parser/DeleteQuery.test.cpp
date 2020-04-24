#include "../../src/query_processor/QueryObject.cpp"
#include "../../src/query_processor/DeleteObject.cpp"

#include "../../src/query_parser/QueryParser.cpp"

#include "../../src/query_parser/QueryParserException.cpp"

#include <string>

using namespace std;

int main() {
    try {
        string query = "DELETE FROM table WHERE f1=6 AND f2 IN (2,5,6) OR f3 LIKE 'b';";
        QueryObject* queryObject = QueryParser::parseQuery(query);
        DeleteObject* deleteObject = dynamic_cast<DeleteObject*>(queryObject);
        
        cout << deleteObject->toString();
    } catch (const exception &ex) {
        cout << "Exception:\n\t" << ex.what();
    }
    
    return 0;
}
