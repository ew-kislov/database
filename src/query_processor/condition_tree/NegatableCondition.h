#ifndef NEGATABLE_CONDITION_H
#define NEGATABLE_CONDITION_H

using namespace std;

class NegatableCondition {
    protected:
        bool isNegated;
    public:
        NegatableCondition(bool isNegated = false);
    
        bool negate();
        virtual string toString(int nestLevel = 1) = 0;
};

#endif
