#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include <vector>
#include <string>

#include "QueryObject.h"

namespace QueryParser {
    QueryObject parseQuery(string query);

    QueryObject parseSelectQuery(vector<string> queryTokens);
    QueryObject parseInsertQuery(vector<string> queryTokens);
    QueryObject parseUpdateQuery(vector<string> queryTokens);
    QueryObject parseDeleteQuery(vector<string> queryTokens);
    QueryObject parseCreateQuery(vector<string> queryTokens);
    QueryObject parseDropQuery(vector<string> queryTokens);

    void parseWhereClause(vector<string> queryTokens, QueryObject &queryObject);
    void parseLogicExpression(vector<string> queryTokens, QueryObject &queryObject);
    void parseLogicTerm(vector<string> queryTokens, QueryObject &queryObject);
    void parseLogicFactor(vector<string> queryTokens, QueryObject &queryObject);
    void parseOperation(vector<string> queryTokens, QueryObject &queryObject);
    void parseRelation(vector<string> queryTokens, QueryObject &queryObject);
    void parseStringOperation(vector<string> queryTokens, QueryObject &queryObject);
    void parseSetOperation(vector<string> queryTokens, QueryObject &queryObject);
}

#endif