#include "QueryException.h"
#include "QueryStatusStrings.h"

#include <iostream>
#include <exception>

QueryException::QueryException(QueryStatusEnum status): status(status) {
}

const char * QueryException::what() const throw () {
    string message = "Query Exception: " + queryStatusStrings[static_cast<int>(this->status)] + "\n";
    return message.c_str();
}

QueryException::~QueryException() throw() {
}
