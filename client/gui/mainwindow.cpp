#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    try {
        fileExists("requestsList.csv");
        setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    }  catch (ProgramException &error) {
        error.getError();
    }
    ui->priorityComboBox->setEnabled(false);

    val_1.setAuthority(100);
    val_2.setAuthority(75);
    val_3.setAuthority(1);

    val_1.getBlockChain().show();

    qRegisterMetaType<TransactionData>("TransactionData");

    createActions();
    createMenus();
    createTrayMenu();
    uiChanges();
    requestsHistory();

    connect(&ui_Auth, SIGNAL(login_button_clicked()), this, SLOT(authorizeUser()));
    connect(&ui_Auth, SIGNAL(register_button_clicked()), this, SLOT(registerUser()));
    connect(&ui_Auth, SIGNAL(destroyed()), this, SLOT(show()));

    connect(&ui_Settings, SIGNAL(languageChanged(QVector<QString>)), this, SLOT(setWindowLanguage(QVector<QString>)));
    connect(this, SIGNAL(languageChanged(QVector<QString>)), &ui_Auth, SLOT(setWindowLanguage(QVector<QString>)));

    connect(&ui_Settings, SIGNAL(trayCheckBoxToggled()), this, SLOT(trayEnabled()));

    connect(&ui_Settings, SIGNAL(coinsTypeChanged(int)), this, SLOT(on_coinsBox_currentIndexChanged(int)));

    connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    connect(this, SIGNAL(sendButton_clicked_val_1(TransactionData)), &val_1, SLOT(addTransaction(TransactionData)), Qt::QueuedConnection);
    connect(this, SIGNAL(sendButton_clicked_val_2(TransactionData)), &val_2, SLOT(addTransaction(TransactionData)), Qt::QueuedConnection);
    connect(this, SIGNAL(sendButton_clicked_val_3(TransactionData)), &val_3, SLOT(addTransaction(TransactionData)), Qt::QueuedConnection);

    connect(&val_1, SIGNAL(sendTransaction(QString,TransactionData)), this, SLOT(newTransaction(QString,TransactionData)));
    connect(&val_2, SIGNAL(sendTransaction(QString,TransactionData)), this, SLOT(newTransaction(QString,TransactionData)));
    connect(&val_3, SIGNAL(sendTransaction(QString,TransactionData)), this, SLOT(newTransaction(QString,TransactionData)));

    connect(this, SIGNAL(allBlocksView_next_clicked()), this, SLOT(blocksNext()));
    connect(this, SIGNAL(allBlocksView_prev_clicked()), this, SLOT(blocksPrev()));

    connect(this, SIGNAL(sendWalletPass(QString)), &ui_ChangePass, SLOT(recieveOldWalletPass(QString)));

    ui->stackedWidget->setCurrentIndex(0);
    //setWindowLanguage();

    //statusBar()->showMessage("Connected...");
    ui_Settings.setWindowLanguage();
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

void MainWindow::display()
{
    ui_Auth.show();
}

