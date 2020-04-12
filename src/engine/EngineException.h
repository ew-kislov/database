  
#ifndef ENGINE_EXCEPTION_H
#define ENGINE_EXCEPTION_H

#include <string>
#include <exception>

using namespace std;

class EngineException: public std::exception {
    protected:
        string message;
    public:
        EngineException(string message);

        const char* what() const throw();
        
        ~EngineException() throw();
};

#endif