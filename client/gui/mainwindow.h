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
#include "auth_form.h"
#include "settings_form.h"
#include "about_program_form.h"
#include "client/tests/program_exception.h"
#include "client/scripts/json_func.h"
#include "client/scripts/new_wallet.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QStandardItemModel>

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

signals:

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    auth_Form ui_Auth;
    settings_Form ui_Settings;
    about_program_Form ui_AboutProgram;

    QString wallet_key;
    QString wallet_address;

    QStandardItemModel *request_view_model;

    bool login_succesfull;
    bool tray_enable = false;

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

    void setWindowLanguage();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayEnabled();
    void on_addUserToAddressBook_textChanged(const QString &arg1);
    void on_payToAddress_textChanged(const QString &arg1);

    void newTransaction();
};
#endif // MAINWINDOW_H
