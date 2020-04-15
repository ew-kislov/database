#include "QueryException.h"

#include <iostream>
#include <exception>

QueryException::QueryException(string msg):message(msg) {
}

const char * QueryException::what() const throw () {
    return message.c_str();
}

QueryException::~QueryException() throw() {
}
