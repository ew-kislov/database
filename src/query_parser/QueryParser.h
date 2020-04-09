#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include <vector>
#include <string>

#include "QueryObject.h"

namespace QueryParser {
    QueryObject parseQuery(string query);

    QueryObject parseSelectQuery(vector<string> queryVector);
    QueryObject parseInsertQuery(vector<string> queryVector);
    QueryObject parseUpdateQuery(vector<string> queryVector);
    QueryObject parseDeleteQuery(vector<string> queryVector);
    QueryObject parseCreateQuery(vector<string> queryVector);
    QueryObject parseDropQuery(vector<string> queryVector);

    void parseWhereClause(vector<string> queryVector, QueryObject &queryObject);
    void parseLogicExpression(vector<string> queryVector, QueryObject &queryObject);
    void parseLogicTerm(vector<string> queryVector, QueryObject &queryObject);
    void parseLogicFactor(vector<string> queryVector, QueryObject &queryObject);
    void parseLogicOperation(vector<string> queryVector, QueryObject &queryObject);
    void parseRelation(vector<string> queryVector, QueryObject &queryObject);
    void parseStringOperation(vector<string> queryVector, QueryObject &queryObject);
    void parseSetOperation(vector<string> queryVector, QueryObject &queryObject);
}

#endif