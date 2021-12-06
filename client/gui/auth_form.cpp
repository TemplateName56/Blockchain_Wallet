#include "auth_form.h"
#include "ui_auth_form.h"

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

void auth_Form::setWindowLanguage(int Language)
{
    switch (Language) {
    case 0:
        this->setWindowTitle("Authorization");

        ui->welcomeLabel->setText("Welcome");
        ui->walletKeyInput->setPlaceholderText("Enter your private key...");
        ui->walletKeyInput->setToolTip("");
        ui->loginButton->setText("&Login");
        ui->registerButton->setText("&Register");
        break;
    case 1:
        this->setWindowTitle("Авторізація");

        ui->welcomeLabel->setText("Ласкаво просимо!");
        ui->walletKeyInput->setPlaceholderText("Введіть ваш приватний ключ...");
        ui->walletKeyInput->setToolTip("");
        ui->loginButton->setText("&Вхід");
        ui->registerButton->setText("&Реєстрація");
        break;
    case 2:
        this->setWindowTitle("Авторизация");

        ui->welcomeLabel->setText("Добро пожаловать!");
        ui->walletKeyInput->setPlaceholderText("Введите ваш приватный ключ...");
        ui->walletKeyInput->setToolTip("");
        ui->loginButton->setText("&Войти");
        ui->registerButton->setText("&Регистрация");
        break;
    default:
        break;
    }
}

