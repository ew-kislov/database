#ifndef VARCHAR_H
#define VARCHAR_H

#include <string>

#include "DataType.h"

using namespace std;

class Varchar: public DataType {
    protected:
        string value;
        int maxLength;

        void parse(string valueString);
    public:
        Varchar(string valueString);

        string toString();

        bool operator == (const Varchar &varchar) const;
        bool operator == (const string stringValue) const;

        virtual bool operator > (const Varchar &varchar) const;
        virtual bool operator > (const string stringValue) const;

        virtual bool operator < (const Varchar &varchar) const;
        virtual bool operator < (const string stringValue) const;

        virtual bool operator >= (const Varchar &varchar) const;
        virtual bool operator >= (const string stringValue) const;

        virtual bool operator <= (const Varchar &varchar) const;
        virtual bool operator <= (const string stringValue) const;

        virtual bool operator != (const Varchar &varchar) const;
        virtual bool operator != (const string varchar) const;
};

#endif