#include "change_passphrase_form.h"
#include "ui_change_passphrase_form.h"

#include "settings_form.h"

#include "client/scripts/json_func.h"

change_passphrase_Form::change_passphrase_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::change_passphrase_Form)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("icons/programIcon.png"));
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

void change_passphrase_Form::changePassphraseShow()
{
    this->show();
}

change_passphrase_Form::~change_passphrase_Form()
{
    delete ui;
}

void change_passphrase_Form::on_currentPassLE_textChanged(const QString &arg1)
{
    this->old_password = arg1;
}

void change_passphrase_Form::on_newPassLE_textChanged(const QString &arg1)
{
    this->new_password = arg1;
}

void change_passphrase_Form::on_changePassBTN_clicked()
{
    try {
        if(old_password == new_password)
        {
            throw ProgramException(SAME_PASSWORD);
        }
        else if(new_password.length() < 8)
        {
            throw ProgramException(NOT_VALID_PASSWORD);
        }
        if(users_information->isPasswordExists(new_password))
        {
            throw ProgramException(PASSWORD_HASH_COLLISION);
        }
        if(current_user->isPasswordCorrect(old_password))
        {
            current_user->setPassword(new_password);
            users_information->setUserPassword(current_user->getAddress(), current_user->getPassword());

            JSON file_json("users.json");
            file_json.write_users_file(*users_information);
            throw ProgramException(PASSWORD_CHANGED);
            //emit passwordChanged();
        }
        else
        {
            throw ProgramException(PASSWORD_NOT_CORRECT);
        }
    }  catch (ProgramException &error) {
        error.getError();
    }
}

void change_passphrase_Form::on_clearPassEnterBTN_clicked()
{
    ui->currentPassLE->clear();
    ui->newPassLE->clear();
}

void change_passphrase_Form::currentUserPassChange(User &current_user, Users &users_information)
{
    this->current_user = &current_user;
    this->users_information = &users_information;
}

void change_passphrase_Form::setWindowLanguage(int index)
{
    switch (index) {
    case ENGLISH:

        ui->textEdit_change_pass->setText("<html><head/><body><p><span style=\" font-size:8pt;\">Enter a </span><span style=\" font-size:8pt; font-weight:600;\">new password</span><span style=\" font-size:8pt;\"> for your wallet.</span></p><p><span style=\" font-size:8pt;\">Please use a password of </span><span style=\" font-size:8pt; font-weight:600;\">eight </span><span style=\" font-size:8pt;\">random characters!<br/></span></p></body></html>");
        this->setWindowTitle("Change the password");

        ui->currentPassLabel->setText("Current Password:");
        ui->newPassLabel->setText("New Password:");

        ui->changePassBTN->setText("Change");
        ui->clearPassEnterBTN->setText("Clear");

        break;
    case UKRANIAN:

        ui->textEdit_change_pass->setText("<html><head/><body><p>Введіть <span style=\" font-weight:600;\">новий пароль</span> для свого гаманця.</p><p>Будь ласка, використовуйте пароль з <span style=\" font-weight:600;\">восьми</span> випадкових символів!</p></body></html>");
        this->setWindowTitle("Змініти пароль");

        ui->currentPassLabel->setText("Поточний пароль:");
        ui->newPassLabel->setText("Новий пароль:");

        ui->changePassBTN->setText("Змінити");
        ui->clearPassEnterBTN->setText("Очистити");

        break;
    case RUSSIAN:

        ui->textEdit_change_pass->setText("<html><head/><body><p>Введите <span style=\" font-weight:600;\">новый пароль</span> для вашего кошелька.</p><p>Пожалуйста, используйте пароль из <span style=\" font-weight:600;\">восьми</span> случайных символов!</p></body></html>");
        this->setWindowTitle("Новий пароль:");

        ui->currentPassLabel->setText("Текущий пароль:");
        ui->newPassLabel->setText("Новый пароль:");

        ui->changePassBTN->setText("Изменить");
        ui->clearPassEnterBTN->setText("Очистить");

        break;
    }
}
