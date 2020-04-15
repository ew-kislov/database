#ifndef QUERY_EXCEPTION_H
#define QUERY_EXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class QueryException: public std::exception {
protected:
    string message;
public:
    QueryException(string msg);
    const char * what() const throw ();
        
    ~QueryException() throw();
};

#endif
