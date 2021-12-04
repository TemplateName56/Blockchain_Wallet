#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    try {
        fileExists("requestsList.csv");
    }  catch (ProgramException &error) {
        error.getError();
    }
    ui->priorityComboBox->setEnabled(false);

    val_1.setAuthority(100);
    val_2.setAuthority(75);
    val_3.setAuthority(1);

    qRegisterMetaType<TransactionData>("TransactionData");

    createActions();
    createMenus();
    createTrayMenu();
    uiChanges();
    requestsHistory();

    connect(&ui_Auth, SIGNAL(login_button_clicked()), this, SLOT(authorizeUser()));
    connect(&ui_Auth, SIGNAL(register_button_clicked()), this, SLOT(registerUser()));
    connect(&ui_Auth, SIGNAL(destroyed()), this, SLOT(show()));

    connect(&ui_Settings, SIGNAL(languageChanged()), this, SLOT(setWindowLanguage()));
    connect(&ui_Settings, SIGNAL(trayCheckBoxToggled()), this, SLOT(trayEnabled()));

    connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    connect(this, SIGNAL(sendButton_clicked_val_1(TransactionData)), &val_1, SLOT(addTransaction(TransactionData)), Qt::QueuedConnection);
    connect(this, SIGNAL(sendButton_clicked_val_2(TransactionData)), &val_2, SLOT(addTransaction(TransactionData)), Qt::QueuedConnection);
    connect(this, SIGNAL(sendButton_clicked_val_3(TransactionData)), &val_3, SLOT(addTransaction(TransactionData)), Qt::QueuedConnection);

    connect(&val_1, SIGNAL(sendTransaction(QString,TransactionData)), this, SLOT(newTransaction(QString,TransactionData)));
    connect(&val_2, SIGNAL(sendTransaction(QString,TransactionData)), this, SLOT(newTransaction(QString,TransactionData)));
    connect(&val_3, SIGNAL(sendTransaction(QString,TransactionData)), this, SLOT(newTransaction(QString,TransactionData)));

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
    try {
        algoritms use_algoritm;

        wallet_key = ui_Auth.getInputKey();

        QVector<QString> valid_keys = getUsersInfo(KEY);

        int index = valid_keys.indexOf(QString::fromStdString(use_algoritm.Hash(wallet_key.toStdString() + "SALT")));

        if(index != -1)
        {
            ui_Auth.close();
            Sleep(250);
            QVector<QString> user_address = getUsersInfo(ADDRESS);
            wallet_address = user_address[index];

            Balance current_user = val_1.getChain().getLastBlock().getUserBalance(wallet_address);

            ui->bwcBalance->setText(QString::number(current_user.getBalance(BWC)));
            ui->bwcNBalance->setText(QString::number(current_user.getBalance(BWC_N)));
            ui->bwcQBalance->setText(QString::number(current_user.getBalance(BWC_Q)));

            this->show();

            ui->walletAddressLabel->setText(wallet_address);
            ui->walletKeyLabel->setText(wallet_key);
        }
        else
        {
            throw ProgramException(INVALID_KEY);
        }
    } catch (ProgramException &error) {
        error.getError();
    }
}

