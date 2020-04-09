#pragma once

#include "QueryParser.h"

#include "SelectParser.cpp"
#include "StringHelper.cpp"

QueryObject QueryParser::parse(string query) {
    StringHelper::removeSpaces(query);

    string command = StringHelper::getFirstWord(query); 
    StringHelper::toUpperCase(command);

    StringHelper::removeFirstWord(query);

    if (command == "SELECT") {
        SelectParser::parse(query);
    } else if (command == "INSERT") {
        // TODO: InsertParser.parse(query);
    } else if (command == "UPDATE") {
        // TODO: UpdateParser.parse(query);
    } else if (command == "DELETE") {
        // TODO: DeleteParser.parse(query);
    } else if (command == "CREATE") {
        // TODO: CreateParser.parse(query);
    } else if (command == "DROP") {
        // TODO: DropParser.parse(query);
    } else {
        // TODO: throw QueryException("Unknown command: " + command);
    }
}