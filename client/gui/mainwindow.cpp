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
    transactionsGroup = new QParallelAnimationGroup;

    createActions();
    createMenus();
    createTrayMenu();
    uiChanges();
    requestsHistory();

    connect(&ui_Auth, SIGNAL(login_button_clicked()), this, SLOT(authorizeUser()));
    connect(&ui_Auth, SIGNAL(destroyed()), this, SLOT(show()));
    connect(&ui_Auth, SIGNAL(register_button_clicked()), this, SLOT(registerUser()));
    connect(&ui_Settings, SIGNAL(languageChanged()), this, SLOT(setWindowLanguage()));
    connect(&ui_Settings, SIGNAL(trayCheckBoxToggled()), this, SLOT(trayEnabled()));
    connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    connect(this,SIGNAL(tempTriggered()),this,SLOT(tempSlot())); // delete after test

    ui->stackedWidget->setCurrentIndex(0);
    setWindowLanguage();

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

    int index = valid_keys.indexOf(wallet_key);

    if(index != -1)
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
    }
    else
    {
        QMessageBox key_error;

        key_error.setWindowTitle("Ошибка");
        key_error.setText("Данного ключа не существует");
        key_error.setIcon(QMessageBox::Critical);

        key_error.exec();
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
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::sendTR()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::recieveTR()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::transactionsTR()
{
    ui->stackedWidget->setCurrentIndex(3);
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

    view_window = new QAction("&Show Window", this);
    connect(view_window, &QAction::triggered, this, &MainWindow::show);

    tray_menu->addAction(view_window);
    tray_menu->addSeparator();
    tray_menu->addAction(quit);

    tray_icon = new QSystemTrayIcon(this);
    tray_icon->setIcon(QIcon("icons/programIcon.png"));

    tray_icon->setContextMenu(tray_menu);
    tray_icon->show();
}

void MainWindow::uiChanges()
{
    ui->payToAddress->setPlaceholderText("Enter wallet-address");
    ui->addUserToAddressBook->setPlaceholderText("Enter a label for this address to add it to your address book");
}

void MainWindow::setWindowLanguage()
{
    switch (ui_Settings.languageIndex) {
    case English:
        this->setWindowTitle("My Wallet");

        main_menu->setTitle("&Main");
        settings_menu->setTitle("&Settings");
        help_menu->setTitle("&Help");

        home->setText("&Home");
        send->setText("&Send");
        recieve->setText("&Recieve");
        transactions->setText("&Transactions");

        help->setText("&Help");
        quit->setText("&Quit");

        encrypt_wallet->setText("&Encrypt Wallet...");
        change_passphrase->setText("&Change Passphrase...");
        options->setText("&Options...");

        about_program->setText("&About Program");
        view_window->setText("&Show Window");

        ui->sendCoinsButton->setText("&Send");
        ui->payToLabel->setText("Pay To:");
        ui->addToAddressBookLabel->setText("User Label:");
        ui->amountLabel->setText("Amount:");
        ui->balanceLabel->setText("Balance:");
        ui->commissionLabel->setText("Commission");
        ui->feeCheckBox->setText("&Subsctract fee from amount");

        ui->transactionsOverviewLabel->setText("Transactions");
        break;
    case Ukranian:
        this->setWindowTitle("Мій Гаманець");

        main_menu->setTitle("&Головна");
        settings_menu->setTitle("&Налаштування");
        help_menu->setTitle("&Допомога");

        home->setText("&Огляд");
        send->setText("&Надіслати");
        recieve->setText("&Отримати");
        transactions->setText("&Транзакції");

        help->setText("&Допомога");
        quit->setText("&Вихід");

        encrypt_wallet->setText("&Шифрування гаманця");
        change_passphrase->setText("&Змінити парольну фразу");
        options->setText("&Налаштування");

        about_program->setText("&Про Програму");
        view_window->setText("&Показати вікно");

        ui->sendCoinsButton->setText("&Надіслати");
        ui->addToAddressBookLabel->setText("Ярлик:");
        ui->payToLabel->setText("Адреса:");
        ui->amountLabel->setText("Сума:");
        ui->balanceLabel->setText("Баланс:");
        ui->commissionLabel->setText("Комісія");
        ui->feeCheckBox->setText("&Відніміть від суми комісію");

        ui->transactionsOverviewLabel->setText("Транзакції");
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

        ui->sendCoinsButton->setText("&Отправить");
        ui->addToAddressBookLabel->setText("Метка:");
        ui->payToLabel->setText("Адресс:");
        ui->amountLabel->setText("Сумма:");
        ui->balanceLabel->setText("Баланс:");
        ui->commissionLabel->setText("Комиссия");
        ui->feeCheckBox->setText("&Вычесть комиссию из суммы");

        ui->transactionsOverviewLabel->setText("Транзакции");
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
        ui_Settings.hide();
        ui_AboutProgram.hide();

        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

        tray_icon->showMessage("Wallet","Application minimized in tray", icon, 250);
    }
    else
    {
        ui_Settings.close();
        ui_AboutProgram.close();
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

void MainWindow::on_addUserToAddressBook_textChanged(const QString &arg1)
{

}

void MainWindow::on_payToAddress_textChanged(const QString &arg1)
{

}

void MainWindow::setupTransactionsOverview()
{
    transactionsGroup->clear();

    switch (last_transaction_notify) {
    case 1:
        last_transaction_notify = 5;
        y_tr2_pos += 100;
        y_tr3_pos += 100;
        y_tr4_pos += 100;
        y_tr5_pos += 100;
        y_tr1_pos = 10;
        ui->transactionInfo_1->move(10,-80);
        break;
    case 2:
        last_transaction_notify = 1;
        y_tr1_pos += 100;
        y_tr3_pos += 100;
        y_tr4_pos += 100;
        y_tr5_pos += 100;
        y_tr2_pos = 10;
        ui->transactionInfo_2->move(10,-80);
        break;
    case 3:
        last_transaction_notify = 2;
        y_tr1_pos += 100;
        y_tr2_pos += 100;
        y_tr4_pos += 100;
        y_tr5_pos += 100;
        y_tr3_pos = 10;
        ui->transactionInfo_3->move(10,-80);
        break;
    case 4:
        last_transaction_notify = 3;
        y_tr1_pos += 100;
        y_tr2_pos += 100;
        y_tr3_pos += 100;
        y_tr5_pos += 100;
        y_tr4_pos = 10;
        ui->transactionInfo_4->move(10,-80);
        break;
    case 5:
        last_transaction_notify = 4;
        y_tr1_pos += 100;
        y_tr2_pos += 100;
        y_tr3_pos += 100;
        y_tr4_pos += 100;
        y_tr5_pos = 10;
        ui->transactionInfo_5->move(10,-80);
        break;
    default:
        break;
    }

    transaction_1 = new QPropertyAnimation(ui->transactionInfo_1, "geometry");
    transaction_1->setDuration(500);
    transaction_1->setStartValue(ui->transactionInfo_1->geometry());
    transaction_1->setEndValue(ui->transactionInfo_1->geometry().translated(0, 90));

    transaction_2 = new QPropertyAnimation(ui->transactionInfo_2, "geometry");
    transaction_2->setDuration(500);
    transaction_2->setStartValue(ui->transactionInfo_2->geometry());
    transaction_2->setEndValue(ui->transactionInfo_2->geometry().translated(0, 90));

    transaction_3 = new QPropertyAnimation(ui->transactionInfo_3, "geometry");
    transaction_3->setDuration(500);
    transaction_3->setStartValue(ui->transactionInfo_3->geometry());
    transaction_3->setEndValue(ui->transactionInfo_3->geometry().translated(0, 90));

    transaction_4 = new QPropertyAnimation(ui->transactionInfo_4, "geometry");
    transaction_4->setDuration(500);
    transaction_4->setStartValue(ui->transactionInfo_4->geometry());
    transaction_4->setEndValue(ui->transactionInfo_4->geometry().translated(0, 90));

    transaction_5 = new QPropertyAnimation(ui->transactionInfo_5, "geometry");
    transaction_5->setDuration(500);
    transaction_5->setStartValue(ui->transactionInfo_5->geometry());
    transaction_5->setEndValue(ui->transactionInfo_5->geometry().translated(0, 90));

    transactionsGroup->addAnimation(transaction_1);
    transactionsGroup->addAnimation(transaction_2);
    transactionsGroup->addAnimation(transaction_3);
    transactionsGroup->addAnimation(transaction_4);
    transactionsGroup->addAnimation(transaction_5);
}

void MainWindow::requestsHistory()
{
    request_view_model = new QStandardItemModel(this);
    request_view_model->setColumnCount(4);
    request_view_model->setHorizontalHeaderLabels(QStringList() << "Date" << "Label" << "Message" << "Amount");
    ui->requestsView->setModel(request_view_model);
    ui->requestsView->setColumnWidth(0,100);
    ui->requestsView->setColumnWidth(1,200);
    ui->requestsView->setColumnWidth(2,341);
    ui->requestsView->setColumnWidth(3,100);


    QFile requestsList("requestsList.csv");
    if(!requestsList.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Not open1";
    }
    else
    {
        QTextStream in(&requestsList);
        while(!in.atEnd())
        {
            QString requests = in.readLine();
            qDebug() << "DSA: " << requests;
            QList<QStandardItem *> newRequestsList;

            int count = 0;
            for(const QString &item : requests.split(";"))
            {
                newRequestsList.append(new QStandardItem(item));
                count++;
            }
            for(int i = 0; i < count; i++)
            {
                newRequestsList[i]->setTextAlignment(Qt::AlignCenter);
            }
            request_view_model->insertRow(request_view_model->rowCount(), newRequestsList);
        }
        requestsList.close();
    }
    //ui->requestsView->resizeColumnsToContents();
}

void MainWindow::newTransaction()
{

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
    delete tray_menu;

    delete toolbar;
    delete tray_icon;

    delete transactionsGroup;
}

void MainWindow::tempSlot()
{
    // delete after test
}

void MainWindow::on_tempPushButton_clicked() // delete after test
{
    setupTransactionsOverview();
    transactionsGroup->start();
    emit tempTriggered();
}

