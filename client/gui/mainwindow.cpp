#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->priorityComboBox->setEnabled(false);
    ui->putLinkLE->setDisabled(true);

    try {
        JSON file_json("users.json");
        file_json.read_users_file(users_information);

        val_1.setAuthority(100);
        val_2.setAuthority(75);
        val_3.setAuthority(25);
    }  catch (ProgramException &error) {
        error.getError();
    }

    request_view_model = new QStandardItemModel(this);
    history_view_model = new QStandardItemModel(this);


    qRegisterMetaType<TransactionData>("TransactionData");

    createActions();
    createMenus();
    createTrayMenu();

    connect(&ui_Auth, SIGNAL(login_button_clicked()), this, SLOT(authorizeUser()));
    connect(&ui_Auth, SIGNAL(register_button_clicked()), this, SLOT(registerUser()));
    connect(&ui_Auth, SIGNAL(destroyed()), this, SLOT(show()));

    connect(&ui_Settings, SIGNAL(languageChanged(QVector<QString>, int)), this, SLOT(setWindowLanguage(QVector<QString>, int)));

    connect(this, SIGNAL(languageChanged(QVector<QString>)), &ui_Auth, SLOT(setWindowLanguage(QVector<QString>)));
    connect(this, SIGNAL(languageChanged(int)), &ui_AboutProgram, SLOT(setWindowLanguage(int)));
    connect(this, SIGNAL(languageChanged(int)), &ui_AboutAuthors, SLOT(setWindowLanguage(int)));
    connect(this, SIGNAL(languageChanged(int)), &ui_ChangePass, SLOT(setWindowLanguage(int)));

    connect(&ui_Settings, SIGNAL(trayCheckBoxToggled()), this, SLOT(trayEnabled()));

    connect(&ui_Settings, SIGNAL(coinsTypeChanged(int)), this, SLOT(on_coinsBox_currentIndexChanged(int)));
    connect(&ui_Settings, SIGNAL(coinsTypeChanged(int)), this, SLOT(on_coinsBox_2_currentIndexChanged(int)));

    connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    connect(this, SIGNAL(sendButton_clicked_val_1(TransactionData)), &val_1, SLOT(addTransaction(TransactionData)), Qt::QueuedConnection);
    connect(this, SIGNAL(sendButton_clicked_val_2(TransactionData)), &val_2, SLOT(addTransaction(TransactionData)), Qt::QueuedConnection);
    connect(this, SIGNAL(sendButton_clicked_val_3(TransactionData)), &val_3, SLOT(addTransaction(TransactionData)), Qt::QueuedConnection);

    connect(&val_1, SIGNAL(sendTransaction(QString,TransactionData)), this, SLOT(newTransaction(QString,TransactionData)));
    connect(&val_2, SIGNAL(sendTransaction(QString,TransactionData)), this, SLOT(newTransaction(QString,TransactionData)));
    connect(&val_3, SIGNAL(sendTransaction(QString,TransactionData)), this, SLOT(newTransaction(QString,TransactionData)));

    connect(this, SIGNAL(allBlocksView_next_clicked()), this, SLOT(blocksNext()));
    connect(this, SIGNAL(allBlocksView_prev_clicked()), this, SLOT(blocksPrev()));

    connect(this, SIGNAL(sendUserInformation(User&,Users&)), &ui_ChangePass, SLOT(currentUserPassChange(User&, Users&)));

    connect(this, SIGNAL(requestButton_clicked()), this, SLOT(createLink()));

    connect(this, SIGNAL(loadUserSettings(User&)), &ui_Settings, SLOT(loadSettings(User&)));

    ui->stackedWidget->setCurrentIndex(0);

    ui_Settings.setWindowLanguage();
}

