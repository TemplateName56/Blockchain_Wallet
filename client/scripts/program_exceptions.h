#ifndef PROGRAM_EXCEPTIONS_H
#define PROGRAM_EXCEPTIONS_H

#include <exception>
#include <QException>

enum errors_name
{
    INVALID_INPUT
};

class MyExceptions : public QException
{
private:
    QString error_name;
public:
    MyExceptions(errors_name error);

    void getError();
};

#endif // PROGRAM_EXCEPTIONS_H
