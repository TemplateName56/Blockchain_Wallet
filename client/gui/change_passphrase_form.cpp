#include "change_passphrase_form.h"
#include "ui_change_passphrase_form.h"
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
    JSON file_users("users.json");
    //file_users.changed_passphrase_oldkey(old_password, new_password);
    //file_users.changed_passphrase_address();
    try {
        if(old_password == new_password)
        {
            throw ProgramException(SAME_PASSWORD);
        }
        if(old_password != current_wallet_pass)
        {
            throw ProgramException(NOT_VALID_PASSWORD);
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

void change_passphrase_Form::recieveOldWalletPass(QString current_wallet_pass)
{
    this->current_wallet_pass = current_wallet_pass;
}

void change_passphrase_Form::setWindowLanguage(QVector<QString> language_vector)
{

}
