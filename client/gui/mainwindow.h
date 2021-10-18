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
    bool login_succesfull;

private slots:
    void authorizeUser();
    void registerUser();
};
#endif // MAINWINDOW_H
