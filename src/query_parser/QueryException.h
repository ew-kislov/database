#ifndef QUERY_EXCEPTION_H
#define QUERY_EXCEPTION_H

#include "QueryStatusEnum.h"

#include <exception>
#include <string>

using namespace std;

class QueryException: public std::exception {
protected:
    QueryStatusEnum status;
public:
    QueryException(QueryStatusEnum status);
    const char * what() const throw ();
        
    ~QueryException() throw();
};

#endif
