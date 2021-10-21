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
#include "settings_form.h"
#include "about_program_form.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum languages
{
    English,
    Ukranian,
    Russian
};

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
    settings_Form ui_Settings;
    about_program_Form ui_AboutProgram;

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

    void setWindowLanguage();
};
#endif // MAINWINDOW_H
