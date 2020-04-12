#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <string>
#include <iostream>

using namespace std;

class DataType {
    protected:
        virtual void parse(string valueString);
    public:
        DataType(string valueString);

        virtual string toString();

        virtual bool operator == (const DataType &dataType) const;
        virtual bool operator == (const long double numberValue) const;
        virtual bool operator == (const string stringValue) const;

        virtual bool operator > (const DataType &dataType) const;
        virtual bool operator > (const long double numberValue) const;
        virtual bool operator > (const string stringValue) const;

        virtual bool operator < (const DataType &dataType) const;
        virtual bool operator < (const long double numberValue) const;
        virtual bool operator < (const string stringValue) const;

        virtual bool operator >= (const DataType &dataType) const;
        virtual bool operator >= (const long double numberValue) const;
        virtual bool operator >= (const string stringValue) const;

        virtual bool operator <= (const DataType &dataType) const;
        virtual bool operator <= (const long double numberValue) const;
        virtual bool operator <= (const string stringValue) const;

        virtual bool operator != (const DataType &dataType) const;
        virtual bool operator != (const long double numberValue) const;
        virtual bool operator != (const string stringValue) const;
};

#endif