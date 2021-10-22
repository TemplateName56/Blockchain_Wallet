#ifndef SETTINGS_FORM_H
#define SETTINGS_FORM_H

#include <QWidget>

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

signals:
    void languageChanged();
    void trayCheckBoxToggled();

private:
    Ui::settings_Form *ui;
    friend class mainwindow;

public slots:
    void settingsShow();

private slots:
    void on_languagesBox_currentIndexChanged(int index);
    void on_trayCheckBox_toggled(bool checked);
    void setWindowLanguage();
};

#endif // SETTINGS_FORM_H
