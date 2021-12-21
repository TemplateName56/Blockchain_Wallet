#include "auth_form.h"
#include "ui_auth_form.h"

#include "client/scripts/csv_func.h"

auth_Form::auth_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::auth_Form)
{
    ui->setupUi(this);
    ui->label->setPixmap(QIcon("icons/programIcon.png").pixmap(50,50));
    this->setWindowIcon(QIcon("icons/programIcon.png"));
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

auth_Form::~auth_Form()
{
    delete ui;
}

void auth_Form::on_walletKeyInput_textEdited(const QString &arg1)
{
    this->user_key = arg1;
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
    return this->user_key;
}

void auth_Form::setWindowLanguage(QVector<QString> language_vector)
{
    this->setWindowTitle(language_vector.at(8));

    ui->walletKeyInput->setPlaceholderText(language_vector.at(10));

    ui->welcomeLabel->setText(language_vector.at(9));
    ui->walletKeyInput->setToolTip("");
    ui->loginButton->setText(language_vector.at(11));
    ui->registerButton->setText(language_vector.at(12));

}