void MainWindow::registerUser()
{
    try {
        wallet_address = randomWalletAdress();
        wallet_key = randomWalletKey();

        registerNewUsers(wallet_address, wallet_key + "SALT");

        ui->walletAddressLabel->setText(wallet_address);
        ui->walletKeyLabel->setText(wallet_key);

        ui_Auth.close();
        Sleep(250);

        Balance current_user = val_1.getChain().getLastBlock().getUserBalance(wallet_address);

        ui->bwcBalance->setText(QString::number(current_user.getBalance(BWC)));
        ui->bwcNBalance->setText(QString::number(current_user.getBalance(BWC_N)));
        ui->bwcQBalance->setText(QString::number(current_user.getBalance(BWC_Q)));

        this->show();
    }  catch (ProgramException &error) {
        error.getError();
    }
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

void MainWindow::blocksTR()
{
    ui->stackedWidget->setCurrentIndex(4);
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

    all_blocks = new QAction(transactionspix, "&Blocks", this);

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

    connect(all_blocks, &QAction::triggered, this, &MainWindow::blocksTR);

    connect(options, &QAction::triggered, &ui_Settings, &settings_Form::settingsShow);
    connect(about_program, &QAction::triggered, &ui_AboutProgram, &about_program_Form::aboutShow);
    connect(encrypt_wallet, &QAction::triggered, &ui_EncryptWallet, &encrypt_wallet_Form::showEncrypt);
    connect(change_passphrase, &QAction::triggered, &ui_ChangePass, &change_passphrase_Form::changePassphraseShow);
}

void MainWindow::createMenus()
{
    main_menu = menuBar()->addMenu("&Main");

    main_menu->addAction(home);
    main_menu->addAction(send);
    main_menu->addAction(recieve);
    main_menu->addAction(help);
    main_menu->addAction(all_blocks);
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
    toolbar->addAction(all_blocks);

    toolbar->setIconSize(QSize(90,30));
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
    ui->sendTransactionLabel->setPlaceholderText("Enter a label for this address to add it to your address book");
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

void MainWindow::addTransactionCard(QString label, QString timeStamp, double amount, CoinsType coins_type, int transaction_type)
{
    transactionsCardView *new_card = new transactionsCardView;

    new_card->setData(label, timeStamp, amount, coins_type, 0);
    if(counter == 3)
    {
        QLayoutItem *item = ui->cardsLayout->takeAt(2);
        delete item->widget();
        delete item;
    }
    else
    {
        counter++;
    }
    ui->cardsLayout->insertWidget(0, new_card);
}

void MainWindow::newTransaction(QString wallet_address, TransactionData data)
{
    qDebug() << val_1.getChain().getChainLenght();
    qDebug() << val_2.getChain().getChainLenght();
    qDebug() << val_3.getChain().getChainLenght();

    if(val_1.getChain().getChainLenght() > val_2.getChain().getChainLenght())
    {
        val_2.setChain(val_1.getChain());
    }
    if(val_2.getChain().getChainLenght() > val_1.getChain().getChainLenght())
    {
        val_1.setChain(val_2.getChain());
    }
    if(val_1.getChain().getChainLenght() > val_3.getChain().getChainLenght())
    {
        val_3.setChain(val_1.getChain());
    }
    if(val_3.getChain().getChainLenght() > val_1.getChain().getChainLenght())
    {
        val_1.setChain(val_3.getChain());
    }
    if(val_3.getChain().getChainLenght() > val_2.getChain().getChainLenght())
    {
        val_2.setChain(val_3.getChain());
    }
    if(val_2.getChain().getChainLenght() > val_3.getChain().getChainLenght())
    {
        val_3.setChain(val_2.getChain());
    }

    qDebug() << val_1.getChain().getChainLenght();
    qDebug() << val_2.getChain().getChainLenght();
    qDebug() << val_3.getChain().getChainLenght();

    if(wallet_address == this->wallet_address)
    {
        Balance current_user = val_1.getChain().getLastBlock().getUserBalance(wallet_address);

        ui->bwcBalance->setText(QString::number(current_user.getBalance(BWC)));
        ui->bwcNBalance->setText(QString::number(current_user.getBalance(BWC_N)));
        ui->bwcQBalance->setText(QString::number(current_user.getBalance(BWC_Q)));
    }
}

void MainWindow::on_payToAddress_textChanged(const QString &arg1)
{
    this->reciever_address = arg1;
}

void MainWindow::requestsHistory()
{
    request_view_model = new QStandardItemModel(this);
    request_view_model->setColumnCount(4);
    request_view_model->setHorizontalHeaderLabels(QStringList() << "Date" << "Label" << "Message" << "Amount");
    ui->requestsView->setModel(request_view_model);

    ui->requestsView->verticalHeader()->setVisible(false);

    ui->requestsView->setColumnWidth(0,100);
    ui->requestsView->setColumnWidth(1,200);
    ui->requestsView->setColumnWidth(2,350);
    ui->requestsView->setColumnWidth(3,108);

    CSV file("requestsList.csv");

    for(int index = 1; index < 3; index++)
    {
        QList<QStandardItem *> newRequestsList;
        for(int c = 1; c <= 4; c++)
        {
            switch(c){
            case 1:
                newRequestsList.append(new QStandardItem(file.get_date_csv(index)));
                break;
            case 2:
                newRequestsList.append(new QStandardItem(file.get_label_csv(index)));
                break;
            case 3:
                newRequestsList.append(new QStandardItem(file.get_message_csv(index)));
                break;
            case 4:
                newRequestsList.append(new QStandardItem(file.get_money_csv(index)));
                break;
            default:
                break;
            }
        }
        for(int i = 0; i < newRequestsList.length(); i++)
        {
            newRequestsList[i]->setTextAlignment(Qt::AlignCenter);
        }
        request_view_model->insertRow(request_view_model->rowCount(), newRequestsList);
    }

    QStandardItemModel *history_view_model = new QStandardItemModel(this);
        history_view_model->setColumnCount(5);
        history_view_model->setHorizontalHeaderLabels(QStringList() << "№" << "From" << "To" << "Money" << "Currency");
        ui->historyView->setModel(history_view_model);

        ui->historyView->verticalHeader()->setVisible(false);

        ui->historyView->setColumnWidth(0,100);
        ui->historyView->setColumnWidth(1,225);
        ui->historyView->setColumnWidth(2,225);
        ui->historyView->setColumnWidth(3,108);
        ui->historyView->setColumnWidth(4,108);

        JSON json_file("block2_10.json");
        //qDebug() << json_file.get_array_size();

        for(int i = 1; i <= json_file.get_array_size(); i++){
            QList<QStandardItem *> HistoryList;
            int count = 0;
            for(int c = 0; c < 5; c++){
                if(c == 0){
                    HistoryList.append(new QStandardItem(QString::number(json_file.get_number(i))));
                }else if(c == 1){
                    HistoryList.append(new QStandardItem(json_file.get_address_sender(i)));
                }else if(c == 2){
                    HistoryList.append(new QStandardItem(json_file.get_address_recipient(i)));
                }else if(c == 3){
                    HistoryList.append(new QStandardItem(QString::number(json_file.get_money(i))));
                }else if(c == 4){
                    HistoryList.append(new QStandardItem(json_file.get_currency(i)));
                }
                    //qDebug() << json_file.get_address_recipient(c);
                    count++;
                    //qDebug() << count;
                }
            for(int i = 0; i < count; i++)
            {
                HistoryList[i]->setTextAlignment(Qt::AlignCenter);
            }
            history_view_model->insertRow(history_view_model->rowCount(), HistoryList);
        //HistoryList.close();
        }
}

bool MainWindow::isAmountCorrect(double amount, CoinsType coins_type)
{
    Balance this_user = val_1.getChain().getLastBlock().getUserBalance(wallet_address);
    switch (coins_type) {
    case BWC:
        if(this_user.getBalance(BWC) >= amount)
        {
            return true;
        }
        break;
    case BWC_N:
        if(this_user.getBalance(BWC_N) >= amount)
        {
            return true;
        }
        break;
    case BWC_Q:
        if(this_user.getBalance(BWC_Q) >= amount)
        {
            return true;
        }
        break;
    default:
        break;
    }
    return false;
}

void MainWindow::setWindowLanguage()
{
    // need rework
    switch (ui_Settings.languageIndex) {
    case ENGLISH:
        ui_Auth.setWindowLanguage(ui_Settings.languageIndex);
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

        about_program->setText("&About Wallet");
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
    case UKRANIAN:
        ui_Auth.setWindowLanguage(ui_Settings.languageIndex);
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
    case RUSSIAN:
        ui_Auth.setWindowLanguage(ui_Settings.languageIndex);
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
    default:
        break;
    }
}

void MainWindow::on_sendCoinsButton_clicked()
{
    try {
        if(!isAmountCorrect(amount + fee, coins_type))
        {
            throw ProgramException(INVALID_COINS_VALUE);
        }
        QDateTime timeStamp = QDateTime::currentDateTime();

        int max_authority = std::max(val_1.getAuthority(), val_2.getAuthority());
        qDebug() << max_authority;
        max_authority = std::max(max_authority, val_3.getAuthority());
        qDebug() << max_authority;

        int min_authority = std::min(val_1.getAuthority(), val_2.getAuthority());
        min_authority = std::min(min_authority, val_3.getAuthority());

        switch (priority) {
        case 1:
            if(val_1.getAuthority() == max_authority)
            {
                emit sendButton_clicked_val_1(TransactionData(wallet_address, reciever_address, amount, coins_type, fee, priority));
            }
            else if(val_2.getAuthority() == max_authority)
            {
                emit sendButton_clicked_val_2(TransactionData(wallet_address, reciever_address, amount, coins_type, fee, priority));
            }
            else if(val_3.getAuthority() == max_authority)
            {
                emit sendButton_clicked_val_3(TransactionData(wallet_address, reciever_address, amount, coins_type, fee, priority));
            }
            break;
        case 2:
            if(val_1.getAuthority() < max_authority && val_1.getAuthority() > min_authority)
            {
                emit sendButton_clicked_val_1(TransactionData(wallet_address, reciever_address, amount, coins_type, fee, priority));
            }
            else if(val_2.getAuthority() < max_authority && val_2.getAuthority() > min_authority)
            {
                emit sendButton_clicked_val_2(TransactionData(wallet_address, reciever_address, amount, coins_type, fee, priority));
            }
            else if(val_3.getAuthority() < max_authority && val_3.getAuthority() > min_authority)
            {
                emit sendButton_clicked_val_3(TransactionData(wallet_address, reciever_address, amount, coins_type, fee, priority));
            }
            break;
        case 3:
            if(val_1.getAuthority() == min_authority)
            {
                emit sendButton_clicked_val_1(TransactionData(wallet_address, reciever_address, amount, coins_type, fee, priority));
            }
            else if(val_2.getAuthority() == min_authority)
            {
                emit sendButton_clicked_val_2(TransactionData(wallet_address, reciever_address, amount, coins_type, fee, priority));
            }
            else if(val_3.getAuthority() == min_authority)
            {
                emit sendButton_clicked_val_3(TransactionData(wallet_address, reciever_address, amount, coins_type, fee, priority));
            }
            break;
        default:
            break;
        }

        emit addTransactionCard(transaction_label, timeStamp.toString(), amount, coins_type, 0);

        Balance current_user = val_1.getChain().getLastBlock().getUserBalance(wallet_address);

        ui->bwcBalance->setText(QString::number(current_user.getBalance(BWC)));
        ui->bwcNBalance->setText(QString::number(current_user.getBalance(BWC_N)));
        ui->bwcQBalance->setText(QString::number(current_user.getBalance(BWC_Q)));
    }  catch (ProgramException &error) {
        error.getError();
    }

}


void MainWindow::on_amountSpinBox_valueChanged(double arg1)
{
    this->amount = arg1;
    if(recomActivated)
    {
        emit on_recomValueButton_clicked();
    }
    else
    {
        emit on_priorityComboBox_currentIndexChanged(0);
    }
}


void MainWindow::on_feeCheckBox_stateChanged(int arg1)
{

}


void MainWindow::on_priorityComboBox_currentIndexChanged(int index)
{
    switch(index) {
    case 0:
        fee = amount * 0.15;
        priority = 1;
        ui->customValueLE->setText(QString::number(fee));
        break;
    case 1:
        fee = amount * 0.10;
        priority = 2;
        ui->customValueLE->setText(QString::number(fee));
        break;
    case 2:
        fee = amount * 0.05;
        priority = 3;
        ui->customValueLE->setText(QString::number(fee));
        break;
    default:
        break;
    }
}


void MainWindow::on_customValueButton_clicked()
{
    recomActivated = false;
    ui->priorityComboBox->setEnabled(true);
    ui->priorityComboBox->setCurrentIndex(0);
    emit on_priorityComboBox_currentIndexChanged(0);
}


void MainWindow::on_recomValueButton_clicked()
{
    recomActivated = true;
    ui->priorityComboBox->setEnabled(false);
    fee = amount * 0.05;
    priority = 3;
    ui->recomValueLE->setText(QString::number(fee));
}


void MainWindow::on_coinsBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        this->coins_type = BWC;
        break;
    case 1:
        this->coins_type = BWC_N;
        break;
    case 2:
        this->coins_type = BWC_Q;
        break;
    default:
        break;
    }
}

void MainWindow::on_sendTransactionLabel_textChanged(const QString &arg1)
{
    this->transaction_label = arg1;
}

MainWindow::~MainWindow()
{
    delete ui;

    delete request_view_model;

    delete home;
    delete send;
    delete recieve;
    delete transactions;

    delete all_blocks;

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
}


void MainWindow::on_clearSendButton_clicked()
{
    ui->payToAddress->clear();
    ui->sendTransactionLabel->clear();
    ui->amountSpinBox->clear();
}

