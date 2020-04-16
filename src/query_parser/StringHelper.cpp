#pragma once

#include <set>
#include <string>
#include <sstream>
#include <iostream>
#include <regex>

using namespace std;

namespace StringHelper {
    /*
     * Replaces substrings to specific string by regular expression
     * @param inpString - input string
     * @param patternString - string which contains regular expression
     * @param replacementString - string which will replace substrings selected by regular expression
     * @returns string with replaced pattern
     */
    void replace(string &inpString, string patternString, string replacementString) {
        regex pattern(patternString);
        string outString;
        outString.reserve(inpString.size());
        regex_replace(back_insert_iterator<string>(outString), inpString.cbegin(), inpString.cend(), pattern, replacementString);
        inpString = outString;
    }

    /*
     * Check if string matches regular expression
     * @param inpString - input string
     * @param patternString - string which contains regular expression
     * @returns string with replaced pattern
     */
    bool matches(string inpString, string patternString) {
        regex pattern(patternString);
        return regex_match(inpString, pattern);
    }

    /*
     * Splits string into string vector by char delimeter
     * @param inpString - input string
     * @param delimeter - char delimeneter
     * @returns vector of strings splitted by delimeter
     */
    vector<string> splitToVector(string inpString, char delimeter) {
        vector<string> stringVector;
        istringstream stringStream(inpString);
        string token;

        while (getline(stringStream, token, delimeter)) {
            stringVector.push_back(token);
        }

        return stringVector;
    }

    /*
     * Gets first word of string(all chars before space)
     * @param inpString - input string
     * @returns first word of string
     */ 
    string getFirstWord(string inpString) {
        return inpString.substr(0, inpString.find(" "));
    }

    /*
     * Removes first word from string(all chars before space)
     * @param inpString - input string
     */
    void removeFirstWord(string &inpString) {
        inpString = inpString.substr(inpString.find(" ") + 1);
    }

    /*
     * Makes all string chars upper case
     * @param inpString - input string
     */
    void toUpperCase(string &inpString) {
        transform(inpString.begin(), inpString.end(), inpString.begin(), ::toupper);
    }

    /*
     * Returns string with all chars in upper case
     * @param inpString - input string
     * @returns string with all chars in upper case
     */
    string getUpperString(string inpString) {
        transform(inpString.begin(), inpString.end(), inpString.begin(), ::toupper);
        return inpString;
    }

    /*
     * Checks if input string is a <string>
     * @param inpString - input string
     * @returns true if string is a <string>, false if not
     */
    bool isString(string &inpString) {
        if (inpString[0] == '\'' && inpString.find('\'', 1) == inpString.size() - 1 && inpString.size() > 2)
            return true;
        return false;
    }

    /*
     * Checks if input string is a table field
     * @param inpString - input string
     * @returns true if string is a field, false if not
     */
    bool isField(string &inpString) {
        if (inpString[0] != '\'' && inpString[inpString.size() - 1] != '\'' && inpString.size() > 0)
            return true;
        return false;
    }

    /*
     * Checks if input string is a number
     * @param inpString - input string
     * @returns true if string is a number, false if not
     */
    bool isNumber(string &inpString) {
        string::const_iterator iter = inpString.begin();
        while (iter != inpString.end() && (isdigit(*iter) || *iter == '.'))
            ++iter;
        return !inpString.empty() && iter == inpString.end();
    }

    /*
     * Checks if string is a set of elements of one type (without brackets)
     * @param inpString - input string
     * @return set if string is a set, empty set if not
     */
    bool isSet(string &inpString) {
        int occurrencesOfComa = std::count(inpString.begin(), inpString.end(), ',');
        vector<string> inpVector = StringHelper::splitToVector(inpString, ',');
        
        if (inpVector.size() != occurrencesOfComa + 1)
            return false;
        
        bool isElementString = StringHelper::isString(inpVector[0]);
        bool isElementNumber = StringHelper::isNumber(inpVector[0]);

        if (!isElementString && !isElementNumber)
            return false;

        for (int i = 1; i < inpVector.size(); ++i) {
            if (
                StringHelper::isString(inpVector[i]) != isElementString ||
                StringHelper::isNumber(inpVector[i]) != isElementNumber
            ) {
                return false;
            }
        }

        return true;
    }
}
