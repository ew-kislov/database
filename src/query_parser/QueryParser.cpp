#pragma once

#include "QueryParser.h"

#include "StringHelper.cpp"
#include "VectorHelper.cpp"
#include "QueryHelper.cpp"

// <SQL-query> ::= (<SELECT-statement> | <INSERT -statement> | <UPDATE-statement> |
//                 <DELETE-statement> | <CREATE-statement> | <DROP-statement>);
QueryObject QueryParser::parseQuery(string query) {
    if (query.find(';') != query.size() - 1) {
        throw QueryException("Query must end with semicolon");
    }

    vector<string> queryTokens = QueryHelper::queryToTokenVector(query);
    queryTokens.pop_back();
    
    string command = StringHelper::getUpperString(queryTokens[0]);

    QueryObject queryObject;

    if (command == "SELECT") {
        queryObject = QueryParser::parseSelectQuery(queryTokens);
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
QueryObject QueryParser::parseSelectQuery(vector<string> queryTokens) {
    if (QueryHelper::searchKeyWordInVector(queryTokens, "FROM") == -1) {
        throw QueryException("Wrong SELECT query syntax");
    }

    QueryObject queryObject;
    queryObject.table = queryTokens[0];
    queryObject.fields = StringHelper::split(queryTokens[1], ',');
    queryObject.table = queryTokens[2];

    if (queryTokens.size() > 4) {
        QueryParser::parseWhereClause(VectorHelper::slice(queryTokens, 4), queryObject);
    }

    return queryObject;
}

// <WHERE-cluase> ::= WHERE <logic expression> | WHERE ALL
void QueryParser::parseWhereClause(vector<string> queryTokens, QueryObject &queryObject) {
    string command = queryTokens[0];
    StringHelper::toUpperCase(command);

    if (command != "WHERE") {
        throw QueryException("Invalid syntax for WHERE clause");
    }

    if (QueryHelper::searchKeyWordInVector(queryTokens, "ALL") == -1) {
        QueryParser::parseLogicExpression(VectorHelper::slice(queryTokens, 1), queryObject);
    }
}

// <logic expression> ::= <logic term> { OR <logic term> }
void QueryParser::parseLogicExpression(vector<string> queryTokens, QueryObject &queryObject) {
    cout << "Parsing logic expression: ";
    VectorHelper::print(queryTokens);
    
    if (StringHelper::getUpperString(queryTokens[0]) == "OR"
        || StringHelper::getUpperString(queryTokens[queryTokens.size() - 1]) == "OR") {
        throw QueryException("Invalid syntax for WHERE clause: logic expression");
    }

    for (int i = 0; i < queryTokens.size(); i++) {
        if (StringHelper::getUpperString(queryTokens[i]) == "OR" && !QueryHelper::isTokenNested(queryTokens, i)) {
            QueryParser::parseLogicTerm(VectorHelper::slice(queryTokens, 0, i - 1), queryObject);
            queryTokens = VectorHelper::slice(queryTokens, i + 1);
        }
    }

    QueryParser::parseLogicTerm(queryTokens, queryObject);
}

// <logic term> ::= <logic factor> { AND <logic factor> }
void QueryParser::parseLogicTerm(vector<string> queryTokens, QueryObject &queryObject) {
    cout << "Parsing logic term: ";
    VectorHelper::print(queryTokens);
    
    if (StringHelper::getUpperString(queryTokens[0]) == "AND"
        || StringHelper::getUpperString(queryTokens[queryTokens.size() - 1]) == "AND") {
        throw QueryException("Invalid syntax for WHERE clause: logic term");
    }

    for (int i = 0; i < queryTokens.size(); i++) {
        if (StringHelper::getUpperString(queryTokens[i]) == "AND" && !QueryHelper::isTokenNested(queryTokens, i)) {
            QueryParser::parseLogicFactor(VectorHelper::slice(queryTokens, 0, i - 1), queryObject);
            queryTokens = VectorHelper::slice(queryTokens, i + 1);
        }
    }

    QueryParser::parseLogicFactor(queryTokens, queryObject);
}

// <logic factor> ::= (NOT <logic factor>) | ((<logic expression>)) | <operation>
void QueryParser::parseLogicFactor(vector<string> queryTokens, QueryObject &queryObject) {
    cout << "Parsing logic factor: ";
    VectorHelper::print(queryTokens);

    if (StringHelper::getUpperString(queryTokens[0]) == "NOT") {
        QueryParser::parseLogicFactor(VectorHelper::slice(queryTokens, 1), queryObject);
    } else if (queryTokens[0] == "(" && queryTokens[queryTokens.size() - 1] == ")") {
        QueryParser::parseLogicExpression(VectorHelper::slice(queryTokens, 1, queryTokens.size() - 2), queryObject);
    } else {
        QueryParser::parseOperation(queryTokens, queryObject);
    }
}

// <operation> ::= <relation> | <string operation> | <set operation>
void QueryParser::parseOperation(vector<string> queryTokens, QueryObject &queryObject) {
    cout << "Parsing operation: ";
    VectorHelper::print(queryTokens);
    
    if (QueryHelper::searchKeyWordInVector(queryTokens, "=") != -1
        || QueryHelper::searchKeyWordInVector(queryTokens, ">") != -1
        || QueryHelper::searchKeyWordInVector(queryTokens, "<") != -1) {
        QueryParser::parseRelation(queryTokens, queryObject);
    } else if (QueryHelper::searchKeyWordInVector(queryTokens, "LIKE") != -1) {
        QueryParser::parseStringOperation(queryTokens, queryObject);
    } else if (QueryHelper::searchKeyWordInVector(queryTokens, "IN") != -1) {
        QueryParser::parseSetOperation(queryTokens, queryObject);
    } else {
        throw QueryException("Invalid syntax for WHERE clause: operation");
    }
}

// <relation> ::= (<string expression> <comparasion operator> <string expression>) | (<number expression> <comparasion operation> <number expression>)
void QueryParser::parseRelation(vector<string> queryTokens, QueryObject &queryObject) {
    cout << "Parsing relation: ";
    VectorHelper::print(queryTokens);
    
    // TODO: add operands type check (may be fields)
    
    if (queryTokens.size() == 3) {
        if (QueryHelper::searchKeyWordInVector(queryTokens, "=") != 1
            && QueryHelper::searchKeyWordInVector(queryTokens, ">") != 1
            && QueryHelper::searchKeyWordInVector(queryTokens, "<") != 1) {
            throw QueryException("Invalid syntax for WHERE clause: relation operation");
        }
    } else if (queryTokens.size() == 4) {
        if (QueryHelper::searchKeyWordInVector(queryTokens, "=") != 2) {
            throw QueryException("Invalid syntax for WHERE clause: relation operation");
        }
        if (QueryHelper::searchKeyWordInVector(queryTokens, "!") != 1
            && QueryHelper::searchKeyWordInVector(queryTokens, ">") != 1
            && QueryHelper::searchKeyWordInVector(queryTokens, "<") != 1) {
            throw QueryException("Invalid syntax for WHERE clause: relation operation");
        }
    } else {
        throw QueryException("Invalid syntax for WHERE clause: relation operation");
    }
}

// <string operation> ::= <field> [ NOT ] LIKE <string>
void QueryParser::parseStringOperation(vector<string> queryTokens, QueryObject &queryObject) {
    cout << "Parsing string operation: ";
    VectorHelper::print(queryTokens);
    
    if (QueryHelper::searchKeyWordInVector(queryTokens, "NOT") == -1) {
        if (!(QueryHelper::searchKeyWordInVector(queryTokens, "LIKE") == 1 && queryTokens.size() == 3)) {
            throw QueryException("Invalid syntax for WHERE clause: string operation");
        }
        if (!StringHelper::isString(queryTokens[2])) {
            throw QueryException("Invalid syntax for WHERE clause: string operation");
        }
    } else if (QueryHelper::searchKeyWordInVector(queryTokens, "NOT") != 1) {
        throw QueryException("Invalid syntax for WHERE clause: string operation");
    } else if (!(QueryHelper::searchKeyWordInVector(queryTokens, "LIKE") == 2 && queryTokens.size() == 4)) {
        throw QueryException("Invalid syntax for WHERE clause: string operation");
    } else if (!StringHelper::isString(queryTokens[3])) {
        throw QueryException("Invalid syntax for WHERE clause: string operation");
    }
}

// <set operation> ::= <field> [ NOT ] IN <set>
void QueryParser::parseSetOperation(vector<string> queryTokens, QueryObject &queryObject) {
    cout << "Parsing set operation: ";
    VectorHelper::print(queryTokens);
    
    if (QueryHelper::searchKeyWordInVector(queryTokens, "NOT") == -1) {
        if (QueryHelper::searchKeyWordInVector(queryTokens, "IN") != 1) {
            throw QueryException("Invalid syntax for WHERE clause: set operation");
        }
        if (!(QueryHelper::searchKeyWordInVector(queryTokens, "(") == 2
              && QueryHelper::searchKeyWordInVector(queryTokens, ")") == 4)) {
            throw QueryException("Invalid syntax for WHERE clause: set operation");
        }
        if (!StringHelper::isSet(queryTokens[3])) {
            throw QueryException("Invalid syntax for WHERE clause: set operation");
        }
    } else if (QueryHelper::searchKeyWordInVector(queryTokens, "NOT") != 1) {
        throw QueryException("Invalid syntax for WHERE clause: set operation");
    } else if (QueryHelper::searchKeyWordInVector(queryTokens, "IN") != 2) {
        throw QueryException("Invalid syntax for WHERE clause: set operation");
    } else if (!(QueryHelper::searchKeyWordInVector(queryTokens, "(") == 3
                 && QueryHelper::searchKeyWordInVector(queryTokens, ")") == 5)) {
        throw QueryException("Invalid syntax for WHERE clause: set operation");
    } else {
        if (!StringHelper::isSet(queryTokens[4])) {
            throw QueryException("Invalid syntax for WHERE clause: set operation");
        }
    }
}
