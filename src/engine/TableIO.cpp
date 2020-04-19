#pragma once

#include <string>

#include "fcntl.h"
#include "unistd.h"

#include "TableField.cpp"
#include "Number.cpp"
#include "Varchar.cpp"
#include "DataType.cpp"
#include "DataTypeEnum.h"

#include "Config.h"

#include "EngineStatusEnum.h"
#include "EngineException.cpp"

using namespace std;

namespace TableIO {
    enum TableModeEnum {
        CREATE_WRITE_MODE = O_CREAT | O_WRONLY,
        READ_MODE = O_RDONLY,
        WRITE_MODE = O_WRONLY | O_APPEND,
        READ_WRITE_MODE = O_RDWR
    };

    /*
     * Opens table file with given given mode and returns its file decriptor
     * @param tableName - name of file
     * @param mode - file mode to be opened
     * @throws EngineException if file couldn't be created/opened
     * @returns file descriptor of new table
     */
    int getFD(string tableName, TableModeEnum mode) {
        int tableFd = open(
            (Config::STORAGE_LOCATION + tableName + Config::TABLE_FILE_EXTENSION).c_str(),
            mode,
            0666
        );

        if (tableFd == -1) {
            if (errno == EEXIST) {
                throw EngineException(EngineStatusEnum::TableAlreadyExists);
            } else if (errno == ENOENT) {
                throw EngineException(EngineStatusEnum::TableDoesNotExist);
            } else if (errno == EACCES) {
                throw EngineException(EngineStatusEnum::NoPermission);
            } else {
                throw EngineException(EngineStatusEnum::TableStructureCorrupted);
            }
        }

        return tableFd;
    }

    /*
     * Closes given file descriptor
     * @param tableFD - descriptor of given file
     * @throws EngineException if file couldn't be closed
     */
    void closeFD(int tableFD) {
        int result = close(tableFD);

        if (result == -1) {
            throw EngineException(EngineStatusEnum::InternalError);
        }
    }

    /*
     * Reads fields number of table
     * @param tableFD - file descriptor of table
     * @throws EngineException if couldn't read from file
     * @returns fields number
     */
    int readFieldsNumber(int tableFD) {
        int fieldsNumber;

        int result = read(tableFD, &fieldsNumber, sizeof(int));
        if (result <= 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }

        return fieldsNumber;
    }

    /*
     * Reads table field
     * @param tableFD - file descriptor of table
     * @throws EngineException if couldn't read from file
     * @returns pointer to table field
     */
    TableField* readTableField(int tableFD) {
        int fieldNameSize;
        char fieldName[Config::MAX_FIELD_NAME_SIZE];
        int fieldType;

        int result;

        result = read(tableFD, &fieldNameSize, sizeof(int));
        if (result <= 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }

        result = read(tableFD, &fieldName, fieldNameSize * sizeof(char));
        if (result <= 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }
        fieldName[fieldNameSize] = '\0';

        result = read(tableFD, &fieldType, sizeof(int));
        if (result <= 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }

        return new TableField(string(fieldName), static_cast<DataTypeEnum>(fieldType));
    }

    /*
     * Reads table value
     * @param tableFD - file descriptor of table
     * @param type - value type
     * @throws EngineException if couldn't read from file
     * @returns pointer to value
     */
    DataType* readTableValue(int tableFD, DataTypeEnum type) {
        int result;

        if (type == DataTypeEnum::NUMBER) {
            long double numberValue;

            result = read(tableFD, &numberValue, sizeof(long double));
            if (result <= 0) {
                throw EngineException(EngineStatusEnum::TableStructureCorrupted);
            }

            return new Number(numberValue);
        } else if (type == DataTypeEnum::VARCHAR) {
            char varcharValue[50]; // TODO: add length to varchar and pass TableField*
            int length;

            result = read(tableFD, &length, sizeof(int));
            result = read(tableFD, varcharValue, length * sizeof(char));

            if (result <= 0) {
                throw EngineException(EngineStatusEnum::TableStructureCorrupted);
            }

            varcharValue[length] = '\0';
            return new Varchar(varcharValue, false);
        }
    }

    /*
     * Writes table fields number
     * @param tableFD - file descriptor of table
     * @param fieldsNumber - fields number
     * @throws EngineException if couldn't write to file
     */
    void writeFieldsNumber(int tableFD, int fieldsNumber) {
        write(tableFD, &fieldsNumber, sizeof(int));
    }

    /*
     * Writes table field
     * @param tableFD - file descriptor of table
     * @param field
     * @throws EngineException if couldn't write to file
     */
    void writeTableField(int tableFD, TableField* field) {
        int fieldNameSize = field->getName().length();
        const char* fieldName = field->getName().c_str();
        int fieldType = field->getType();

        int result;

        result = write(tableFD, &fieldNameSize, sizeof(int));
        if (result <= 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }

        result = write(tableFD, fieldName, fieldNameSize * sizeof(char));
        if (result <= 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }

        result = write(tableFD, &fieldType, sizeof(int));
        if (result <= 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }
    }

    /*
     * Writes table value
     * @param tableFD - file descriptor of table
     * @param value
     * @throws EngineException if couldn't write to file
     */
    void writeTableValue(int tableFD, DataType* value) {
        int result;

        if (value->getType() == DataTypeEnum::NUMBER) {
            Number* number = dynamic_cast<Number*>(value);
            long double numberValue = number->getValue();

            result = write(tableFD, &numberValue, sizeof(long double));

            if (result <= 0) {
                throw EngineException(EngineStatusEnum::TableStructureCorrupted);
            }
        } else if (value->getType() == DataTypeEnum::VARCHAR) {
            Varchar* varchar = dynamic_cast<Varchar*>(value);
            string varcharValue = varchar->getValue();
            int length = varcharValue.size();

            result = write(tableFD, &length, sizeof(int));
            if (result <= 0) {
                throw EngineException(EngineStatusEnum::TableStructureCorrupted);
            }

            result = write(tableFD, varcharValue.c_str(), length * sizeof(char));
            if (result <= 0) {
                throw EngineException(EngineStatusEnum::TableStructureCorrupted);
            }
        }
    }
}