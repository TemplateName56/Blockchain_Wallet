#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "client/scripts/json_func.h"
#include "client/scripts/new_wallet_generation_procedure.h"
#include <windows.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login_succesfull = false;

    QPixmap homepix("icons/menuIcon.png");
    QPixmap sendpix("icons/sendIcon.png");
    QPixmap recievepix("icons/recieveIcon.png");
    QPixmap helppix("icons/helpIcon.png");
    QPixmap transactionspix("icons/transactionsIcon.png");

    QMenu *main_menu;
    main_menu = menuBar()->addMenu("&Main");

    QMenu *settings_menu;
    settings_menu = menuBar()->addMenu("&Settings");

    QMenu *help_menu;
    help_menu = menuBar()->addMenu("&Help");

    QAction *home = new QAction(homepix, "&Home", this);
    QAction *send = new QAction(sendpix, "&Send", this);
    QAction *recieve = new QAction(recievepix, "&Recieve", this);
    QAction *transactions = new QAction(transactionspix, "&Transactions", this);
    QAction *help = new QAction(helppix, "&Help", this);
    QAction *quit = new QAction("&Quit", this);

    main_menu->addAction(home);
    main_menu->addAction(send);
    main_menu->addAction(recieve);
    main_menu->addAction(help);
    main_menu->addSeparator();
    main_menu->addAction(quit);

    connect(&ui_Auth, SIGNAL(login_button_clicked()), this, SLOT(authorizeUser()));
    connect(&ui_Auth, SIGNAL(destroyed()), this, SLOT(show()));
    connect(&ui_Auth, SIGNAL(register_button_clicked()), this, SLOT(registerUser()));
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);

    QToolBar *toolbar = addToolBar("main menu");
    toolbar->addAction(QIcon(homepix),"Home page");
    toolbar->addAction(QIcon(sendpix),"Send page");
    toolbar->addAction(QIcon(recievepix),"Recieve page");
    toolbar->addAction(QIcon(transactionspix),"Transactions");

    statusBar()->showMessage("Connected");
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
    QVector<QString> valid_keys = getUsersInfo(KEY);

    for(int index = 0; index < valid_keys.length(); index++)
    {
        if(wallet_key == valid_keys[index])
        {
            login_succesfull = true;

            ui_Auth.close();
            Sleep(250);
            this->show();

            break;
        }
        else if (index == valid_keys.length() - 1)
        {
            QMessageBox key_error;

            key_error.setWindowTitle("Ошибка");
            key_error.setText("Данного ключа не существует");
            key_error.setIcon(QMessageBox::Critical);

            key_error.exec();

            break;
        }
    }


}

void MainWindow::registerUser()
{
    QString new_user_address = randomWalletAdress();
    QString new_user_wallet_key = randomWalletKey();

    registerNewUsers(new_user_address, new_user_wallet_key);
    login_succesfull = true;

    ui_Auth.close();
    Sleep(250);
    this->show();
}
