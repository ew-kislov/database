#ifndef QUERY_TREE_H
#define QUERY_TREE_H

#include <map>
#include <vector>

using namespace std;


enum OperandType {NODE, DOUBLE, STRING, SET};

enum RelationType {EQ, NEQ, GREATER, EQGREATER, LESS, EQLESS};


template <typename T>
class Operand {
protected:
    OperandType operandType;
    T value;
};


class BaseOperation {
public:
    virtual bool calculate(map<string, Operand> dictionary) = 0;
};


class BinaryOperation: public BaseOperation {
protected:
    Operand operand1, operand2;
};


class MultiOperandOperation: public BaseOperation {
protected:
    vector<BaseOperation> operands;
};


class OperationIn: public BinaryOperation {
public:
    bool calculate(map<string, OperandType> dictionary);
};


class OperationLike: public BinaryOperation {
public:
    bool calculate(map<string, OperandType> dictionary);
};


class OperationRelate: public BinaryOperation {
protected:
    RelationType relationType;
public:
    bool calculate(map<string, OperandType> dictionary);
};


class OperationAnd: public MultiOperandOperation {
public:
    bool calculate(map<string, OperandType> dictionary) {
        bool result = true;
        for (BaseOperation operation : operands)
            result = result && operation.calculate(map<string, OperandType> dictionary);
        return result;
    }
};


class OperationOr: public MultiOperandOperation {
public:
    bool calculate(map<string, OperandType> dictionary);
};


#endif
