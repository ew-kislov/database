#include "../../src/engine/DataType.cpp"
#include "../../src/engine/Number.cpp"
#include "../../src/engine/Varchar.cpp"
#include "../../src/engine/TableField.cpp"
#include "../../src/engine/DataTypeEnum.h"

#include "../../src/query_processor/QueryObject.cpp"
#include "../../src/query_processor/CreateObject.cpp"

#include "../../src/query_parser/QueryParser.cpp"

#include "../../src/query_parser/QueryParserException.cpp"

#include <string>

using namespace std;

int main() {
    try {
        string query = "CREATE TABLE table (cat TEXT (12), doggo ji NUMBER, lama TEXT (14));";
        QueryObject* queryObject = QueryParser::parseQuery(query);
        CreateObject* createObject = dynamic_cast<CreateObject*>(queryObject);
        
        cout << createObject->toString();
    } catch (const exception &ex) {
        cout << "Exception:\n\t" << ex.what();
    }
    
    
    return 0;
}
