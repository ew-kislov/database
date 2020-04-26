#include "../../src/engine/DataType.cpp"
#include "../../src/engine/Number.cpp"
#include "../../src/engine/Varchar.cpp"
#include "../../src/engine/TableField.cpp"
#include "../../src/engine/DataTypeEnum.h"

#include "../../src/query_processor/QueryObject.cpp"
#include "../../src/query_processor/InsertObject.cpp"

#include "../../src/query_parser/QueryParser.cpp"

#include "../../src/query_parser/QueryParserException.cpp"

#include <string>

using namespace std;

int main() {
    string query = "INSERT INTO table ('qwerty', 12, 'adv');";
    QueryObject* queryObject = QueryParser::parseQuery(query);
    InsertObject* insertObject = dynamic_cast<InsertObject*>(queryObject);
    
    cout << query << endl << insertObject->toString() << endl;
    
    return 0;
}
