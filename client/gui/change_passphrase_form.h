#ifndef CHANGE_PASSPHRASE_FORM_H
#define CHANGE_PASSPHRASE_FORM_H

#include <QWidget>

#include "client/classes/program_exception.h"
#include "client/classes/users.h"

namespace Ui {
class change_passphrase_Form;
}

class change_passphrase_Form : public QWidget
{
    Q_OBJECT

public:
    explicit change_passphrase_Form(QWidget *parent = nullptr);
    ~change_passphrase_Form();

    Users *users_information;

    User *current_user;
    QString current_wallet_pass;
    QString old_password;
    QString new_password;

signals:
    void changePassBTN_clicked();
    void clearPassEnterBTN_clicked();

public slots:
    void changePassphraseShow();
    void setWindowLanguage(int index);

private slots:
    void on_currentPassLE_textChanged(const QString &arg1);
    void on_newPassLE_textChanged(const QString &arg1);

    void on_changePassBTN_clicked();
    void on_clearPassEnterBTN_clicked();

    void currentUserPassChange(User &current_user, Users &users_information);

private:
    Ui::change_passphrase_Form *ui;
};

#endif // CHANGE_PASSPHRASE_FORM_H
