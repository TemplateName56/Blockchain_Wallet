#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "client/scripts/json_func.h"
#include "client/scripts/new_wallet.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login_succesfull = false;

    createActions();
    createMenus();
    createTrayMenu();

    connect(&ui_Auth, SIGNAL(login_button_clicked()), this, SLOT(authorizeUser()));
    connect(&ui_Auth, SIGNAL(destroyed()), this, SLOT(show()));
    connect(&ui_Auth, SIGNAL(register_button_clicked()), this, SLOT(registerUser()));
    connect(&ui_Settings, SIGNAL(languageChanged()), this, SLOT(setWindowLanguage()));
    connect(&ui_Settings, SIGNAL(trayCheckBoxToggled()), this, SLOT(trayEnabled()));
    connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    ui->sendWidget->hide();
    ui->recieveWidget->hide();
    ui->transactionsWidget->hide();

    statusBar()->showMessage("Connected...");
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

    ui->walletAddressLabel->setText(wallet_address);
    ui->walletKeyLabel->setText(wallet_key);

    ui_Auth.close();
    Sleep(250);
    this->show();
}

void MainWindow::homeTR()
{
    ui->sendWidget->hide();
    ui->recieveWidget->hide();
    ui->transactionsWidget->hide();
    ui->mainWidget->setVisible(true);
}

void MainWindow::sendTR()
{
    ui->mainWidget->hide();
    ui->recieveWidget->hide();
    ui->transactionsWidget->hide();
    ui->sendWidget->setVisible(true);
}

void MainWindow::recieveTR()
{
    ui->sendWidget->hide();
    ui->mainWidget->hide();
    ui->transactionsWidget->hide();
    ui->recieveWidget->setVisible(true);
}

void MainWindow::transactionsTR()
{
    ui->sendWidget->hide();
    ui->mainWidget->hide();
    ui->recieveWidget->hide();
    ui->transactionsWidget->setVisible(true);
}

void MainWindow::createActions()
{
    QPixmap homepix("icons/menuIcon.png");
    QPixmap sendpix("icons/sendIcon.png");
    QPixmap recievepix("icons/recieveIcon.png");
    QPixmap helppix("icons/helpIcon.png");
    QPixmap transactionspix("icons/transactionsIcon.png");
    //QPixmap programpix("icons/programIcon.png");

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

    about_program = new QAction("&About Wallet", this);

    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
    connect(home, &QAction::triggered, this, &MainWindow::homeTR);
    connect(send, &QAction::triggered, this, &MainWindow::sendTR);
    connect(recieve, &QAction::triggered, this, &MainWindow::recieveTR);
    connect(transactions, &QAction::triggered, this, &MainWindow::transactionsTR);

    connect(options, &QAction::triggered, &ui_Settings, &settings_Form::settingsShow);
    connect(about_program, &QAction::triggered, &ui_AboutProgram, &about_program_Form::aboutShow);
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

void MainWindow::createTrayMenu()
{
    tray_menu = new QMenu(this);

    view_window = new QAction("&Show window", this);
    connect(view_window, SIGNAL(triggered()), this, SLOT(show()));

    tray_menu->addAction(view_window);
    tray_menu->addSeparator();
    tray_menu->addAction(quit);

    tray_icon = new QSystemTrayIcon(this);
    tray_icon->setIcon(QIcon("icons/programIcon.png"));

    tray_icon->setContextMenu(tray_menu);
    tray_icon->show();
}

void MainWindow::setWindowLanguage()
{
    switch (ui_Settings.languageIndex) {
    case English:
        break;
    case Ukranian:
        break;
    case Russian:
        setWindowTitle("Мой кошелёк");

        main_menu->setTitle("&Главное");
        settings_menu->setTitle("&Настройки");
        help_menu->setTitle("&Помощь");

        home->setText("&Обзор");
        send->setText("&Отправить");
        recieve->setText("&Получить");
        transactions->setText("&Транзакции");

        help->setText("&Помощь");
        quit->setText("&Выход");

        encrypt_wallet->setText("&Зашифровать кошелёк");
        change_passphrase->setText("&Изменить секретное слово");
        options->setText("&Настройки");

        about_program->setText("&О Программе");
        view_window->setText("&Показать окно");

        break;
    }
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        if(tray_enable)
        {
            if(!this->isVisible())
            {
                Sleep(250);
                this->show();
            }
            else
            {
                Sleep(250);
                this->hide();
            }
        }
        break;
    default:
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (tray_icon->isVisible() && tray_enable)
    {
        event->ignore();
        this->hide();

        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

        tray_icon->showMessage("Wallet","Application minimized in tray", icon, 250);
    }
}

void MainWindow::trayEnabled()
{
    if(tray_enable)
    {
        tray_enable = false;
    }
    else
    {
        tray_enable = true;
    }
}

MainWindow::~MainWindow()
{
    delete ui;

    delete home;
    delete send;
    delete recieve;
    delete transactions;

    delete help;
    delete quit;

    delete encrypt_wallet;
    delete change_passphrase;
    delete options;

    delete about_program;
    delete view_window;

    delete main_menu;
    delete settings_menu;
    delete help_menu;

    delete toolbar;
    delete tray_icon;
}