MainWindow::~MainWindow()
{
    delete ui;

    delete home;
    delete send;
    delete recieve;
    delete transactions;

    delete all_blocks;

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
        wallet_key = ui_Auth.getInputKey();

        if(users_information.isPasswordExists(wallet_key))
        {
            ui_Auth.close();
            Sleep(250);
            current_user = users_information.getUser(wallet_key);

            Balance current_user_balance = val_1.getBlockChain().getLastBlock().getUserBalance(current_user.getAddress());

            if(!current_user.isAdmin())
            {
                main_menu->removeAction(all_blocks);
                toolbar->removeAction(all_blocks);
            }
            emit allBlocksView_next_clicked();

            ui->bwcBalance->setText(QString::number(current_user_balance.getBalance(BWC)));
            ui->bwcNBalance->setText(QString::number(current_user_balance.getBalance(BWC_N)));
            ui->bwcQBalance->setText(QString::number(current_user_balance.getBalance(BWC_Q)));

            emit on_coinsBox_currentIndexChanged(current_user.getUserPreferCoinsType());
            emit loadUserSettings(current_user);

            ui->walletAddressLabel->setText(current_user.getAddress());
            ui->walletKeyLabel->setText(wallet_key);

            ui->walletKeyLabel->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

            val_1.loadTransactions();

            this->show();
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
        users_information.addUser(User(wallet_address, wallet_key, true));

        JSON file("users.json");
        file.write_users_file(users_information);

        current_user = users_information.getUser(wallet_key);

        ui->walletKeyLabel->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

        ui->walletAddressLabel->setText(wallet_address);
        ui->walletKeyLabel->setText(wallet_key);

        main_menu->removeAction(all_blocks);
        toolbar->removeAction(all_blocks);

        ui_Auth.close();
        Sleep(250);

        Balance current_user_balance = val_1.getBlockChain().getLastBlock().getUserBalance(wallet_address);

        ui->bwcBalance->setText(QString::number(current_user_balance.getBalance(BWC)));
        ui->bwcNBalance->setText(QString::number(current_user_balance.getBalance(BWC_N)));
        ui->bwcQBalance->setText(QString::number(current_user_balance.getBalance(BWC_Q)));

        emit on_coinsBox_currentIndexChanged(0);
        requestsHistory();

        emit loadUserSettings(current_user);
        this->show();
        throw ProgramException(SAVE_PASSWORD, wallet_key);
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
    QPixmap transactionspix("icons/transactionsIcon.png");
    QPixmap all_blockspix("icons/all_blocksIcon.png");
    QPixmap quitpix("icons/quitIcon.png");

    home = new QAction(homepix, "&Home", this);
    send = new QAction(sendpix, "&Send", this);
    recieve = new QAction(recievepix, "&Recieve", this);
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
        ui_AboutAuthors.close();
        ui_Auth.close();
        ui_ChangePass.close();
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
    try {
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

        if(wallet_address == current_user.getAddress())
        {
            Balance current_user_balance = val_1.getBlockChain().getLastBlock().getUserBalance(current_user.getAddress());

            ui->bwcBalance->setText(QString::number(current_user_balance.getBalance(BWC)));
            ui->bwcNBalance->setText(QString::number(current_user_balance.getBalance(BWC_N)));
            ui->bwcQBalance->setText(QString::number(current_user_balance.getBalance(BWC_Q)));

            emit addTransactionCard(data.getSender(), data.getTimeStamp(), data.getAmount(), data.getCoinsType(), 1);
        }
        else if(data.getSender() == current_user.getAddress())
        {
            Balance current_user_balance = val_1.getBlockChain().getLastBlock().getUserBalance(current_user.getAddress());

            ui->bwcBalance->setText(QString::number(current_user_balance.getBalance(BWC)));
            ui->bwcNBalance->setText(QString::number(current_user_balance.getBalance(BWC_N)));
            ui->bwcQBalance->setText(QString::number(current_user_balance.getBalance(BWC_Q)));

            emit addTransactionCard(data.getReciever(), data.getTimeStamp(), data.getAmount(), data.getCoinsType(), 0);
        }
        else
        {
            Balance current_user_balance = val_1.getBlockChain().getLastBlock().getUserBalance(current_user.getAddress());

            ui->bwcBalance->setText(QString::number(current_user_balance.getBalance(BWC)));
            ui->bwcNBalance->setText(QString::number(current_user_balance.getBalance(BWC_N)));
            ui->bwcQBalance->setText(QString::number(current_user_balance.getBalance(BWC_Q)));
        }
        request_view_model->clear();
        history_view_model->clear();
        requestsHistory();
    }  catch (ProgramException &error) {
        error.getError();
    }
}

void MainWindow::on_payToAddress_textChanged(const QString &arg1)
{
    this->reciever_address = arg1;
}

QString toCoinsType2(int CoinId)
{
    switch (CoinId) {
    case 0:
        return "BWC";
        break;
    case 1:
        return "BWC-N";
        break;
    case 2:
        return "BWC-Q";
        break;
    default:
        break;
    }
}

void MainWindow::requestsHistory()
{
    try {
        CSV file("requestsList.csv");
        QVector<QString> str_request = file.find_user(current_user.getAddress());
        request_view_model->setColumnCount(4);

        request_view_model->setHorizontalHeaderLabels(QStringList() << table_translation.at(0) << table_translation.at(1) << table_translation.at(2) << table_translation.at(3));

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

        ui->requestsView->setColumnWidth(0,300);
        ui->requestsView->setColumnWidth(1,280);
        ui->requestsView->setColumnWidth(2,80);
        ui->requestsView->setColumnWidth(3,100);
        //ui->requestsView->setColumnWidth(4,150);

        for(int index = 0; index < str_request.size(); index++)
        {
            QList<QStandardItem *> newRequestsList;
            for(int c = 1; c <= 4; c++)
            {
                switch(c){
                case 1:
                    newRequestsList.append(new QStandardItem(str_request.at(index).section(',', 0, 0)));
                    break;
                case 2:
                    newRequestsList.append(new QStandardItem(str_request.at(index).section(',', 1, 1)));
                    break;
                case 3:
                    newRequestsList.append(new QStandardItem(str_request.at(index).section(',', 2, 2)));
                    break;
                case 4:
                    newRequestsList.append(new QStandardItem(str_request.at(index).section(',', 3, 3)));
                    break;
                default:
                    break;
                }
            }
            for(int i = 0; i < newRequestsList.length(); i++)
            {
                newRequestsList[i]->setTextAlignment(Qt::AlignCenter);
            }
            request_view_model->appendRow(newRequestsList);
        }

        JSON json_file("chain.json");

        history_view_model->setColumnCount(6);

        history_view_model->setHorizontalHeaderLabels(QStringList() << "???" << table_translation.at(4) << table_translation.at(5) << table_translation.at(6) << table_translation.at(7) << table_translation.at(3) << table_translation.at(8));

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

        ui->historyView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->historyView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        ui->historyView-> horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

        ui->historyView->setColumnWidth(0,100);
        ui->historyView->setColumnWidth(1,225);
        ui->historyView->setColumnWidth(2,225);
        ui->historyView->setColumnWidth(3,108);
        ui->historyView->setColumnWidth(4,108);
        ui->historyView->setColumnWidth(5,108);
        ui->historyView->setColumnWidth(6,250);
        int num = 0;
        for(int i = 1; i <= json_file.get_array_size_blockchain(); i++)
        {
            QList<QStandardItem *> HistoryList;

            int count = 0;
            if((json_file.get_sender(i) == current_user.getAddress()) || (json_file.get_reciever(i) == current_user.getAddress())){
                num++;
            for(int c = 0; c < 7; c++){
                if(c == 0){
                    HistoryList.append(new QStandardItem(QString::number(num)));
                }else if(c == 1){
                    HistoryList.append(new QStandardItem(json_file.get_sender(i)));
                }else if(c == 2){
                    HistoryList.append(new QStandardItem(json_file.get_reciever(i)));
                }else if(c == 3){
                    HistoryList.append(new QStandardItem(QString::number(json_file.get_amount(i))));
                }else if(c == 4){
                    HistoryList.append(new QStandardItem(QString::number(json_file.get_fee(i))));
                }else if(c == 5){
                    HistoryList.append(new QStandardItem(toCoinsType2(json_file.get_CoinsType(i))));
                }else if(c == 6){
                    HistoryList.append(new QStandardItem(json_file.get_timestamp(i)));
                }
                count++;
            }
            for(int i = 0; i < count; i++)
            {
                HistoryList[i]->setTextAlignment(Qt::AlignCenter);
            }
            history_view_model->appendRow(HistoryList);
            }
        }
        num = 0;

    }  catch (ProgramException &error) {
        error.getError();
    }
}

bool MainWindow::isAmountCorrect(double amount, CoinsType coins_type)
{
    try {
        Balance this_user = val_1.getBlockChain().getLastBlock().getUserBalance(current_user.getAddress());
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
    }  catch (ProgramException &error) {
        error.getError();
    }
}

void MainWindow::setWindowLanguage(QVector<QString> language_vector, int language_index)
{
    this->setWindowTitle(language_vector.at(57));

    main_menu->setTitle(language_vector.at(1));
    settings_menu->setTitle(language_vector.at(0));
    help_menu->setTitle(language_vector.at(41));

    home->setText(language_vector.at(42));
    send->setText(language_vector.at(43));
    recieve->setText(language_vector.at(44));
    transactions->setText(language_vector.at(45));

    quit->setText(language_vector.at(47));

    change_passphrase->setText(language_vector.at(48));
    options->setText(language_vector.at(0));

    about_program->setText(language_vector.at(49));
    about_of_authors->setText(language_vector.at(65));
    view_window->setText(language_vector.at(50));

    ui->sendCoinsButton->setText(language_vector.at(43));

    ui->payToLabel->setText(language_vector.at(22));
    ui->amountLabel->setText(language_vector.at(36));
    ui->balanceLabel->setText(language_vector.at(18));
    ui->commissionLabel->setText(language_vector.at(38));

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

    ui->requestLabelLine->setPlaceholderText(language_vector.at(63));
    ui->messageLine->setPlaceholderText(language_vector.at(64));

    ui->linkLabel->setText(language_vector.at(82));
    ui->linkCB->setText(language_vector.at(83));


    if(table_translation.length() != 0)
    {
        table_translation.clear();

        table_translation.push_back(language_vector.at(84));
        table_translation.push_back(language_vector.at(85));
        table_translation.push_back(language_vector.at(86));
        table_translation.push_back(language_vector.at(87));

        table_translation.push_back(language_vector.at(88));
        table_translation.push_back(language_vector.at(89));
        table_translation.push_back(language_vector.at(90));
        table_translation.push_back(language_vector.at(91));
        table_translation.push_back(language_vector.at(92));

        request_view_model->clear();
        history_view_model->clear();
        requestsHistory();
    }
    else
    {
        table_translation.push_back(language_vector.at(84));
        table_translation.push_back(language_vector.at(85));
        table_translation.push_back(language_vector.at(86));
        table_translation.push_back(language_vector.at(87));

        table_translation.push_back(language_vector.at(88));
        table_translation.push_back(language_vector.at(89));
        table_translation.push_back(language_vector.at(90));
        table_translation.push_back(language_vector.at(91));
        table_translation.push_back(language_vector.at(92));
    }

    statusBar()->showMessage(language_vector.at(58));

    emit languageChanged(language_vector);
    emit languageChanged(language_index);
}

void MainWindow::on_sendCoinsButton_clicked()
{
    try {
        if(reciever_address.length() != 17)
        {
            throw ProgramException(INVALID_ADDRESS);
        }
        if(reciever_address == current_user.getAddress())
        {
            throw ProgramException(CURRENT_USER_ADDRESS);
        }
        JSON file_json("users.json");

        if(!users_information.isAddressExists(reciever_address))
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
                emit sendButton_clicked_val_1(TransactionData(current_user.getAddress(), reciever_address, amount, coins_type, fee, priority));
            }
            else if(val_2.getAuthority() == max_authority)
            {
                emit sendButton_clicked_val_2(TransactionData(current_user.getAddress(), reciever_address, amount, coins_type, fee, priority));
            }
            else if(val_3.getAuthority() == max_authority)
            {
                emit sendButton_clicked_val_3(TransactionData(current_user.getAddress(), reciever_address, amount, coins_type, fee, priority));
            }
            break;
        case 2:
            if(val_1.getAuthority() <= max_authority && val_1.getAuthority() >= min_authority)
            {
                emit sendButton_clicked_val_1(TransactionData(current_user.getAddress(), reciever_address, amount, coins_type, fee, priority));
            }
            else if(val_2.getAuthority() <= max_authority && val_2.getAuthority() >= min_authority)
            {
                emit sendButton_clicked_val_2(TransactionData(current_user.getAddress(), reciever_address, amount, coins_type, fee, priority));
            }
            else if(val_3.getAuthority() <= max_authority && val_3.getAuthority() >= min_authority)
            {
                emit sendButton_clicked_val_3(TransactionData(current_user.getAddress(), reciever_address, amount, coins_type, fee, priority));
            }
            break;
        case 3:
            if(val_1.getAuthority() == min_authority)
            {
                emit sendButton_clicked_val_1(TransactionData(current_user.getAddress(), reciever_address, amount, coins_type, fee, priority));
            }
            else if(val_2.getAuthority() == min_authority)
            {
                emit sendButton_clicked_val_2(TransactionData(current_user.getAddress(), reciever_address, amount, coins_type, fee, priority));
            }
            else if(val_3.getAuthority() == min_authority)
            {
                emit sendButton_clicked_val_3(TransactionData(current_user.getAddress(), reciever_address, amount, coins_type, fee, priority));
            }
            break;
        default:
            break;
        }
        throw ProgramException(SEND_SUCCESSFUL);
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
    ui->recomValueLE->setText("");
    emit on_priorityComboBox_currentIndexChanged(0);
}


