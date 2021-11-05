#include "encrypt_wallet_form.h"
#include "ui_encrypt_wallet_form.h"

encrypt_wallet_Form::encrypt_wallet_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::encrypt_wallet_Form)
{
    ui->setupUi(this);
}

void encrypt_wallet_Form::showEncrypt()
{
    this->show();
}

encrypt_wallet_Form::~encrypt_wallet_Form()
{
    delete ui;
}
