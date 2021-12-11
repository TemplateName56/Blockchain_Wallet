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
    NOT_VALID_PASSWORD
};

class ProgramException : public QException
{
    ErrorsNames error_name;
    QMessageBox error_messageBox;
    QString wallet_key;
public:
    ProgramException();
    ProgramException(ErrorsNames error_name);
    ProgramException(ErrorsNames error_name, QString wallet_key);

    void getError();

    ~ProgramException();
};

#endif // PROGRAMEXCEPTION_H
