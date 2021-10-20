#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include "auth_form.h"

enum menu_changes
{
    HOME,
    SEND,
    RECIEVE,
    TRANSACTIONS
};

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

private:
    Ui::MainWindow *ui;
    auth_Form ui_Auth;

    QString wallet_key;
    QString wallet_address;
    bool login_succesfull;

    void createActions();
    void createMenus();

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

    QMenu *main_menu;
    QMenu *settings_menu;
    QMenu *help_menu;
    QToolBar *toolbar;

private slots:
    void authorizeUser();
    void registerUser();

    void homeTR();
    void sendTR();
    void recieveTR();
    void transactionsTR();
};
#endif // MAINWINDOW_H
