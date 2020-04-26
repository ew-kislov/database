#include "../../src/engine/DataType.cpp"
#include "../../src/engine/Number.cpp"
#include "../../src/engine/Varchar.cpp"
#include "../../src/engine/TableField.cpp"
#include "../../src/engine/DataTypeEnum.h"

#include "../../src/query_processor/QueryObject.cpp"
#include "../../src/query_processor/SelectObject.cpp"

#include "../../src/query_parser/QueryParser.cpp"

#include "../../src/query_parser/QueryParserException.cpp"

#include <string>

using namespace std;

int main() {
    string query = "SELECT f1, f2 FROM t WHERE f1 = 5 OR NOT f2 = 'a' AND ( f3 NOT IN ( '1','2','3' ) OR f1 = 2 ) OR f3 NOT LIKE 'b%';";
    QueryObject* queryObject = QueryParser::parseQuery(query);
    SelectObject* selectObject = dynamic_cast<SelectObject*>(queryObject);
    
    cout << query << endl << selectObject->toString() << endl;
    
    return 0;
}
