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

void testValidCreateSingleField() {
    try {
        string query = "CREATE TABLE table (cat TEXT (12));";
        QueryObject* queryObject = QueryParser::parseQuery(query);
        CreateObject* createObject = dynamic_cast<CreateObject*>(queryObject);
        
        vector<TableField> tableFields;
        
        tableFields.push_back(TableField("cat", DataTypeEnum::VARCHAR));
        
        assert(createObject->getTableFields() == tableFields);
        
        query = "CREATE TABLE table (lama NUMBER);";
        queryObject = QueryParser::parseQuery(query);
        createObject = dynamic_cast<CreateObject*>(queryObject);
        
        tableFields.clear();
        tableFields.push_back(TableField("lama", DataTypeEnum::NUMBER));
        
        assert(createObject->getTableFields() == tableFields);
    } catch (exception &ex) {
        assert(false);
    }
}

void testValidCreateNumberFields() {
    try {
        string query = "CREATE TABLE table (cat NUMBER, doggo NUMBER, lama NUMBER);";
        QueryObject* queryObject = QueryParser::parseQuery(query);
        CreateObject* createObject = dynamic_cast<CreateObject*>(queryObject);
        
        vector<TableField> tableFields;
        
        tableFields.push_back(TableField("cat", DataTypeEnum::NUMBER));
        tableFields.push_back(TableField("doggo", DataTypeEnum::NUMBER));
        tableFields.push_back(TableField("lama", DataTypeEnum::NUMBER));
        
        assert(createObject->getTableFields() == tableFields);
    } catch (exception &ex) {
        assert(false);
    }
}

void testValidCreateVarcharFields() {
    try {
        string query = "CREATE TABLE table (cat TEXT (10), doggo TEXT (12), lama TEXT (14));";
        QueryObject* queryObject = QueryParser::parseQuery(query);
        CreateObject* createObject = dynamic_cast<CreateObject*>(queryObject);
        
        vector<TableField> tableFields;
        
        tableFields.push_back(TableField("cat", DataTypeEnum::VARCHAR));
        tableFields.push_back(TableField("doggo", DataTypeEnum::VARCHAR));
        tableFields.push_back(TableField("lama", DataTypeEnum::VARCHAR));
        
        assert(createObject->getTableFields() == tableFields);
    } catch (exception &ex) {
        assert(false);
    }
}

void testValidCreateMixedFields() {
    try {
        string query = "CREATE TABLE table (cat NUMBER, doggo TEXT (12), lama NUMBER);";
        QueryObject* queryObject = QueryParser::parseQuery(query);
        CreateObject* createObject = dynamic_cast<CreateObject*>(queryObject);
        
        vector<TableField> tableFields;
        
        tableFields.push_back(TableField("cat", DataTypeEnum::NUMBER));
        tableFields.push_back(TableField("doggo", DataTypeEnum::VARCHAR));
        tableFields.push_back(TableField("lama", DataTypeEnum::NUMBER));
        
        assert(createObject->getTableFields() == tableFields);
    } catch (exception &ex) {
        assert(false);
    }
}

void testWrongTableName() {
    try {
        string query = "CREATE TABLE 'table' (cat NUMBER, doggo TEXT (12), lama NUMBER);";
        QueryObject* queryObject = QueryParser::parseQuery(query);
    } catch (exception &ex) {
        assert(true);
    }
    
    try {
        string query = "CREATE TABLE 134 (cat NUMBER, doggo TEXT (12), lama NUMBER);";
        QueryObject* queryObject = QueryParser::parseQuery(query);
    } catch (exception &ex) {
        assert(true);
    }
}

void testWrongFieldsDescritpion() {
    try {
        string query = "CREATE TABLE table (doggo TEXT, lama NUMBER);";
        QueryObject* queryObject = QueryParser::parseQuery(query);
    } catch (exception &ex) {
        assert(true);
    }
    
    try {
        string query = "CREATE TABLE table (doggo TEXT (), lama NUMBER);";
        QueryObject* queryObject = QueryParser::parseQuery(query);
    } catch (exception &ex) {
        assert(true);
    }
    
    try {
        string query = "CREATE TABLE table (doggo TEXT (34), lama);";
        QueryObject* queryObject = QueryParser::parseQuery(query);
    } catch (exception &ex) {
        assert(true);
    }
}

void testMissingBrackets() {
    try {
        string query = "CREATE TABLE table doggo TEXT (12), lama NUMBER;";
        QueryObject* queryObject = QueryParser::parseQuery(query);
    } catch (exception &ex) {
        assert(true);
    }
}

int main() {
    testValidCreateSingleField();
    testValidCreateNumberFields();
    testValidCreateVarcharFields();
    testValidCreateMixedFields();

    testWrongTableName();
    testWrongFieldsDescritpion();
    testMissingBrackets();
    
    return 0;
}
