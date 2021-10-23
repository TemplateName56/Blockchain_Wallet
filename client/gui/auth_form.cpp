#include "auth_form.h"
#include "ui_auth_form.h"

auth_Form::auth_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::auth_Form)
{
    ui->setupUi(this);
    ui->walletKeyInput->setPlaceholderText("Enter your passphrase...");
}

auth_Form::~auth_Form()
{
    qDebug() << "destroyed auth";
    delete ui;
}

void auth_Form::on_walletKeyInput_textEdited(const QString &arg1)
{
    auth_Form::user_key = arg1;
}


void auth_Form::on_loginButton_clicked()
{
    emit login_button_clicked();
}


void auth_Form::on_registerButton_clicked()
{
    emit register_button_clicked();
}

QString auth_Form::getInputKey()
{
    return auth_Form::user_key;
}

