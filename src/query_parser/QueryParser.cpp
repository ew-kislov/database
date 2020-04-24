#pragma once

#include "QueryParser.h"

#include "../shared/StringHelper.cpp"
#include "../shared/VectorHelper.cpp"

#include "QueryHelper.cpp"
#include "LexicParser.cpp"

#include "../query_processor/QueryObject.cpp"
#include "../query_processor/SelectObject.cpp"
#include "../query_processor/InsertObject.cpp"
#include "../query_processor/UpdateObject.cpp"
#include "../query_processor/DropObject.cpp"
#include "../query_processor/DeleteObject.cpp"
#include "../query_processor/CreateObject.cpp"

#include "../query_processor/condition_tree/NegatableCondition.cpp"
#include "../query_processor/condition_tree/OrCondition.cpp"
#include "../query_processor/condition_tree/AndCondition.cpp"
#include "../query_processor/condition_tree/MultipleCondition.cpp"
#include "../query_processor/condition_tree/BinaryCondition.cpp"
#include "../query_processor/condition_tree/InCondition.cpp"
#include "../query_processor/condition_tree/RelationCondition.cpp"
#include "../query_processor/condition_tree/LikeCondition.cpp"

#include "../query_processor/condition_tree/BaseOperand.cpp"
#include "../query_processor/condition_tree/NumberSetOperand.cpp"
#include "../query_processor/condition_tree/StringSetOperand.cpp"
#include "../query_processor/condition_tree/NumberOperand.cpp"
#include "../query_processor/condition_tree/StringOperand.cpp"
#include "../query_processor/condition_tree/TableFieldOperand.cpp"

#include "../engine/TableField.cpp"

#include <set>
#include <string>

// <SQL-query> ::= (<SELECT-statement> | <INSERT -statement> | <UPDATE-statement> |
//                 <DELETE-statement> | <CREATE-statement> | <DROP-statement>);
QueryObject* QueryParser::parseQuery(string query) {
    if (query.find(';') != query.size() - 1) {
        throw QueryException("Query must end with semicolon");
    }

    vector<string> queryTokens = QueryHelper::queryToTokenVector(query);
    queryTokens.pop_back();
    
    string command = StringHelper::getUpperString(queryTokens[0]);

    QueryObject* queryObject;

    if (command == "SELECT") {
        queryObject = QueryParser::parseSelectQuery(queryTokens);
    } else if (command == "INSERT") {
        queryObject = QueryParser::parseInsertQuery(queryTokens);
    } else if (command == "UPDATE") {
        queryObject = QueryParser::parseUpdateQuery(queryTokens);
    } else if (command == "DELETE") {
        queryObject = QueryParser::parseDeleteQuery(queryTokens);
    } else if (command == "CREATE") {
        queryObject = QueryParser::parseCreateQuery(queryTokens);
    } else if (command == "DROP") {
        queryObject = QueryParser::parseDropQuery(queryTokens);
    } else {
        throw QueryException("Unknown command: " + command);
    }

    return queryObject;
}

// <SELECT-statement> ::= SELECT <field list> FROM <table name> [ <WHERE-clause> ]
SelectObject* QueryParser::parseSelectQuery(vector<string> queryTokens) {
    if (
        queryTokens.size() < 4 ||
        QueryHelper::searchKeyWordInVector(queryTokens, "FROM") != 2 ||
        !LexicParser::isIdentifier(queryTokens[3])
    ) {
        throw QueryException("Wrong SELECT query syntax");
    }
    
    vector<string> fields = StringHelper::splitToVector(queryTokens[1], ',');

    SelectObject* selectObject = new SelectObject(queryTokens[3], fields);

    if (queryTokens.size() > 4) {
        selectObject->treeRoot = QueryParser::parseWhereClause(VectorHelper::slice(queryTokens, 4));
    }

    return selectObject;
}

// <INSERT-statement> ::= INSERT INTO <table name> <table row>
InsertObject* QueryParser::parseInsertQuery(vector<string> queryTokens) {
    if (
        queryTokens.size() < 6 ||
        QueryHelper::searchKeyWordInVector(queryTokens, "INTO") != 1 ||
        !LexicParser::isIdentifier(queryTokens[2])
    ) {
        throw QueryException("Wrong INSERT query syntax");
    }

    InsertObject* insertObject = new InsertObject(queryTokens[2]);
    insertObject->setFieldValues(parseFieldValues(VectorHelper::slice(queryTokens, 3)));

    return insertObject;
}

