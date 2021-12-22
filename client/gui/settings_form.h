#ifndef SETTINGS_FORM_H
#define SETTINGS_FORM_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "client/classes/users.h"
#include "client/classes/program_exception.h"

namespace Ui { class settings_Form; }

class settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit settings_Form(QWidget *parent = nullptr);
    ~settings_Form();

    int languageIndex;
    int preferCoinsIndex;
    User *current_user;

    bool minimizeInTray();

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void languageChanged(QVector<QString>, int);
    void trayCheckBoxToggled();
    void coinsTypeChanged(int);

private:
    Ui::settings_Form *ui;
    friend class mainwindow;

public slots:
    void settingsShow();
    void setWindowLanguage();

private slots:
    void on_languagesBox_currentIndexChanged(int index);
    void on_trayCheckBox_toggled(bool checked);
    void on_defaultCoinsTypeCB_currentIndexChanged(int index);

    void loadSettings(User &current_user);
};

#endif // SETTINGS_FORM_H
