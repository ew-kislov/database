#pragma once

#include "QueryParser.h"

QueryObject QueryParser::parse(string query) {
    // get first word of query(which is command)
    string command = query.substr(0, query.find(" "));
    // make command uppercase
    transform(command.begin(), command.end(),command.begin(), ::toupper);

    if (command == "SELECT") {
        // TODO: selectParser.parse(query)
    } else if (command == "INSERT") {
        // TODO: insertParser.parse(query)
    } else if (command == "UPDATE") {
        // TODO: updateParser.parse(query)
    } else if (command == "DELETE") {
        // TODO: deleteParser.parse(query)
    } else if (command == "CREATE") {
        // TODO: createParser.parse(query)
    } else if (command == "DROP") {
        // TODO: dropParser.parse(query)
    }
}