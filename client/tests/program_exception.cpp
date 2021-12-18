#include "program_exception.h"
#include "QApplication"
#include <QTimer>
#include <QIcon>
#include "client/scripts/csv_func.h"

ProgramException::ProgramException()
{

}

ProgramException::ProgramException(ErrorsNames error_name)
{
    this->error_name = error_name;
}

ProgramException::ProgramException(ErrorsNames error_name, QString exception_source)
{
    this->error_name = error_name;
    this->exception_source = exception_source;
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
        error_messageBox.setText("File: " + exception_source + "\nNot Exist");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();

        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    case FILE_READ_ERROR:
        error_messageBox.setText("File: " + exception_source + "\nRead Error");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    case FILE_WRITE_ERROR:
        error_messageBox.setText("File: " + exception_source + "\nWrite Error");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    case INVALID_ADDRESS:
        error_messageBox.setText("Address can consist only 17 symbols");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
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
    case SAVE_PASSPHRASE:
        error_messageBox.setWindowTitle("Infomation");
        error_messageBox.setText("Your passphrase: " + exception_source + "\nif u lose them, you should cant restore them.");
        error_messageBox.setIcon(QMessageBox::Information);
        error_messageBox.setTextInteractionFlags(Qt::TextSelectableByMouse);

        error_messageBox.exec();
        break;
    case SAME_PASSWORD:
        error_messageBox.setText("New password similar to old");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case NOT_VALID_PASSWORD:
        error_messageBox.setText("Not correct password, they must consist over 8 symbols");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case PASSWORD_NOT_CORRECT:
        error_messageBox.setText("Old password not correct");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case PASSWORD_HASH_COLLISION:
        error_messageBox.setText("Not correct password");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case OUT_OF_RANGE:
        qDebug() << "Out of range in: " << exception_source;
        break;
    case USER_NOT_EXIST:
        qDebug() << "User not exist";
        break;
    case LANGUAGE_LOAD_ERROR:
        break;
    default:
        break;
    }
}

ProgramException::~ProgramException()
{

}

void ProgramException::setWindowLanguage()
{

     //CSV file_tr("translation.csv");

     //QVector<QString> str = file_tr.get_tr(languageIndex);

     //language_vector.at(57)

//this->error_messageBox.setWindowTitle(language_vector.at(68));
     //this->error_messageBox.setText("This key not exists");



//     error_messageBox.setWindowTitle(language_vector.at(68));
//     error_messageBox.setWindowIcon(QIcon("icons/programIcon.png"));

//     switch (error_name) {
//     case INVALID_INPUT:
//         break;
//     case INVALID_KEY:
//         error_messageBox.setText(language_vector.at(69));
//         error_messageBox.setIcon(QMessageBox::Critical);

//         error_messageBox.exec();
//         break;
//     case FILE_EXIST_ERROR:
//         error_messageBox.setText(language_vector.at(70) + exception_source + "\n" + (language_vector.at(71));
//         error_messageBox.setIcon(QMessageBox::Critical);

//         error_messageBox.exec();

//         QTimer::singleShot(0, qApp, &QCoreApplication::quit);
//         break;
//     case FILE_READ_ERROR:
//         error_messageBox.setText(language_vector.at(70) + exception_source + "\n" + (language_vector.at(72));
//         error_messageBox.setIcon(QMessageBox::Critical);

//         error_messageBox.exec();
//         QTimer::singleShot(0, qApp, &QCoreApplication::quit);
//         break;
//     case FILE_WRITE_ERROR:
//         error_messageBox.setText(language_vector.at(70) + exception_source + "\n" + (language_vector.at(73));
//         error_messageBox.setIcon(QMessageBox::Critical);

//         error_messageBox.exec();
//         QTimer::singleShot(0, qApp, &QCoreApplication::quit);
//         break;
//     case INVALID_ADDRESS:
//         error_messageBox.setText(language_vector.at(74));
//         error_messageBox.setIcon(QMessageBox::Critical);

//         error_messageBox.exec();
//         break;
//     case ADDRESS_NOT_EXISTS:
//         error_messageBox.setText(language_vector.at(75));
//         error_messageBox.setIcon(QMessageBox::Critical);

//         error_messageBox.exec();
//         break;
//     case INVALID_COINS_VALUE:
//         error_messageBox.setText(language_vector.at(76));
//         error_messageBox.setIcon(QMessageBox::Critical);

//         error_messageBox.exec();
//         break;
//     case HASH_COLLISION:
//         break;
//     case SAVE_PASSPHRASE:
//         error_messageBox.setWindowTitle(language_vector.at(76));
//         error_messageBox.setText(language_vector.at(80) + exception_source + "\n" + language_vector.at(76));
//         error_messageBox.setIcon(QMessageBox::Information);
//         error_messageBox.setTextInteractionFlags(Qt::TextSelectableByMouse);

//         error_messageBox.exec();
//         break;
//     case SAME_PASSWORD:
//         error_messageBox.setText(language_vector.at(79));
//         error_messageBox.setIcon(QMessageBox::Critical);

//         error_messageBox.exec();
//         break;
//     case NOT_VALID_PASSWORD:
//         error_messageBox.setText(language_vector.at(78));
//         error_messageBox.setIcon(QMessageBox::Critical);

//         error_messageBox.exec();
//         break;
//     default:
//         break;
//     }

     //emit languageChanged(str);
}