// <UPDATE-statement> ::= UPDATE <table name> SET <field name> = <field value> <WHERE-clause>
UpdateObject* QueryParser::parseUpdateQuery(vector<string> queryTokens) {
    if (
        queryTokens.size() < 7 ||
        QueryHelper::searchKeyWordInVector(queryTokens, "UPDATE") != 0 ||
        !LexicParser::isIdentifier(queryTokens[1]) ||
        QueryHelper::searchKeyWordInVector(queryTokens, "SET") != 2 ||
        !LexicParser::isIdentifier(queryTokens[3]) ||
        queryTokens[4] != "=" ||
        !LexicParser::isDataType(queryTokens[5])
    ) {
        throw QueryException("Wrong UPDATE query syntax");
    }

    TableField* field;
    DataType* value;

    if (LexicParser::isNumber(queryTokens[5])) {
        field = new TableField(queryTokens[3], DataTypeEnum::NUMBER);
        value = new Number(queryTokens[5]);
    } else {
        field = new TableField(queryTokens[3], DataTypeEnum::VARCHAR);
        value = new Varchar(queryTokens[5]);
    }

    int wherePosition = QueryHelper::searchKeyWordInVector(queryTokens, "WHERE");
    if (wherePosition == -1) {
        return new UpdateObject(queryTokens[1], field, value);
    } else if (wherePosition != 6) {
        throw QueryException("Wrong UPDATE query syntax");
    } else {
        BaseCondition* conditionTree = QueryParser::parseWhereClause(VectorHelper::slice(queryTokens, wherePosition));
        return new UpdateObject(queryTokens[1], field, value, conditionTree);
    }
}

// <DELETE-statement> ::= DELETE FROM <table name> <WHERE-clause>
DeleteObject* QueryParser::parseDeleteQuery(vector<string> queryTokens) {
    if (
        queryTokens.size() < 4 ||
        QueryHelper::searchKeyWordInVector(queryTokens, "FROM") != 1 ||
        !LexicParser::isIdentifier(queryTokens[2])
    ) {
        throw QueryException("Wrong DELETE query syntax");
    }
    
    return new DeleteObject(queryTokens[2], QueryParser::parseWhereClause(VectorHelper::slice(queryTokens, 3)));
}

// <CREATE-statement> ::= CREATE TABLE <table name> ( <fields description> )
CreateObject* QueryParser::parseCreateQuery(vector<string> queryTokens) {
    if (
        queryTokens.size() < 6 ||
        QueryHelper::searchKeyWordInVector(queryTokens, "TABLE") != 1 ||
        !LexicParser::isIdentifier(queryTokens[2]) ||
        queryTokens[3] != "("||
        queryTokens[queryTokens.size() - 1] != ")"
    ) {
        throw QueryException("Wrong CREATE query syntax");
    }
    
    return new CreateObject(queryTokens[2], QueryParser::parseFieldDescriptions(VectorHelper::slice(queryTokens, 4, queryTokens.size() - 2)));
}

// <DROP-statement> ::= DROP TABLE <table name>
DropObject* QueryParser::parseDropQuery(vector<string> queryTokens) {
    if (
        queryTokens.size() != 3 ||
        QueryHelper::searchKeyWordInVector(queryTokens, "TABLE") != 1 ||
        !LexicParser::isIdentifier(queryTokens[2])
    ) {
        throw QueryException("Wrong DROP query syntax");
    }
    
    return new DropObject(queryTokens[2]);
}

// <table row> ::= (<field value> { , <field value> })
vector<DataType*> QueryParser::parseFieldValues(vector<string> queryTokens) {
    if (
        QueryHelper::searchKeyWordInVector(queryTokens, "(") != 0 ||
        QueryHelper::searchKeyWordInVector(queryTokens, ")") != queryTokens.size() - 1
    ) {
        throw QueryException("Wrong INSERT query syntax for field values");
    }
    
    queryTokens = VectorHelper::slice(queryTokens, 1, queryTokens.size() - 2);
    vector<string> fieldValues = StringHelper::splitToVector(queryTokens[0], ',');
    vector<DataType*> dataTypeVector;
    
    for (int i = 0; i < fieldValues.size(); ++i) {
        if (LexicParser::isString(fieldValues[i])) {
            dataTypeVector.push_back(new Varchar(fieldValues[i]));
        } else if (LexicParser::isNumber(fieldValues[i])) {
            dataTypeVector.push_back(new Number(fieldValues[i]));
        } else {
            throw QueryException("Wrong INSERT query syntax for field values");
        }
    }
    
    return dataTypeVector;
}

