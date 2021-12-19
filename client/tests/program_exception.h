#ifndef PROGRAMEXCEPTION_H
#define PROGRAMEXCEPTION_H

#include <QException>
#include <QFileInfo>
#include <QMessageBox>

enum ErrorsNames
{
    INVALID_INPUT,
    INVALID_KEY,
    FILE_EXIST_ERROR,
    FILE_READ_ERROR,
    FILE_WRITE_ERROR,
    INVALID_ADDRESS,
    ADDRESS_NOT_EXISTS,
    INVALID_COINS_VALUE,
    HASH_COLLISION,
    BLOCKCHAIN_NOT_VALID,
    SAVE_PASSPHRASE,
    SAME_PASSWORD,
    NOT_VALID_PASSWORD,
    PASSWORD_NOT_CORRECT,
    PASSWORD_HASH_COLLISION,
    OUT_OF_RANGE,
    USER_NOT_EXIST,
    LANGUAGE_LOAD_ERROR,
    CHAIN_LENGTH_ERROR,
    CURRENT_USER_ADDRESS,
    REQUEST_MESSAGE_EMPTY,
    REQUEST_AMOUNT_INVALID
};

class ProgramException : public QException
{
    ErrorsNames error_name;
    QMessageBox error_messageBox;
    QString exception_source;
public:
    ProgramException();
    ProgramException(ErrorsNames error_name);
    ProgramException(ErrorsNames error_name, QString exception_source);

    void getError();
    void setWindowLanguage(int index);

    ~ProgramException();
};

#endif // PROGRAMEXCEPTION_H
