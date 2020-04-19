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

using namespace std;

int main() {
    BaseOperand* fieldOperand = new TableFieldOperand("f2");
    BaseOperand* stringOperand = new StringOperand("qwerty");
    BaseCondition* condition = new RelationCondition(fieldOperand, stringOperand, "=");

    vector<TableField> fields;
    fields.push_back(TableField("f1", DataTypeEnum::NUMBER));
    fields.push_back(TableField("f2", DataTypeEnum::VARCHAR));
    fields.push_back(TableField("f3", DataTypeEnum::NUMBER));

    vector<DataType*> row;
    row.push_back(new Number("1"));
    row.push_back(new Varchar("'qwerty'"));
    row.push_back(new Number("145.5"));

    bool result = condition->calculate(fields, row);

    cout << result << endl;
}