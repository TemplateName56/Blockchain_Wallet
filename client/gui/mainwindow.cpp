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

    createActions();
    createMenus();


    connect(&ui_Auth, SIGNAL(login_button_clicked()), this, SLOT(authorizeUser()));
    connect(&ui_Auth, SIGNAL(destroyed()), this, SLOT(show()));
    connect(&ui_Auth, SIGNAL(register_button_clicked()), this, SLOT(registerUser()));

    ui->sendMenuWidget->setVisible(false);

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
            QVector<QString> user_address = getUsersInfo(ADDRESS);
            wallet_address = user_address[index];
            this->show();

            ui->walletAddressLabel->setText(wallet_address);
            ui->walletKeyLabel->setText(wallet_key);

            qDebug() << wallet_address;
            qDebug() << wallet_key;

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
    wallet_address = randomWalletAdress();
    wallet_key = randomWalletKey();

    registerNewUsers(wallet_address, wallet_key);
    login_succesfull = true;

    ui_Auth.close();
    Sleep(250);
    this->show();
}

void MainWindow::homeTR()
{
    ui->sendMenuWidget->hide();
    ui->mainMenuWidget->setVisible(true);
}

void MainWindow::sendTR()
{
    ui->mainMenuWidget->hide();
    ui->sendMenuWidget->setVisible(true);
}

void MainWindow::recieveTR()
{

}

void MainWindow::transactionsTR()
{

}

void MainWindow::createActions()
{
    QPixmap homepix("icons/menuIcon.png");
    QPixmap sendpix("icons/sendIcon.png");
    QPixmap recievepix("icons/recieveIcon.png");
    QPixmap helppix("icons/helpIcon.png");
    QPixmap transactionspix("icons/transactionsIcon.png");

    home = new QAction(homepix, "&Home", this);
    send = new QAction(sendpix, "&Send", this);
    recieve = new QAction(recievepix, "&Recieve", this);
    help = new QAction(helppix, "&Help", this);
    quit = new QAction("&Quit", this);

    quit->setShortcut(tr("Ctrl+Q"));

    transactions = new QAction(transactionspix, "&Transactions", this);
    encrypt_wallet = new QAction("&Encrypt Wallet...", this);
    change_passphrase = new QAction("&Change Passphrase...", this);
    options = new QAction("&Options...", this);

    about_program = new QAction("&About Wallet",this);


    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
    connect(home, &QAction::triggered, this, &MainWindow::homeTR);
    connect(send, &QAction::triggered, this, &MainWindow::sendTR);
}

void MainWindow::createMenus()
{
    main_menu = menuBar()->addMenu("&Main");

    main_menu->addAction(home);
    main_menu->addAction(send);
    main_menu->addAction(recieve);
    main_menu->addAction(help);
    main_menu->addSeparator();
    main_menu->addAction(quit);


    settings_menu = menuBar()->addMenu("&Settings");

    settings_menu->addAction(encrypt_wallet);
    settings_menu->addAction(change_passphrase);
    settings_menu->addSeparator();
    settings_menu->addAction(options);


    help_menu = menuBar()->addMenu("&Help");

    help_menu->addAction(about_program);


    toolbar = addToolBar("main menu");

    toolbar->addAction(home);
    toolbar->addAction(send);
    toolbar->addAction(recieve);
    toolbar->addAction(transactions);
}
