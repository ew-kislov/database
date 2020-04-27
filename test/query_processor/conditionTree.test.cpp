#include "../../src/query_processor/QueryObject.cpp"
#include "../../src/query_processor/SelectObject.cpp"

#include "../../src/query_processor/condition_tree/NegatableCondition.cpp"
#include "../../src/query_processor/condition_tree/OrCondition.cpp"
#include "../../src/query_processor/condition_tree/AndCondition.cpp"
#include "../../src/query_processor/condition_tree/MultipleCondition.cpp"
#include "../../src/query_processor/condition_tree/BinaryCondition.cpp"
#include "../../src/query_processor/condition_tree/InCondition.cpp"
#include "../../src/query_processor/condition_tree/RelationCondition.cpp"
#include "../../src/query_processor/condition_tree/LikeCondition.cpp"

#include "../../src/query_processor/condition_tree/BaseOperand.cpp"
#include "../../src/query_processor/condition_tree/NumberSetOperand.cpp"
#include "../../src/query_processor/condition_tree/StringSetOperand.cpp"
#include "../../src/query_processor/condition_tree/NumberOperand.cpp"
#include "../../src/query_processor/condition_tree/StringOperand.cpp"
#include "../../src/query_processor/condition_tree/TableFieldOperand.cpp"

#include <iostream>
#include <set>

using namespace std;

template<typename T> string rowToString(vector<T> object) {
    string message;
    message += "Fields: {\n";
    for (int i = 0; i < object.size(); ++i) {
        message += "   " + object[i]->toString();
        if (i != object.size() - 1) {
            message += ",";
        }
        
        message += "\n";
    }
    
    message += "}\n\n";
    return message;
}

template<typename T> string fieldsToString(vector<T> object) {
    string message;
    message += "Fields: {\n";
    for (int i = 0; i < object.size(); ++i) {
        message += "   " + object[i].toString();
        if (i != object.size() - 1) {
            message += ",";
        }
        
        message += "\n";
    }

    message += "}\n\n";
    return message;
}

void testRelationCondition() {
    vector<TableField> fields;
    fields.push_back(TableField("f1", DataTypeEnum::NUMBER));
    fields.push_back(TableField("f2", DataTypeEnum::VARCHAR));
    fields.push_back(TableField("f3", DataTypeEnum::NUMBER));

    vector<DataType*> row;
    row.push_back(new Number("1"));
    row.push_back(new Varchar("'qwerty'"));
    row.push_back(new Number("145.5"));
    
    cout << fieldsToString(fields);
    cout << rowToString(row);
    
    BaseOperand* fieldOperand = new TableFieldOperand("f2");
    BaseOperand* stringOperand = new StringOperand("qwerty");
    BaseCondition* condition = new RelationCondition(fieldOperand, stringOperand, "=");

    bool result = condition->calculate(fields, row);

    cout << condition->toString();
    cout << result << endl << endl;
}

void testInCondition() {
    vector<TableField> fields;
    fields.push_back(TableField("f1", DataTypeEnum::NUMBER));
    fields.push_back(TableField("f2", DataTypeEnum::VARCHAR));
    fields.push_back(TableField("f3", DataTypeEnum::NUMBER));

    vector<DataType*> row;
    row.push_back(new Number("1"));
    row.push_back(new Varchar("'qwerty'"));
    row.push_back(new Number("145.5"));
    
    cout << fieldsToString(fields);
    cout << rowToString(row);
    
    BaseOperand* fieldOperand = new TableFieldOperand("f1");
    set<long double> numberSetValue;
    numberSetValue.insert(10);
    numberSetValue.insert(6);
    numberSetValue.insert(28);
    BaseOperand* numberSetOperand = new NumberSetOperand(numberSetValue);
    BaseCondition* condition = new InCondition(fieldOperand, numberSetOperand);
        
    bool result = condition->calculate(fields, row);

    cout << condition->toString();
    cout << result << endl << endl;
    
    numberSetValue.insert(1);
    delete(numberSetOperand);
    delete(condition);
    numberSetOperand = new NumberSetOperand(numberSetValue);
    condition = new InCondition(fieldOperand, numberSetOperand);
    
    result = condition->calculate(fields, row);

    cout << condition->toString();
    cout << result << endl << endl;
}

int main() {
    
    testRelationCondition();
//    testLikeCondition();
    testInCondition();
    
    
}
