#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QDialog>
#include <windows.h>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QStandardItemModel>
#include <QDate>
#include <QQueue>
#include <QMetaType>

#include "auth_form.h"
#include "settings_form.h"
#include "about_program_form.h"
#include "encrypt_wallet_form.h"
#include "change_passphrase_form.h"
#include "transactionscardview.h"
#include "client/tests/program_exception.h"
#include "client/scripts/json_func.h"
#include "client/scripts/new_wallet.h"
#include "client/scripts/csv_func.h"
#include "client/blockchain/blockchain.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void display();
    void requestsHistory();

    bool isAmountCorrect(double amount, CoinsType coins_type);

signals:
    void sendButton_clicked(TransactionData new_data);
    void newTrasaction_clicked();
    void sendTransaction(TransactionData new_transaction);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    Validator val_1;
    Validator val_2;
    Validator val_3;

    settings_Form ui_Settings;
    auth_Form ui_Auth;
    about_program_Form ui_AboutProgram;
    encrypt_wallet_Form ui_EncryptWallet;
    change_passphrase_Form ui_ChangePass;

    QString wallet_key;
    QString wallet_address;

    bool tray_enable = false;
    bool recomActivated = true;

    QString reciever_address;
    QString transaction_label;
    double amount;
    CoinsType coins_type = BWC;
    double fee;
    short priority = 3;

    QStandardItemModel *request_view_model;

    QAction *home;
    QAction *send;
    QAction *recieve;
    QAction *transactions;

    QAction *all_blocks;

    QAction *help;
    QAction *quit;

    QAction *encrypt_wallet;
    QAction *change_passphrase;
    QAction *options;

    QAction *about_program;
    QAction *view_window;

    QMenu *main_menu;
    QMenu *settings_menu;
    QMenu *help_menu;
    QMenu *tray_menu;

    QToolBar *toolbar;
    QSystemTrayIcon *tray_icon;

    int counter = 0;
    QList<transactionsCardView> card_list;

    void createActions();
    void createMenus();
    void createTrayMenu();
    void uiChanges();

private slots:
    void authorizeUser();
    void registerUser();

    void homeTR();
    void sendTR();
    void recieveTR();
    void transactionsTR();
    void blocksTR();

    void setWindowLanguage();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayEnabled();

    void addTransactionCard(QString label, QString timeStamp, double amount, CoinsType coins_type, int transaction_type);

    void newTransaction(QString wallet_address, TransactionData data);

    void on_payToAddress_textChanged(const QString &arg1);
    void on_sendTransactionLabel_textChanged(const QString &arg1);

    void on_payToAddress_textEdited(const QString &arg1);

    void on_sendCoinsButton_clicked();
    void on_customValueButton_clicked();
    void on_recomValueButton_clicked();

    void on_amountSpinBox_valueChanged(double arg1);

    void on_feeCheckBox_stateChanged(int arg1);

    void on_priorityComboBox_currentIndexChanged(int index);
    void on_coinsBox_currentIndexChanged(int index);
};
#endif // MAINWINDOW_H