// <fields description> ::= <field description> { , <field description> }
vector<TableField> QueryParser::parseFieldDescriptions(vector<string> queryTokens) {
    vector<string> currentTableInfo;
    vector<TableField> tableFieldVector;
    
    for (int i = 0; i < queryTokens.size(); ++i) {
        int commaPosition;
        
        if (queryTokens[i].find(',') == 0) {
            tableFieldVector.push_back(QueryParser::parseTableField(currentTableInfo));
            currentTableInfo.clear();
            currentTableInfo.push_back(queryTokens[i].erase(0, 1));
        } else if ((commaPosition = queryTokens[i].find(',')) != -1) {
            vector<string> tokenAsVector = StringHelper::splitToVector(queryTokens[i], ',');
            currentTableInfo.push_back(tokenAsVector[0]);
            tableFieldVector.push_back(QueryParser::parseTableField(currentTableInfo));
            currentTableInfo.clear();
            currentTableInfo.push_back(tokenAsVector[1]);
        } else {
            currentTableInfo.push_back(queryTokens[i]);
        }
    }
    
    tableFieldVector.push_back(QueryParser::parseTableField(currentTableInfo));
    
    return tableFieldVector;
}

// <field description> ::= <field name> <field type>
// <field type> ::= TEXT (<unsigned>) | NUMBER
TableField QueryParser::parseTableField(vector<string> queryTokens) {
    if (
        queryTokens.size() < 2 ||
        !LexicParser::isIdentifier(queryTokens[0])
    ) {
        throw QueryException("Invalid syntax for CREATE clause");
    }
    
    if (queryTokens[1] == "NUMBER" && queryTokens.size() == 2) {
        return TableField(queryTokens[0], DataTypeEnum::NUMBER);
    } else if (queryTokens[1] == "TEXT" && queryTokens.size() == 5) {
        if (
            QueryHelper::searchKeyWordInVector(queryTokens, "(") == 2 ||
            QueryHelper::searchKeyWordInVector(queryTokens, ")") == 4
        ) {
            // TODO: add queryTokens[3] to TableField* (which is length of VARCHAR)
            return TableField(queryTokens[0], DataTypeEnum::VARCHAR);
        }
    } else {
        throw QueryException("Invalid syntax for CREATE clause");
    }
    
}

// <WHERE-cluase> ::= WHERE <logic expression> | WHERE ALL
OrCondition* QueryParser::parseWhereClause(vector<string> queryTokens) {
    string command = queryTokens[0];
    StringHelper::toUpperCase(command);

    if (command != "WHERE") {
        throw QueryException("Invalid syntax for WHERE clause");
    }
    
    int andKeyWordIndex = QueryHelper::searchKeyWordInVector(queryTokens, "ALL");
    
    if (andKeyWordIndex == -1) {
        return QueryParser::parseLogicExpression(VectorHelper::slice(queryTokens, 1));
    } else if (andKeyWordIndex == 1) {
        return NULL;
    } else {
        throw QueryException("Invalid syntax for WHERE clause");
    }
}

// <logic expression> ::= <logic term> { OR <logic term> }
OrCondition* QueryParser::parseLogicExpression(vector<string> queryTokens) {
    cout << "Parsing logic expression: ";
    VectorHelper::print(queryTokens);
    
    if (
        StringHelper::getUpperString(queryTokens[0]) == "OR" ||
        StringHelper::getUpperString(queryTokens[queryTokens.size() - 1]) == "OR"
    ) {
        throw QueryException("Invalid syntax for WHERE clause: logic expression");
    }
    
    OrCondition* node = new OrCondition;

    for (int i = 0; i < queryTokens.size(); i++) {
        if (StringHelper::getUpperString(queryTokens[i]) == "OR" && !QueryHelper::isTokenNested(queryTokens, i)) {
            node->MultipleCondition::addOperand(QueryParser::parseLogicTerm(VectorHelper::slice(queryTokens, 0, i - 1)));
            queryTokens = VectorHelper::slice(queryTokens, i + 1);
            i = 0;
        }
    }

    node->MultipleCondition::addOperand(QueryParser::parseLogicTerm(queryTokens));
    
    return node;
}

