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

enum languages
{
    ENGLISH,
    UKRANIAN,
    RUSSIAN
};

namespace Ui {
class settings_Form;
}

class settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit settings_Form(QWidget *parent = nullptr);
    ~settings_Form();
    int languageIndex;
    bool minimizeInTray();

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void languageChanged(QVector<QString>);
    void trayCheckBoxToggled();
    void coinsTypeChanged(int);

private:
    Ui::settings_Form *ui;
    friend class mainwindow;
    void readSettings();
    void writeSettings();

public slots:
    void settingsShow();
    void setWindowLanguage();

private slots:
    void on_languagesBox_currentIndexChanged(int index);
    void on_trayCheckBox_toggled(bool checked);
    void on_defaultCoinsTypeCB_currentIndexChanged(int index);
};

#endif // SETTINGS_FORM_H
