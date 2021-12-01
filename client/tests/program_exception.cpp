#include "program_exception.h"
#include "QApplication"
#include <QTimer>
#include <QIcon>

ProgramException::ProgramException()
{

}

ProgramException::ProgramException(ErrorsNames new_error)
{
    error_name = new_error;
}

void ProgramException::getError()
{
    error_messageBox.setWindowTitle("Error");
    error_messageBox.setWindowIcon(QIcon("icons/programIcon.png"));

    switch (error_name) {
    case INVALID_INPUT:
        break;
    case INVALID_KEY:
        error_messageBox.setText("This key not exists");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case FILE_EXIST_ERROR:
        error_messageBox.setText("FILE EXISTS ERROR");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();

        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    case FILE_READ_ERROR:
        error_messageBox.setText("FILE READ ERROR");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    case FILE_WRITE_ERROR:
        error_messageBox.setText("FILE WRITE ERROR");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    case ADDRESS_NOT_EXISTS:
        error_messageBox.setText("This address not available");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case INVALID_COINS_VALUE:
        error_messageBox.setText("You don't have enough money");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case HASH_COLLISION:
        break;
    default:
        break;
    }
}

ProgramException::~ProgramException()
{

}

