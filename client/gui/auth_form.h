#ifndef AUTH_FORM_H
#define AUTH_FORM_H

#include <QWidget>

namespace Ui {
class auth_Form;
}

class auth_Form : public QWidget
{
    Q_OBJECT

public:
    explicit auth_Form(QWidget *parent = nullptr);
    ~auth_Form();
    QString getInputKey();

signals:
    void login_button_clicked();
    void register_button_clicked();

private slots:
    void on_walletKeyInput_textEdited(const QString &arg1);
    void on_loginButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::auth_Form *ui;
    QString user_key;
    friend class mainwindow;
};

#endif // AUTH_FORM_H
