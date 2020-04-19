#pragma once

#include "QueryParser.h"

#include "../shared/StringHelper.cpp"
#include "../shared/LexicParser.cpp"
#include "../shared/VectorHelper.cpp"
#include "QueryHelper.cpp"

#include "../query_processor/QueryObject.cpp"
#include "../query_processor/SelectObject.cpp"

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
    
    QueryObject * queryObject;

    if (command == "SELECT") {
        SelectObject selectObject = QueryParser::parseSelectQuery(queryTokens);
        cout << endl;
        cout << selectObject.treeRoot->toString();
        queryObject = &selectObject;
    } else if (command == "INSERT") {
        // TODO: InsertParser::parse(query);
    } else if (command == "UPDATE") {
        // TODO: UpdateParser::parse(query);
    } else if (command == "DELETE") {
        // TODO: DeleteParser::parse(query);
    } else if (command == "CREATE") {
        // TODO: CreateParser::parse(query);
    } else if (command == "DROP") {
        // TODO: DropParser::parse(query);
    } else {
        throw QueryException("Unknown command: " + command);
    }

    return queryObject;
}

// <SELECT-statement> ::= SELECT <field list> FROM <table name> [ <WHERE-clause> ]
SelectObject QueryParser::parseSelectQuery(vector<string> queryTokens) {
    if (QueryHelper::searchKeyWordInVector(queryTokens, "FROM") != 2 || queryTokens.size() < 4) {
        throw QueryException("Wrong SELECT query syntax");
    }
    
    vector<string> fields = StringHelper::splitToVector(queryTokens[1], ',');

    SelectObject queryObject(queryTokens[3], fields);

    if (queryTokens.size() > 4) {
        queryObject.treeRoot = QueryParser::parseWhereClause(VectorHelper::slice(queryTokens, 4));
    }

    return queryObject;
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
        cout << QueryParser::parseLogicExpression(VectorHelper::slice(queryTokens, 1))->toString() << endl;
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
    
    if (LexicParser::isField(queryTokens[0])) {
        operand1 = new TableFieldOperand(queryTokens[0]);
    } else if (LexicParser::isString(queryTokens[0])) {
        operand1 = new StringOperand(queryTokens[0]);
    } else if (LexicParser::isNumber(queryTokens[0])) {
        operand1 = new NumberOperand(stold(queryTokens[0]));
    } else {
        throw QueryException("Invalid syntax for WHERE clause: relation operation");
    }
    
    if (LexicParser::isField(queryTokens[queryTokens.size() - 1])) {
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
        !LexicParser::isField(queryTokens[0]) ||
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
        !LexicParser::isField(queryTokens[0]) ||
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
