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

#include "auth_form.h"
#include "settings_form.h"
#include "about_program_form.h"
#include "encrypt_wallet_form.h"
#include "change_passphrase_form.h"
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

    bool isAmountCorrect(double amount);

signals:
    void sendButton_clicked();
    void newTrasaction_clicked();
protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    Blockchain chain;

    settings_Form ui_Settings;
    auth_Form ui_Auth;
    about_program_Form ui_AboutProgram;
    encrypt_wallet_Form ui_EncryptWallet;
    change_passphrase_Form ui_ChangePass;

    QString wallet_key;
    QString wallet_address;

    QStandardItemModel *request_view_model;

    bool login_succesfull;
    bool tray_enable = false;

    QString reciever_address;
    double amount;
    double fee;
    QString coins_type;

    bool recomActivated = true;

    int last_transaction_notify = 5;

    int y_tr1_pos = 10;
    int y_tr2_pos = 100;
    int y_tr3_pos = 190;
    int y_tr4_pos = 280;
    int y_tr5_pos = 370;

    void createActions();
    void createMenus();
    void createTrayMenu();
    void uiChanges();
    void setupTransactionsOverview();

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

    QParallelAnimationGroup *transactionsGroup = new QParallelAnimationGroup;

    QPropertyAnimation *transaction_1;
    QPropertyAnimation *transaction_2;
    QPropertyAnimation *transaction_3;
    QPropertyAnimation *transaction_4;
    QPropertyAnimation *transaction_5;

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
    void on_addUserToAddressBook_textChanged(const QString &arg1);
    void on_payToAddress_textChanged(const QString &arg1);

    void newTransaction();
    void on_sendCoinsButton_clicked();
    void on_payToAddress_textEdited(const QString &arg1);
    void on_amountSpinBox_valueChanged(double arg1);
    void on_feeCheckBox_stateChanged(int arg1);
    void on_priorityComboBox_currentIndexChanged(int index);
    void on_custinValueButton_clicked();
    void on_recomValueButton_clicked();
};
#endif // MAINWINDOW_H
