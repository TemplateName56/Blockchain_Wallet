#include "program_exception.h"
#include "QApplication"
#include <QTimer>

ProgramException::ProgramException()
{

}

ProgramException::ProgramException(errorsNames new_error)
{
    error_name = new_error;
}

void ProgramException::getError()
{
    switch (error_name) {
    case INVALID_INPUT:
        break;
    case INVALID_KEY:
        error_messageBox.setWindowTitle("Ошибка");
        error_messageBox.setText("Данного ключа не существует");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case FILE_EXIST_ERROR:
        error_messageBox.setWindowTitle("Ошибка");
        error_messageBox.setText("FILE EXISTS ERROR");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();

        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    case FILE_READ_ERROR:
        break;
    case FILE_WRITE_ERROR:
        break;
    default:
        break;
    }
}

ProgramException::~ProgramException()
{

}

