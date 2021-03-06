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
    case INVALID_KEY:
        error_messageBox.setText("Невірний пароль.");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case FILE_EXIST_ERROR:
        error_messageBox.setText("Файл: " + exception_source + "\nВідсутній.\nДодайте його з теки\n /Blockchain Wallet/doc/" + exception_source);
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();

        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    case FILE_READ_ERROR:
        error_messageBox.setText("Файл: " + exception_source + "\nПомилка зчитування");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    case FILE_WRITE_ERROR:
        error_messageBox.setText("Файл: " + exception_source + "\nПомилка запису");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    case INVALID_ADDRESS:
        error_messageBox.setText("Адреса може складатися тільки з 17 символів");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case ADDRESS_NOT_EXISTS:
        error_messageBox.setText("Гаманця з заданою адресою, не існує.");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case INVALID_COINS_VALUE:
        error_messageBox.setText("Недостатньо коштів на рахунку");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case HASH_COLLISION:
        error_messageBox.setText("Ваша транзакція заблокована");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case SAVE_PASSWORD:
        error_messageBox.setWindowTitle("Інформація");
        error_messageBox.setText("Ваш пароль: " + exception_source + "\nякщо ви його втратите,\n відновлення буде неможливе");
        error_messageBox.setIcon(QMessageBox::Information);
        error_messageBox.setTextInteractionFlags(Qt::TextSelectableByMouse);

        error_messageBox.exec();
        break;
    case SAME_PASSWORD:
        error_messageBox.setText("Новий пароль схожий на старий");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case NOT_VALID_PASSWORD:
        error_messageBox.setText("Не коректний пароль, пароль повинен складитися мінімум з 8 символів");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case PASSWORD_NOT_CORRECT:
        error_messageBox.setText("Старий пароль не коректний");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case PASSWORD_HASH_COLLISION:
        error_messageBox.setText("Не коректний пароль");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case OUT_OF_RANGE:
        error_messageBox.setText("Фатальна помилка!\nВихід за межі у: " + exception_source);
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();

        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    case CURRENT_USER_ADDRESS:
        error_messageBox.setText("Ви не можете відправити кошти самому собі");
        error_messageBox.setIcon(QMessageBox::Information);

        error_messageBox.exec();
        break;
    case REQUEST_MESSAGE_EMPTY:
        error_messageBox.setText("Пустий рядок повідомлення");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case REQUEST_AMOUNT_INVALID:
        error_messageBox.setText("Сумма запиту не коректна");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();
        break;
    case SEND_SUCCESSFUL:
        error_messageBox.setText("Ваша транзакція відправлена до валідатора");
        error_messageBox.setIcon(QMessageBox::Information);

        error_messageBox.exec();
        break;
    case BLOCKCHAIN_HASH_COLLISION:
        error_messageBox.setText("Фатальна помилка!\nБлокчейн має колізії");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();

        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    case CHAIN_NOT_VALID:
        error_messageBox.setText("Фатальна помилка!\nЛанцюг блокчейна не дійсний");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();

        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    case PASSWORD_CHANGED:
        error_messageBox.setText("Пароль успішно змінено");
        error_messageBox.setIcon(QMessageBox::Information);

        error_messageBox.exec();
        break;
    case IS_EMPTY:
        error_messageBox.setText("Фатальна помилка!\n" + exception_source + " пустий");
        error_messageBox.setIcon(QMessageBox::Critical);

        error_messageBox.exec();

        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        break;
    default:
        break;
    }
}

ProgramException::~ProgramException()
{

}