// <logic term> ::= <logic factor> { AND <logic factor> }
AndCondition* QueryParser::parseLogicTerm(vector<string> queryTokens) {
    cout << "Parsing logic term: ";
    VectorHelper::print(queryTokens);
    
    if (
        StringHelper::getUpperString(queryTokens[0]) == "AND" ||
        StringHelper::getUpperString(queryTokens[queryTokens.size() - 1]) == "AND"
    ) {
        throw QueryException("Invalid syntax for WHERE clause: logic term");
    }
    
    AndCondition* node = new AndCondition;

    for (int i = 0; i < queryTokens.size(); i++) {
        if (StringHelper::getUpperString(queryTokens[i]) == "AND" && !QueryHelper::isTokenNested(queryTokens, i)) {
            node->MultipleCondition::addOperand(QueryParser::parseLogicFactor(VectorHelper::slice(queryTokens, 0, i - 1)));
            queryTokens = VectorHelper::slice(queryTokens, i + 1);
            i = 0;
        }
    }
    
    node->MultipleCondition::addOperand(QueryParser::parseLogicFactor(queryTokens));
    
    return node;
}

// <logic factor> ::= (NOT <logic factor>) | ((<logic expression>)) | <operation>
BaseCondition* QueryParser::parseLogicFactor(vector<string> queryTokens) {
    cout << "Parsing logic factor: ";
    VectorHelper::print(queryTokens);

    if (StringHelper::getUpperString(queryTokens[0]) == "NOT") {
        AndCondition* node = new AndCondition;
        node->NegatableCondition::negate();
        node->MultipleCondition::addOperand(QueryParser::parseLogicFactor(VectorHelper::slice(queryTokens, 1)));
        return node;
    } else if (queryTokens[0] == "(" && queryTokens[queryTokens.size() - 1] == ")") {
        return QueryParser::parseLogicExpression(VectorHelper::slice(queryTokens, 1, queryTokens.size() - 2));
    } else {
        return QueryParser::parseOperation(queryTokens);
    }
}

// <operation> ::= <relation> | <string operation> | <set operation>
BinaryCondition* QueryParser::parseOperation(vector<string> queryTokens) {
    cout << "Parsing operation: ";
    VectorHelper::print(queryTokens);
    
    if (
        QueryHelper::searchKeyWordInVector(queryTokens, "=") != -1 ||
        QueryHelper::searchKeyWordInVector(queryTokens, ">") != -1 ||
        QueryHelper::searchKeyWordInVector(queryTokens, "<") != -1
    ) {
        return QueryParser::parseRelation(queryTokens);
    } else if (QueryHelper::searchKeyWordInVector(queryTokens, "LIKE") != -1) {
       return QueryParser::parseLikeOperation(queryTokens);
    } else if (QueryHelper::searchKeyWordInVector(queryTokens, "IN") != -1) {
        return QueryParser::parseSetOperation(queryTokens);
    } else {
        throw QueryException("Invalid syntax for WHERE clause: operation");
    }
}

