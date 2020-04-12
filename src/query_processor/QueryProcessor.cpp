#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "QueryProcessor.h"

#include "../engine/Table.cpp"
#include "../engine/Engine.cpp"

#include "QueryObject.cpp"
#include "QueryTypeEnum.h"

#include "QueryResult.cpp"
#include "QueryStatusEnum.h"

using namespace std;

/*
 * Executes query
 * @params queryObject - object which contains parsed inforamtion about query
 * @returns QueryResult
 */
QueryResult QueryProcessor::executeQuery(QueryObject queryObject) {
    switch (queryObject.getType()) {
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
            return QueryResult(queryObject.getTable(), QueryStatusEnum::UnknownCommand, 0);
    }
}

/*
 * Executes SELECT query
 * @params queryObject - object which contains parsed inforamtion about query
 * @returns QueryResult
 */
QueryResult QueryProcessor::executeSelect(QueryObject queryObject) {
    Table table;

    try {
        table = Engine::loadTable(queryObject.getTable(), true);
    } catch(const exception& e) {
        // TODO: return error in QueryResult
        cout << "error" << endl;
    }

    // TODO filter by WHERE clause

    cout << (*(table.getRows()[0][1]) == "kuzya") << endl;
    cout << (*(table.getRows()[0][3]) == 4) << endl;

    return QueryResult(queryObject.getTable(), QueryStatusEnum::Success, 0);
}

// int main() {
//     // QueryObject queryObject;

//     // QueryProcessor::executeQuery(queryObject);
// }