void MainWindow::on_recomValueButton_clicked()
{
    recomActivated = true;
    ui->priorityComboBox->setEnabled(false);
    fee = round(amount * 0.05 * 100)/100;
    priority = 3;
    ui->customValueLE->setText("");
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

void MainWindow::on_clearSendButton_clicked()
{
    ui->payToAddress->clear();
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

int coinsTypeStringToInt(QString coins_type)
{
    if(coins_type == "BWC") return 0;
    if(coins_type == "BWC-N") return 1;
    if(coins_type == "BWC-Q") return 2;
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
    try {
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
    }  catch (ProgramException &error) {
        error.getError();
    }
}

void MainWindow::blocksNext()
{
    try {
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
    }  catch (ProgramException &error) {
        error.getError();
    }
}

void MainWindow::sendWalletPassToChangeForm()
{
    emit sendUserInformation(current_user, users_information);
}


void MainWindow::on_requestButton_clicked()
{
    emit requestButton_clicked();
}


void MainWindow::on_clearRequestButton_clicked()
{
    ui->amountToRequestSpinBox->clear();
    ui->messageLabel->clear();
    ui->requestLabelLine->clear();
}


void MainWindow::on_coinsBox_2_currentIndexChanged(int index)
{
    ui->coinsBox_2->setCurrentIndex(index);
    switch (index) {
    case 0:
        this->request_coins_type = BWC;
        break;
    case 1:
        this->request_coins_type = BWC_N;
        break;
    case 2:
        this->request_coins_type = BWC_Q;
        break;
    default:
        break;
    }
}


void MainWindow::on_amountToRequestSpinBox_valueChanged(double arg1)
{
    request_amount = QString::number(arg1);
}


void MainWindow::on_messageLine_textChanged(const QString &arg1)
{
    request_message = arg1;
}

void MainWindow::createLink()
{
    try {
        if(request_message.length() == 0)
        {
            throw ProgramException(REQUEST_MESSAGE_EMPTY);
        }
        if(request_amount.toDouble() <= 0)
        {
            throw ProgramException(REQUEST_AMOUNT_INVALID);
        }
        algoritms algo;
        QString link = QString::fromStdString(algo.GenerateLink(request_message.toStdString() + ";" +
                                                                request_amount.toStdString() + ";" +
                                                                coinsTypeToString(request_coins_type).toStdString() + ";" +
                                                                current_user.getAddress().toStdString()));
        ui->requestLabelLine->setText(link);
        try {
            CSV file("requestsList.csv");
            file.append_csv_request(link, request_message,
                                    request_amount, coinsTypeToString(request_coins_type),
                                    current_user.getAddress());
        }  catch (ProgramException &error) {
            error.getError();
        }

        request_view_model->clear();
        history_view_model->clear();
        requestsHistory();
    }  catch (ProgramException &error) {
        error.getError();
    }
}


void MainWindow::on_linkCB_stateChanged(int arg1)
{
    switch(arg1)
    {
    case 0:
        emit on_clearSendButton_clicked();

        ui->putLinkLE->setDisabled(true);

        ui->payToAddress->setDisabled(false);

        ui->amountSpinBox->setDisabled(false);

        ui->coinsBox->setDisabled(false);

        ui->putLinkLE->setText("");
        break;
    case 2:
        emit on_clearSendButton_clicked();

        ui->putLinkLE->setDisabled(false);

        ui->payToAddress->setDisabled(true);

        ui->amountSpinBox->setDisabled(true);

        ui->coinsBox->setDisabled(true);
        break;
    default:
        break;
    }
}


void MainWindow::on_putLinkLE_textChanged(const QString &arg1)
{
    try {
        algoritms algo;
        link = arg1;

        if(link.length() >= 36 && 0 == link.indexOf("https://") && link.length() - 3 == link.indexOf(".ua"))
        {
            link = QString::fromStdString(algo.DecryptionLink(link.toStdString()));
            QStringList encrypted_link = link.split(";");

            if(encrypted_link.at(3) == current_user.getAddress())
            {
                throw ProgramException(CURRENT_USER_ADDRESS);
            }
            ui->amountSpinBox->setValue(encrypted_link.at(1).toDouble());
            ui->coinsBox->setCurrentIndex(coinsTypeStringToInt(encrypted_link.at(2)));
            ui->payToAddress->setText(encrypted_link.at(3));
        }
    }  catch (ProgramException &error) {
        error.getError();
    }
}
