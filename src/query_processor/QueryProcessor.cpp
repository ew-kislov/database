#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "QueryProcessor.h"

#include "../engine/Table.cpp"
#include "../engine/Engine.cpp"

#include "QueryObject.cpp"
#include "QueryTypeEnum.h"

#include "condition_tree/BaseCondition.h"
#include "condition_tree/BinaryCondition.cpp"
#include "condition_tree/InCondition.cpp"
#include "condition_tree/BaseOperand.cpp"
#include "condition_tree/TableFieldOperand.cpp"
#include "condition_tree/NumberSetOperand.cpp"

// #include "QueryResult.cpp"
// #include "QueryStatusEnum.h"

using namespace std;

/*
 * Executes query
 * @params queryObject - object which contains parsed inforamtion about query
 * @returns string
 */
string QueryProcessor::executeQuery(QueryObject* queryObject) {
    switch (queryObject->getType()) {
        case QueryTypeEnum::Select:
            return executeSelect(queryObject);
        case QueryTypeEnum::Insert:
            // TODO
        case QueryTypeEnum::Update:
            // TODO
        case QueryTypeEnum::Delete:
            // TODO
        case QueryTypeEnum::Create:
            // TODO
        case QueryTypeEnum::Drop:
            // TODO
        default:
            throw "shit";
    }
}

/*
 * Executes SELECT query
 * @params queryObject - object which contains parsed inforamtion about query
 * @returns string
 */
string QueryProcessor::executeSelect(QueryObject* queryObject) {
    Table table = Engine::loadTable(queryObject->getTable(), true);

    // TODO: filter by WHERE clause

    return table.toString();
}