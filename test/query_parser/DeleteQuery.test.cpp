#include "../../src/query_processor/QueryObject.cpp"
#include "../../src/query_processor/DeleteObject.cpp"

#include "../../src/query_parser/QueryParser.cpp"

#include "../../src/query_parser/QueryParserException.cpp"

#include <string>

using namespace std;

void testValidDelete() {
    try {
        string query = "DELETE FROM table WHERE f1=6 AND f2 IN (2,5,6) OR f3 LIKE 'b';";
        QueryObject* queryObject = QueryParser::parseQuery(query);
        DeleteObject* deleteObject = dynamic_cast<DeleteObject*>(queryObject);
        
        assert(deleteObject->getConditionTree() != nullptr);
    } catch (const exception &ex) {
        assert(false);
    }
}

void testMissingWhereClause() {
    try {
        string query = "DELETE FROM table;";
        QueryObject* queryObject = QueryParser::parseQuery(query);
        DeleteObject* deleteObject = dynamic_cast<DeleteObject*>(queryObject);
    } catch (const exception &ex) {
        assert(true);
    }
}

void testWrongTableName() {
    try {
        string query = "DELETE FROM 1table WHERE f1=6 AND f2 IN (2,5,6) OR f3 LIKE 'b';";
        QueryObject* queryObject = QueryParser::parseQuery(query);
        DeleteObject* deleteObject = dynamic_cast<DeleteObject*>(queryObject);
    } catch (const exception &ex) {
        assert(true);
    }
}

int main() {
    testValidDelete();
    
    testMissingWhereClause();
    testWrongTableName();
    
    return 0;
}
