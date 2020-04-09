#include "SocketException.h"

#include <iostream>
#include <exception>

SocketException::SocketException(const string & msg):message(msg){
}

const char * SocketException::what() const throw (){
   return message.c_str();
}

string SocketException::get_message() const {
    return message;
}

SocketException::~SocketException() throw() {
}
