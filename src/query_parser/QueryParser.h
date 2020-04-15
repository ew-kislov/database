#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include <vector>
#include <string>

#include "../query_processor/QueryObject.h"
#include "../query_processor/QueryObject.cpp"
#include "../query_processor/SelectObject.h"
#include "../query_processor/SelectObject.cpp"
//#include "../query_processor/condition_tree/BaseCondition.h"
#include "../query_processor/condition_tree/OrCondition.h"
#include "../query_processor/condition_tree/AndCondition.h"
#include "../query_processor/condition_tree/RelationCondition.h"
#include "../query_processor/condition_tree/LikeCondition.h"
#include "../query_processor/condition_tree/InCondition.h"

#include "../query_processor/condition_tree/BaseOperand.h"


namespace QueryParser {
    QueryObject* parseQuery(string query);

    SelectObject parseSelectQuery(vector<string> queryTokens);
    QueryObject parseInsertQuery(vector<string> queryTokens);
    QueryObject parseUpdateQuery(vector<string> queryTokens);
    QueryObject parseDeleteQuery(vector<string> queryTokens);
    QueryObject parseCreateQuery(vector<string> queryTokens);
    QueryObject parseDropQuery(vector<string> queryTokens);

    OrCondition* parseWhereClause(vector<string> queryTokens);
    OrCondition* parseLogicExpression(vector<string> queryTokens);
    AndCondition* parseLogicTerm(vector<string> queryTokens);
    AndCondition* parseLogicFactor(vector<string> queryTokens);
    BinaryCondition* parseOperation(vector<string> queryTokens);
    RelationCondition* parseRelation(vector<string> queryTokens);
    LikeCondition* parseStringOperation(vector<string> queryTokens);
    InCondition* parseSetOperation(vector<string> queryTokens);
}

#endif