// <relation> ::= (<string expression> <comparasion operator> <string expression>) | (<number expression> <comparasion operation> <number expression>)
RelationCondition* QueryParser::parseRelation(vector<string> queryTokens) {
    cout << "Parsing relation: ";
    VectorHelper::print(queryTokens);
    
    string relationType;
    
    if (queryTokens.size() == 3) {
        if (
            QueryHelper::searchKeyWordInVector(queryTokens, "=") != 1 &&
            QueryHelper::searchKeyWordInVector(queryTokens, ">") != 1 &&
            QueryHelper::searchKeyWordInVector(queryTokens, "<") != 1
        ) {
            throw QueryException("Invalid syntax for WHERE clause: relation operation");
        }
        relationType = queryTokens[1];
    } else if (queryTokens.size() == 4) {
        if (QueryHelper::searchKeyWordInVector(queryTokens, "=") != 2) {
            throw QueryException("Invalid syntax for WHERE clause: relation operation");
        }
        if (
            QueryHelper::searchKeyWordInVector(queryTokens, "!") != 1 &&
            QueryHelper::searchKeyWordInVector(queryTokens, ">") != 1 &&
            QueryHelper::searchKeyWordInVector(queryTokens, "<") != 1
        ) {
            throw QueryException("Invalid syntax for WHERE clause: relation operation");
        }
        relationType = queryTokens[1] + queryTokens[2];
    } else {
        throw QueryException("Invalid syntax for WHERE clause: relation operation");
    }
    
    BaseOperand* operand1;
    BaseOperand* operand2;
    
    if (LexicParser::isIdentifier(queryTokens[0])) {
        operand1 = new TableFieldOperand(queryTokens[0]);
    } else if (LexicParser::isString(queryTokens[0])) {
        operand1 = new StringOperand(queryTokens[0]);
    } else if (LexicParser::isNumber(queryTokens[0])) {
        operand1 = new NumberOperand(stold(queryTokens[0]));
    } else {
        throw QueryException("Invalid syntax for WHERE clause: relation operation");
    }
    
    if (LexicParser::isIdentifier(queryTokens[queryTokens.size() - 1])) {
        operand2 = new TableFieldOperand(queryTokens[queryTokens.size() - 1]);
    } else if (LexicParser::isString(queryTokens[queryTokens.size() - 1])) {
        operand2 = new StringOperand(queryTokens[queryTokens.size() - 1]);
    } else if (LexicParser::isNumber(queryTokens[queryTokens.size() - 1])) {
        operand2 = new NumberOperand(stold(queryTokens[queryTokens.size() - 1]));
    } else {
        throw QueryException("Invalid syntax for WHERE clause: relation operation");
    }
    
    return new RelationCondition(operand1, operand2, relationType);
}

// <string operation> ::= <field> [ NOT ] LIKE <string>
LikeCondition* QueryParser::parseLikeOperation(vector<string> queryTokens) {
    cout << "Parsing like operation: ";
    VectorHelper::print(queryTokens);
    
    int notKeyWordIndex = QueryHelper::searchKeyWordInVector(queryTokens, "NOT");
    bool isNegated = notKeyWordIndex != -1;

    if (isNegated && notKeyWordIndex != 1) {
        throw QueryException("QueryParser::parseLikeOperation(): NOT keyword has wrong position");
    } else if (isNegated) {
        VectorHelper::removeByIndex(queryTokens, notKeyWordIndex);
    }

    if (
        queryTokens.size() != 3 ||
        QueryHelper::searchKeyWordInVector(queryTokens, "LIKE") != 1 ||
        !LexicParser::isIdentifier(queryTokens[0]) ||
        !LexicParser::isString(queryTokens[2])
    ) {
        throw QueryException("QueryParser::parseLikeOperation(): invalid syntax for LIKE condition");
    }
    
    return new LikeCondition(new TableFieldOperand(queryTokens[0]), new StringOperand(queryTokens[2]), isNegated);
}

// <set operation> ::= <field> [ NOT ] IN <set>
InCondition* QueryParser::parseSetOperation(vector<string> queryTokens) {
    cout << "Parsing set operation: ";
    VectorHelper::print(queryTokens);
    
    int notKeyWordIndex = QueryHelper::searchKeyWordInVector(queryTokens, "NOT");
    bool isNegated = (notKeyWordIndex != -1);
    
    if (isNegated && (notKeyWordIndex != 1)) {
        throw QueryException("QueryParser::parseSetOperation(): NOT keyword has wrong position");
    } else if (isNegated) {
        VectorHelper::removeByIndex(queryTokens, notKeyWordIndex);
    }
    
    if (
        queryTokens.size() < 5 ||
        QueryHelper::searchKeyWordInVector(queryTokens, "IN") != 1 ||
        !LexicParser::isIdentifier(queryTokens[0]) ||
        !LexicParser::isSet(queryTokens[3])
    ) {
        throw QueryException("QueryParser::parseSetOperation(): invalid syntax for IN condition");
    }
    
    BaseOperand* operandSet;
   
    if (queryTokens[3][0] == '\'') {
        return new InCondition(new TableFieldOperand(queryTokens[0]), new StringSetOperand(LexicParser::splitToStringSet(queryTokens[3], ',')), isNegated);
    } else {
        return new InCondition(new TableFieldOperand(queryTokens[0]), new NumberSetOperand(LexicParser::splitToNumberSet(queryTokens[3], ',')), isNegated);
    }
}
