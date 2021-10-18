#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "client/scripts/json_func.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    login_succesfull = false;

    connect(&ui_Auth, SIGNAL(login_button_clicked()), this, SLOT(authorizeUser()));
    connect(&ui_Auth, SIGNAL(destroyed()), this, SLOT(show()));
    connect(&ui_Auth, SIGNAL(register_button_clicked()), this, SLOT(registerUser()));

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display()
{
    ui_Auth.show();
}

void MainWindow::authorizeUser()
{

    wallet_key = ui_Auth.getInputKey();
    QVector<QString> valid_keys = getUserKey();
    for(int index = 0; index < valid_keys.length(); index++)
    {
        if(wallet_key == valid_keys[index])
        {
            ui_Auth.close();
            this->show();
            break;
        }
        else if (index == valid_keys.length()-1)
        {
            QMessageBox keyErr;
            keyErr.setWindowTitle("Ошибка");
            keyErr.setText("Данного ключа не существует");
            keyErr.setIcon(QMessageBox::Critical);
            keyErr.exec();
            break;
        }
    }

}

void MainWindow::registerUser()
{

}
