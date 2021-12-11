#ifndef CHANGE_PASSPHRASE_FORM_H
#define CHANGE_PASSPHRASE_FORM_H

#include <QWidget>
#include "client/tests/program_exception.h"

namespace Ui {
class change_passphrase_Form;
}

class change_passphrase_Form : public QWidget
{
    Q_OBJECT

public:
    explicit change_passphrase_Form(QWidget *parent = nullptr);
    ~change_passphrase_Form();

    QString current_wallet_pass;
    QString old_password;
    QString new_password;

signals:
    void changePassBTN_clicked();
    void clearPassEnterBTN_clicked();

public slots:
    void changePassphraseShow();

private slots:
    void on_currentPassLE_textChanged(const QString &arg1);
    void on_newPassLE_textChanged(const QString &arg1);
    void on_changePassBTN_clicked();
    void on_clearPassEnterBTN_clicked();
    void recieveOldWalletPass(QString current_wallet_pass);

private:
    Ui::change_passphrase_Form *ui;
};

#endif // CHANGE_PASSPHRASE_FORM_H
