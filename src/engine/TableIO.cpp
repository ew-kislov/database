#pragma once

#include <string>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "TableField.cpp"
#include "NumberField.cpp"
#include "VarcharField.cpp"

#include "DataType.cpp"
#include "Number.cpp"
#include "Varchar.cpp"

#include "DataTypeEnum.h"

#include "Config.h"

#include "EngineStatusEnum.h"
#include "EngineException.cpp"

using namespace std;

namespace TableIO {
    enum TableModeEnum {
        CREATE_WRITE_MODE = O_CREAT | O_EXCL | O_WRONLY,
        READ_MODE = O_RDONLY,
        WRITE_MODE = O_WRONLY | O_APPEND,
        READ_WRITE_MODE = O_RDWR
    };

    enum SeekWhence {
        START_WHENCE = SEEK_SET,
        CURRENT_WHENCE = SEEK_CUR,
        END_WHENCE = SEEK_END
    };

    int lastReadBytes = 0;

    /*
     * moves file pointer by given offset using given whence
     * @param tableFD - descriptor of given table
     * @param whence - whence mode
     * @param offset - offset the pointer will be moved
     */
    void seek(int tableFD, SeekWhence whence, int offset) {
        int result = lseek(tableFD, offset, SEEK_CUR);
        if (result == -1) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }
    }

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
            0777
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
            throw EngineException(EngineStatusEnum::BadTableDescriptor);
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
    TableField* readTableField(int tableFD, int& bytesRead) {
        bytesRead = 0;

        int nameLength;
        char name[TableField::MAX_FIELD_LENGTH];
        DataTypeEnum type;

        int result;

        result = read(tableFD, &nameLength, sizeof(int));
        if (result < 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }
        bytesRead += result;

        result = read(tableFD, &name, nameLength * sizeof(char));
        if (result < 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }
        bytesRead += result;
        name[nameLength] = '\0';

        result = read(tableFD, &type, sizeof(int));
        if (result < 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }
        bytesRead += result;

        switch (type) {
            case DataTypeEnum::NUMBER: {
                return new NumberField(name);
            }
            case DataTypeEnum::VARCHAR: {
                int length;
                result = read(tableFD, &length, sizeof(int));
                if (result < 0) {
                    throw EngineException(EngineStatusEnum::TableStructureCorrupted);
                }
                bytesRead += result;
                return new VarcharField(name, length);
            }
            default:
                cout << "readTableField" << endl;
                throw EngineException(EngineStatusEnum::WrongFieldType);
        }
    }

    /*
     * Reads table value
     * @param tableFD - file descriptor of table
     * @param type - value type
     * @throws EngineException if couldn't read from file
     * @returns pointer to value
     */
    DataType* readTableValue(int tableFD, TableField* field, int& bytesRead = lastReadBytes) {
        int result;
        bytesRead = 0;

        switch (field->getType()) {
            case DataTypeEnum::NUMBER: {
                long double numberValue;

                result = read(tableFD, &numberValue, sizeof(long double));
                if (result <= 0) {
                    throw EngineException(EngineStatusEnum::TableStructureCorrupted);
                }

                bytesRead += result;
                return new Number(numberValue);
            }
            case DataTypeEnum::VARCHAR: {
                VarcharField* varcharField = dynamic_cast<VarcharField*>(field);

                char varcharValue[varcharField->getLength()];
                int length;

                result = read(tableFD, &length, sizeof(int));
                if (result <= 0) {
                    throw EngineException(EngineStatusEnum::TableStructureCorrupted);
                }
                bytesRead += result;

                result = read(tableFD, varcharValue, varcharField->getLength() * sizeof(char));
                if (result <= 0) {
                    throw EngineException(EngineStatusEnum::TableStructureCorrupted);
                }
                bytesRead += result;

                varcharValue[length] = '\0';
                return new Varchar(varcharValue, false);
            }
            default:
                throw EngineException(EngineStatusEnum::WrongValueType);
        }
    }

    bool readRowDeletedFlag(int tableFD, int& bytesRead = lastReadBytes) {
        bool deleted;
        bytesRead = read(tableFD, &deleted, sizeof(bool));
        return deleted;
    }

    /*
     * Writes table fields number
     * @param tableFD - file descriptor of table
     * @param fieldsNumber - fields number
     * @throws EngineException if couldn't write to file
     */
    int writeFieldsNumber(int tableFD, int fieldsNumber) {
        int result = write(tableFD, &fieldsNumber, sizeof(int));
        if (result <= 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }
        return result;
    }

    /*
     * Writes table field
     * @param tableFD - file descriptor of table
     * @param field
     * @throws EngineException if couldn't write to file
     */
    void writeTableField(int tableFD, TableField* field) {
        int nameLength = field->getName().length();
        const char* name = field->getName().c_str();
        int type = field->getType();

        int result;

        result = write(tableFD, &nameLength, sizeof(int));
        if (result < 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }

        result = write(tableFD, name, nameLength * sizeof(char));
        if (result < 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }

        result = write(tableFD, &type, sizeof(int));
        if (result < 0) {
            throw EngineException(EngineStatusEnum::TableStructureCorrupted);
        }

        switch (field->getType()) {
            case DataTypeEnum::NUMBER:
                break;
            case DataTypeEnum::VARCHAR: {
                VarcharField* varcharField = dynamic_cast<VarcharField*>(field);
                int length = varcharField->getLength();

                result = write(tableFD, &length, sizeof(int));
                if (result < 0) {
                    throw EngineException(EngineStatusEnum::TableStructureCorrupted);
                }

                break;
            }
            default:
                cout << "writeTableField " << name << " " << type << endl;
                throw EngineException(EngineStatusEnum::WrongFieldType);
        }
    }

    /*
     * Writes table value
     * @param tableFD - file descriptor of table
     * @param value
     * @throws EngineException if couldn't write to file
     */
    void writeTableValue(int tableFD, TableField* field, DataType* value) {
        int result;

        switch (value->getType()) {
            case DataTypeEnum::NUMBER: {
                Number* number = dynamic_cast<Number*>(value);
                long double numberValue = number->getValue();

                result = write(tableFD, &numberValue, sizeof(long double));

                if (result <= 0) {
                    throw EngineException(EngineStatusEnum::TableStructureCorrupted);
                }

                break;
            }
            case DataTypeEnum::VARCHAR: {
                Varchar* varchar = dynamic_cast<Varchar*>(value);
                VarcharField* varcharField = dynamic_cast<VarcharField*>(field);

                string varcharValue = varchar->getValue();
                int length = varcharValue.size();

                if (length > varcharField->getLength()) {
                    throw EngineException(EngineStatusEnum::VarcharValueTooLong);
                }

                result = write(tableFD, &length, sizeof(int));
                if (result <= 0) {
                    throw EngineException(EngineStatusEnum::TableStructureCorrupted);
                }

                varcharValue += string(varcharField->getLength() - length, ' ');
                result = write(tableFD, varcharValue.c_str(), varcharField->getLength() * sizeof(char));
                if (result <= 0) {
                    throw EngineException(EngineStatusEnum::TableStructureCorrupted);
                }

                break;
            }
            default:
                throw EngineException(EngineStatusEnum::WrongTableValueType);
        }
    }

    /*
     * Writes to table file "deleted" flag for row
     * @param tableFD - file descriptor of table
     * @param deleted - "deleted" flag
     * @throws EngineException
     */
    void writeRowDeletedFlag(int tableFD, bool deleted) {
        write(tableFD, &deleted, sizeof(bool));
    }

    /*
     * Deletes file that contains given table
     * @param tableName - table name
     * @throws EngineException
     */
    void deleteTable(string tableName) {
        int result = remove((Config::STORAGE_LOCATION + tableName + Config::TABLE_FILE_EXTENSION).c_str());
        if (result != 0) {
            throw EngineException(EngineStatusEnum::TableDoesNotExist);
        }
    }
}