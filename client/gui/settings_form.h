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
    English,
    Ukranian,
    Russian
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
    void languageChanged();
    void trayCheckBoxToggled();

private:
    Ui::settings_Form *ui;
    friend class mainwindow;
    void readSettings();
    void writeSettings();

public slots:
    void settingsShow();

private slots:
    void on_languagesBox_currentIndexChanged(int index);
    void on_trayCheckBox_toggled(bool checked);
    void setWindowLanguage();
};

#endif // SETTINGS_FORM_H
