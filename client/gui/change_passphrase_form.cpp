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

void change_passphrase_Form::on_languagesBox_currentIndexChanged(int index){

switch (index) {

   //case ENGLISH:

        //ui->textEdit_change_pass->setText("<html><head/><body><p><span style=\" font-size:8pt;\">Enter a </span><span style=\" font-size:8pt; font-weight:600;\">new password</span><span style=\" font-size:8pt;\"> for your wallet.</span></p><p><span style=\" font-size:8pt;\">Please use a password of </span><span style=\" font-size:8pt; font-weight:600;\">ten </span><span style=\" font-size:8pt;\">random characters!<br/></span></p></body></html>");

       // break;

//    case UKRANIAN:

//ui->textEdit_change_pass->setText("<html><head/><body><p>Введіть <span style=\" font-weight:600;\">новий пароль</span> для свого гаманця.</p><p>Будь ласка, використовуйте пароль з <span style=\" font-weight:600;\">десяти</span> випадкових символів!</p></body></html>");

         //        break;

//    case RUSSIAN:
//
        //ui->textEdit_change_pass->setText("<html><head/><body><p>Введите <span style=\" font-weight:600;\">новый пароль</span> для вашего кошелька.</p><p>Пожалуйста, используйте пароль из <span style=\" font-weight:600;\">десяти</span> случайных символов!</p></body></html>");

//        break;
    }
}
