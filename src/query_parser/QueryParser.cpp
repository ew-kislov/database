#pragma once

#include "QueryParser.h"

#include "StringHelper.cpp"
#include "VectorHelper.cpp"
#include "QueryHelper.cpp"

// <SQL-query> ::= (<SELECT-statement> | <INSERT -statement> | <UPDATE-statement> |
//                 <DELETE-statement> | <CREATE-statement> | <DROP-statement>);
QueryObject QueryParser::parseQuery(string query) {
    if (query.find(';') != query.size() - 1) {
        // TODO: throw QueryParserException("Query must end with semicolon")
    }

    StringHelper::replace(query, "\\s*[,]\\s*", ",");
    StringHelper::replace(query, "\\s*\\s\\s*", " ");
    StringHelper::replace(query, "\\s*;\\s*", ";");
    StringHelper::replace(query, "\\s*=\\s*", "=");

    vector<string> queryVector = StringHelper::split(query, ' ');

    string command = queryVector[0];
    StringHelper::toUpperCase(command);

    QueryObject queryObject;

    if (command == "SELECT") {
        queryObject = QueryParser::parseSelectQuery(queryVector);
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
        // TODO: throw QueryParserException("Unknown command: " + command);
    }

    return queryObject;
}

// <SELECT-statement> ::= SELECT <field list> FROM <table name> [ <WHERE-clause> ]
QueryObject QueryParser::parseSelectQuery(vector<string> queryVector) {
    QueryObject queryObject;
    queryObject.table = queryVector[0];
    queryObject.fields = StringHelper::split(queryVector[1], ',');
    queryObject.table = queryVector[2];

    if (queryVector.size() > 4) {
        QueryParser::parseWhereClause(VectorHelper::slice(queryVector, 4), queryObject);
    }

    return queryObject;
}

// <WHERE-cluase> ::= WHERE <logic expression> | WHERE ALL
void QueryParser::parseWhereClause(vector<string> queryVector, QueryObject &queryObject) {
    VectorHelper::print(queryVector);

    string command = queryVector[0];
    StringHelper::toUpperCase(command);

    if (command != "WHERE") {
        // TODO: throw QueryParserException("Invalid syntax for WHERE clause");
    }

    if (QueryHelper::searchKeyWordInVector(queryVector, "ALL") == -1) {
        QueryParser::parseLogicExpression(queryVector, queryObject);
    }
}

// <logic expression> ::= <logic term> { OR <logic term> }
void QueryParser::parseLogicExpression(vector<string> queryVector, QueryObject &queryObject) {

}

// <logic term> ::= <logic factor> { AND <logic factor> }
void QueryParser::parseLogicTerm(vector<string> queryVector, QueryObject &queryObject) {

}

// <logic factor> ::= NOT <logic factor> | (<logic expression>) | <logic operation>
void QueryParser::parseLogicFactor(vector<string> queryVector, QueryObject &queryObject) {

}

// <logic operation> ::= <relation> | <string operation> | <set operation>
void QueryParser::parseLogicOperation(vector<string> queryVector, QueryObject &queryObject) {

}

// <relation> ::= (<string expression> <comparasion operation> <string expression>) | (<number expression> <comparasion operation> <number expression>)
void QueryParser::parseRelation(vector<string> queryVector, QueryObject &queryObject) {

}

// <string operation> ::= <field> [ NOT ] LIKE <string>
void QueryParser::parseStringOperation(vector<string> queryVector, QueryObject &queryObject) {

}

// <set operation> ::= <field> [ NOT ] IN <set>
void QueryParser::parseSetOperation(vector<string> queryVector, QueryObject &queryObject) {

}