#pragma once

#include "QueryResult.h"

QueryResult::QueryResult(string table, QueryStatusEnum status, int executionTime) {
    this->table = table;
    this->status = status;
    this->executionTime = executionTime;
}