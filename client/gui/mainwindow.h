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
#include <QStyle>
#include "auth_form.h"
#include "settings_form.h"
#include "about_program_form.h"

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

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    auth_Form ui_Auth;
    settings_Form ui_Settings;
    about_program_Form ui_AboutProgram;

    QString wallet_key;
    QString wallet_address;
    bool login_succesfull;
    bool tray_enable;

    void createActions();
    void createMenus();
    void createTrayMenu();
    void uiChanges();

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
};
#endif // MAINWINDOW_H
