#ifndef PROGRAMEXCEPTION_H
#define PROGRAMEXCEPTION_H

#include <QException>
#include <QFileInfo>
#include <QMessageBox>

enum errorsNames{
    INVALID_INPUT,
    INVALID_KEY,
    FILE_EXIST_ERROR,
    FILE_READ_ERROR,
    FILE_WRITE_ERROR,
    ADDRESS_NOT_EXISTS,
    INVALID_CONS_VALUE,
    INCORRECT_ADDRESS
};

class ProgramException : public QException
{
    errorsNames error_name;
    QMessageBox error_messageBox;
public:
    ProgramException();
    ProgramException(errorsNames new_error);

    ~ProgramException();

    void getError();
};

#endif // PROGRAMEXCEPTION_H