void MainWindow::authorizeUser()
{
    try {
        algoritms use_algoritm;

        wallet_key = ui_Auth.getInputKey();

        JSON file("users.json");
        QVector<QString> valid_keys = file.get_users_info(JSON::KEY);

        //QVector<QString> valid_keys = getUsersInfo(KEY);

        int index = valid_keys.indexOf(QString::fromStdString(use_algoritm.Hash(wallet_key.toStdString() + "SALT")));

        if(index != -1)
        {
            ui_Auth.close();
            Sleep(250);
            QVector<QString> user_address = file.get_users_info(JSON::ADDRESS);
            //QVector<QString> user_address = getUsersInfo(ADDRESS);
            wallet_address = user_address[index];

            Balance current_user = val_1.getBlockChain().getLastBlock().getUserBalance(wallet_address);

            QVector<QString> users_admin = file.get_users_info(JSON::ADMIN);
            //QVector<QString> users_admin = getUsersInfo(ADMIN);
            QString admin_check = users_admin[index];

            if(admin_check == "0")
            {
                main_menu->removeAction(all_blocks);
                toolbar->removeAction(all_blocks);
            }

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

        JSON file("users.json");
        file.registerNewUser(wallet_address, wallet_key + "SALT");


        //registerNewUsers(wallet_address, wallet_key + "SALT");

        /*QPalette palette;
        QColor color;

        color = ui->walletKeyLabel->parentWidget()->palette().color(QPalette);
        palette.setColor(QPalette::Base,color);
        ui->walletKeyLabel->setPalette(palette);*/

        ui->walletKeyLabel->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

        ui->walletAddressLabel->setText(wallet_address);
        ui->walletKeyLabel->setText(wallet_key);

        main_menu->removeAction(all_blocks);
        toolbar->removeAction(all_blocks);

        ui_Auth.close();
        Sleep(250);

        Balance current_user = val_1.getBlockChain().getLastBlock().getUserBalance(wallet_address);

        ui->bwcBalance->setText(QString::number(current_user.getBalance(BWC)));
        ui->bwcNBalance->setText(QString::number(current_user.getBalance(BWC_N)));
        ui->bwcQBalance->setText(QString::number(current_user.getBalance(BWC_Q)));

        this->show();
        throw ProgramException(SAVE_PASSPHRASE, wallet_key);
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
    QPixmap recievepix("icons/recieveIcon.jpg");
    QPixmap helppix("icons/helpIcon.png");
    QPixmap transactionspix("icons/transactionsIcon.png");
    QPixmap all_blockspix("icons/all_blocksIcon.png");
    QPixmap quitpix("icons/quitIcon.png");

    //QPixmap programpix("icons/programIcon.png");


    home = new QAction(homepix, "&Home", this);
    send = new QAction(sendpix, "&Send", this);
    recieve = new QAction(recievepix, "&Recieve", this);
    help = new QAction(helppix, "&Help", this);
    all_blocks = new QAction(all_blockspix, "&Blocks", this);
    quit = new QAction(quitpix, "&Quit", this);

    quit->setShortcut(tr("Ctrl+Q"));

    transactions = new QAction(transactionspix, "&Transactions", this);
    change_passphrase = new QAction("&Change Passphrase...", this);
    options = new QAction("&Options...", this);

    about_program = new QAction("&About Wallet", this);
    about_of_authors = new QAction("&About Authors", this);

    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
    connect(home, &QAction::triggered, this, &MainWindow::homeTR);
    connect(send, &QAction::triggered, this, &MainWindow::sendTR);
    connect(recieve, &QAction::triggered, this, &MainWindow::recieveTR);
    connect(transactions, &QAction::triggered, this, &MainWindow::transactionsTR);

    connect(all_blocks, &QAction::triggered, this, &MainWindow::blocksTR);

    connect(options, &QAction::triggered, &ui_Settings, &settings_Form::settingsShow);
    connect(about_program, &QAction::triggered, &ui_AboutProgram, &about_program_Form::aboutShow);
    connect(about_of_authors, &QAction::triggered, &ui_AboutAuthors, &about_of_authors::aboutAuth);
    connect(change_passphrase, &QAction::triggered, &ui_ChangePass, &change_passphrase_Form::changePassphraseShow);
    connect(change_passphrase, &QAction::triggered, this, &MainWindow::sendWalletPassToChangeForm);
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

    settings_menu->addAction(change_passphrase);
    settings_menu->addSeparator();
    settings_menu->addAction(options);

    help_menu = menuBar()->addMenu("&Help");

    help_menu->addAction(about_program);
    help_menu->addSeparator();
    help_menu->addAction(about_of_authors);

//    QMenu* menu = new QMenu("about_program"); //помощь
//        menu->addAction(about_program);
//        menu->addAction(home); //about autors
//        help_menu->addMenu(menu);

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
//    ui->payToAddress->setPlaceholderText("Enter wallet-address");
//    ui->sendTransactionLabel->setPlaceholderText("Enter a label for this address to add it to your address book");

//    ui->requestLabelLine->setPlaceholderText("263 stroka, plz changed");
//    ui->messageLine->setPlaceholderText("264 stroka, plz changed");

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

    new_card->setData(label, timeStamp, amount, coins_type, transaction_type);
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
    if(val_1.getBlockChain().getChainLenght() > val_2.getBlockChain().getChainLenght())
    {
        val_2.setBlockChain(val_1.getBlockChain());
    }
    if(val_2.getBlockChain().getChainLenght() > val_1.getBlockChain().getChainLenght())
    {
        val_1.setBlockChain(val_2.getBlockChain());
    }
    if(val_1.getBlockChain().getChainLenght() > val_3.getBlockChain().getChainLenght())
    {
        val_3.setBlockChain(val_1.getBlockChain());
    }
    if(val_3.getBlockChain().getChainLenght() > val_1.getBlockChain().getChainLenght())
    {
        val_1.setBlockChain(val_3.getBlockChain());
    }
    if(val_3.getBlockChain().getChainLenght() > val_2.getBlockChain().getChainLenght())
    {
        val_2.setBlockChain(val_3.getBlockChain());
    }
    if(val_2.getBlockChain().getChainLenght() > val_3.getBlockChain().getChainLenght())
    {
        val_3.setBlockChain(val_2.getBlockChain());
    }

    if(wallet_address == this->wallet_address)
    {
        Balance current_user = val_1.getBlockChain().getLastBlock().getUserBalance(wallet_address);

        ui->bwcBalance->setText(QString::number(current_user.getBalance(BWC)));
        ui->bwcNBalance->setText(QString::number(current_user.getBalance(BWC_N)));
        ui->bwcQBalance->setText(QString::number(current_user.getBalance(BWC_Q)));

        emit addTransactionCard(data.getSender(), data.getTimeStamp(), data.getAmount(), data.getCoinsType(), 1);
    }
    else
    {
        Balance current_user = val_1.getBlockChain().getLastBlock().getUserBalance(this->wallet_address);

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

    ui->requestsView->setEditTriggers( QAbstractItemView::NoEditTriggers);

    ui->requestsView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->requestsView-> horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    QString styleSheet_1 = "::section {"
                         "spacing: 10px;"
                         "background-color: lightblue;"
                         "color: black;"
                         "border: 1px solid black;"
                         "margin: 1px;"
                         "font-weight: bold;"
                         "font-family: arial;"
                         "font-size: 15px; }";

    ui->requestsView->horizontalHeader()->setStyleSheet(styleSheet_1);

    ui->requestsView->verticalHeader()->setVisible(false);

    ui->requestsView->setColumnWidth(0,100);
    ui->requestsView->setColumnWidth(1,200);
    ui->requestsView->setColumnWidth(2,350);
    ui->requestsView->setColumnWidth(3,108);

    CSV file("requestsList.csv");

    for(int index = 1; index < file.get_amount_row(); index++)
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

        QString styleSheet_2 = "::section {"
                             "spacing: 10px;"
                             "background-color: lightblue;"
                             "color: black;"
                             "border: 1px solid black;"
                             "margin: 1px;"
                             "font-weight: bold;"
                             "font-family: arial;"
                             "font-size: 15px; }";

        ui->historyView->horizontalHeader()->setStyleSheet(styleSheet_2);

        ui->historyView->verticalHeader()->setVisible(false);

        ui->historyView->setEditTriggers( QAbstractItemView::NoEditTriggers);
        ui->historyView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        ui->historyView-> horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

        ui->historyView->setColumnWidth(0,100);
        ui->historyView->setColumnWidth(1,225);
        ui->historyView->setColumnWidth(2,225);
        ui->historyView->setColumnWidth(3,108);
        ui->historyView->setColumnWidth(4,108);

        JSON json_file("chain.json");
        //qDebug() << json_file.get_array_size();

        for(int i = 1; i <= json_file.new_get_array_size_blockchain(); i++){
            QList<QStandardItem *> HistoryList;
            int count = 0;
            for(int c = 0; c < 5; c++){
                if(c == 0){
                    HistoryList.append(new QStandardItem(QString::number(json_file.new_get_id(i))));
                }else if(c == 1){
                    HistoryList.append(new QStandardItem(json_file.new_get_sender(i, 0)));
                }else if(c == 2){
                    HistoryList.append(new QStandardItem(json_file.new_get_reciever(i, 0)));
                }else if(c == 3){
                    HistoryList.append(new QStandardItem(QString::number(json_file.new_get_amount(i, 0))));
                }else if(c == 4){
                    HistoryList.append(new QStandardItem(json_file.new_get_fee(i, 0)));
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
    Balance this_user = val_1.getBlockChain().getLastBlock().getUserBalance(wallet_address);
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

void MainWindow::setWindowLanguage(QVector<QString> language_vector)
{
    this->setWindowTitle(language_vector.at(57));

           main_menu->setTitle(language_vector.at(1));
           settings_menu->setTitle(language_vector.at(0));
           help_menu->setTitle(language_vector.at(41));

           home->setText(language_vector.at(42));
           send->setText(language_vector.at(43));
           recieve->setText(language_vector.at(44));
           transactions->setText(language_vector.at(45));

           help->setText(language_vector.at(46));
           quit->setText(language_vector.at(47));

           change_passphrase->setText(language_vector.at(48));
           options->setText(language_vector.at(0));

           about_program->setText(language_vector.at(49));
           about_of_authors->setText(language_vector.at(65));
           view_window->setText(language_vector.at(50));

           ui->sendCoinsButton->setText(language_vector.at(43));
           ui->addToAddressBookLabel->setText(language_vector.at(25));
           ui->payToLabel->setText(language_vector.at(22));
           ui->amountLabel->setText(language_vector.at(36));
           ui->balanceLabel->setText(language_vector.at(18));
           ui->commissionLabel->setText(language_vector.at(38));
           ui->feeCheckBox->setText(language_vector.at(51));

           ui->transactionsOverviewLabel->setText(language_vector.at(21));
           ui->addresslabel->setText(language_vector.at(19));
           ui->keylabel->setText(language_vector.at(20));

           ui->recomValueButton->setText(language_vector.at(52));
           ui->customValueButton->setText(language_vector.at(53));

           ui->balanceTextLabel->setText(language_vector.at(18));
           ui->sendCoinsButton->setText(language_vector.at(43));
           ui->clearSendButton->setText(language_vector.at(17));

           ui->requestLabel->setText(language_vector.at(23));
           ui->amountToRecieveLabel->setText(language_vector.at(24));
           ui->messageLabel->setText(language_vector.at(25));

           ui->requestButton->setText(language_vector.at(26));
           ui->clearRequestButton->setText(language_vector.at(27));

           ui->historyLabel->setText(language_vector.at(28));

           ui->transactionsLabel->setText(language_vector.at(29));

           ui->idLabel->setText(language_vector.at(30));
           ui->hashLabel->setText(language_vector.at(31));
           ui->prevHashLabel->setText(language_vector.at(32));
           ui->senderLabel->setText(language_vector.at(33));
           ui->recieverLabel->setText(language_vector.at(34));
           ui->timestampLabel->setText(language_vector.at(35));
           ui->amountLabel_2->setText(language_vector.at(36));
           ui->coinstypeLabel->setText(language_vector.at(37));
           ui->feeLabel->setText(language_vector.at(38));

           ui->prevBlockBTN->setText(language_vector.at(39));
           ui->nextBlockBTN->setText(language_vector.at(40));

           ui->priorityComboBox->setItemText(0, language_vector.at(54));
           ui->priorityComboBox->setItemText(1, language_vector.at(55));
           ui->priorityComboBox->setItemText(2, language_vector.at(56));

           ui->payToAddress->setPlaceholderText(language_vector.at(61));
           ui->sendTransactionLabel->setPlaceholderText(language_vector.at(62));

           ui->requestLabelLine->setPlaceholderText(language_vector.at(63));
           ui->messageLine->setPlaceholderText(language_vector.at(64));



           //view_window = new QAction("&Show Window", this);


           statusBar()->showMessage(language_vector.at(58));

           emit languageChanged(language_vector);
}

void MainWindow::on_sendCoinsButton_clicked()
{
    try {
        if(reciever_address.length() != 17)
        {
            throw ProgramException(INVALID_ADDRESS);
        }
        QVector<QString> exists_address = getUsersInfo(ADDRESS);
        int exist_flag = exists_address.indexOf(reciever_address);
        if(exist_flag == -1)
        {
            throw ProgramException(ADDRESS_NOT_EXISTS);
        }
        if(!isAmountCorrect(amount + fee, coins_type))
        {
            throw ProgramException(INVALID_COINS_VALUE);
        }
        QDateTime timeStamp = QDateTime::currentDateTime();

        int max_authority = std::max(std::max(val_1.getAuthority(), val_2.getAuthority()), val_3.getAuthority());

        int min_authority = std::min(std::min(val_1.getAuthority(), val_2.getAuthority()), val_3.getAuthority());

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
    fee = round(amount * 0.05 * 100)/100;
    priority = 3;
    ui->recomValueLE->setText(QString::number(fee));
}


void MainWindow::on_coinsBox_currentIndexChanged(int index)
{
    ui->coinsBox->setCurrentIndex(index);
    switch (index) {
    case 0:
        this->coins_type = BWC;
        ui->balanceCoins->setText(ui->bwcBalance->text() + " BWC");
        break;
    case 1:
        this->coins_type = BWC_N;
        ui->balanceCoins->setText(ui->bwcNBalance->text() + " BWC-N");
        break;
    case 2:
        this->coins_type = BWC_Q;
        ui->balanceCoins->setText(ui->bwcQBalance->text() + " BWC-Q");
        break;
    default:
        break;
    }
}

void MainWindow::on_sendTransactionLabel_textChanged(const QString &arg1)
{
    this->transaction_label = arg1;
}

void MainWindow::on_clearSendButton_clicked()
{
    ui->payToAddress->clear();
    ui->sendTransactionLabel->clear();
    ui->amountSpinBox->clear();
}

QString coinsTypeToString(CoinsType coins_type)
{
    switch (coins_type) {
    case BWC:
        return "BWC";
        break;
    case BWC_N:
        return "BWC-N";
        break;
    case BWC_Q:
        return "BWC-Q";
        break;
    default:
        return "BWC";
        break;
    }
}


void MainWindow::on_prevBlockBTN_clicked()
{
    emit allBlocksView_prev_clicked();
}


void MainWindow::on_nextBlockBTN_clicked()
{
    emit allBlocksView_next_clicked();
}

void MainWindow::blocksPrev()
{
    if(block_index > 0)
    {
        block_index--;
        ui->idInf->setText(QString::number(val_1.getBlockChain().getBlock(block_index).getIndex()));
        ui->hashInf->setText(val_1.getBlockChain().getBlock(block_index).getBlockHash());
        ui->prevHashInf->setText(val_1.getBlockChain().getBlock(block_index).getPrevBlockHash());
        ui->senderInf->setText(val_1.getBlockChain().getBlock(block_index).getBlockData().getSender());
        ui->recieverInf->setText(val_1.getBlockChain().getBlock(block_index).getBlockData().getReciever());
        ui->timestampInf->setText(val_1.getBlockChain().getBlock(block_index).getBlockData().getTimeStamp());
        ui->amountInf->setText(QString::number(val_1.getBlockChain().getBlock(block_index).getBlockData().getAmount()));
        ui->coinsTypeInf->setText(coinsTypeToString(val_1.getBlockChain().getBlock(block_index).getBlockData().getCoinsType()));
        ui->feeInf->setText(QString::number(val_1.getBlockChain().getBlock(block_index).getBlockData().getFee()));
    }
}

void MainWindow::blocksNext()
{
    if(block_index < val_1.getBlockChain().getChainLenght() - 1)
    {
        block_index++;
        ui->idInf->setText(QString::number(val_1.getBlockChain().getBlock(block_index).getIndex()));
        ui->hashInf->setText(val_1.getBlockChain().getBlock(block_index).getBlockHash());
        ui->prevHashInf->setText(val_1.getBlockChain().getBlock(block_index).getPrevBlockHash());
        ui->senderInf->setText(val_1.getBlockChain().getBlock(block_index).getBlockData().getSender());
        ui->recieverInf->setText(val_1.getBlockChain().getBlock(block_index).getBlockData().getReciever());
        ui->timestampInf->setText(val_1.getBlockChain().getBlock(block_index).getBlockData().getTimeStamp());
        ui->amountInf->setText(QString::number(val_1.getBlockChain().getBlock(block_index).getBlockData().getAmount()));
        ui->coinsTypeInf->setText(coinsTypeToString(val_1.getBlockChain().getBlock(block_index).getBlockData().getCoinsType()));
        ui->feeInf->setText(QString::number(val_1.getBlockChain().getBlock(block_index).getBlockData().getFee()));
    }
}

void MainWindow::sendWalletPassToChangeForm()
{
    emit sendWalletPass(wallet_key);
}

