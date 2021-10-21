#ifndef SETTINGS_FORM_H
#define SETTINGS_FORM_H

#include <QWidget>

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

signals:
    void languageChanged();

private:
    Ui::settings_Form *ui;
    friend class mainwindow;
public slots:
    void settingsShow();
private slots:
    void on_languagesBox_currentIndexChanged(int index);
};

#endif // SETTINGS_FORM_H
