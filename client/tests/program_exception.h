#ifndef PROGRAMEXCEPTION_H
#define PROGRAMEXCEPTION_H

#include <QException>
#include <QFileInfo>
#include <QMessageBox>

enum ErrorsNames{
    INVALID_INPUT,
    INVALID_KEY,
    FILE_EXIST_ERROR,
    FILE_READ_ERROR,
    FILE_WRITE_ERROR,
    ADDRESS_NOT_EXISTS,
    INVALID_CONS_VALUE,
    INCORRECT_ADDRESS,
    HASH_COLLISION
};

class ProgramException : public QException
{
    ErrorsNames error_name;
    QMessageBox error_messageBox;
public:
    ProgramException();
    ProgramException(ErrorsNames new_error);

    void getError();

    ~ProgramException();
};

#endif // PROGRAMEXCEPTION_H
