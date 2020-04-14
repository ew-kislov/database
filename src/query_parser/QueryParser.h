#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include <vector>
#include <string>

#include "../query_processor/QueryObject.h"
#include "../query_processor/QueryObject.cpp"
#include "../query_processor/SelectObject.h"
#include "../query_processor/SelectObject.cpp"
#include "../query_processor/condition_tree/BaseCondition.h"
#include "../query_processor/condition_tree/OrCondition.h"
#include "../query_processor/condition_tree/AndCondition.h"
#include "../query_processor/condition_tree/InCondition.h"
// add LikeCondition

namespace QueryParser {
    QueryObject* parseQuery(string query);

    SelectObject parseSelectQuery(vector<string> queryTokens);
    QueryObject parseInsertQuery(vector<string> queryTokens);
    QueryObject parseUpdateQuery(vector<string> queryTokens);
    QueryObject parseDeleteQuery(vector<string> queryTokens);
    QueryObject parseCreateQuery(vector<string> queryTokens);
    QueryObject parseDropQuery(vector<string> queryTokens);

    void parseWhereClause(vector<string> queryTokens, BaseCondition * treeRoot);
    void parseLogicExpression(vector<string> queryTokens, BaseCondition * treeRoot);
    void parseLogicTerm(vector<string> queryTokens, BaseCondition * treeRoot);
    void parseLogicFactor(vector<string> queryTokens, BaseCondition * treeRoot);
    void parseOperation(vector<string> queryTokens, BaseCondition * treeRoot);
    void parseRelation(vector<string> queryTokens, BaseCondition * treeRoot);
    void parseStringOperation(vector<string> queryTokens, BaseCondition * treeRoot);
    void parseSetOperation(vector<string> queryTokens, BaseCondition * treeRoot);
}

#endif
