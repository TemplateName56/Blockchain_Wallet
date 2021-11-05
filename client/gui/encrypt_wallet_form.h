#ifndef ENCRYPT_WALLET_FORM_H
#define ENCRYPT_WALLET_FORM_H

#include <QWidget>

namespace Ui {
class encrypt_wallet_Form;
}

class encrypt_wallet_Form : public QWidget
{
    Q_OBJECT

public:
    explicit encrypt_wallet_Form(QWidget *parent = nullptr);
    ~encrypt_wallet_Form();

public slots:
    void showEncrypt();

private:
    Ui::encrypt_wallet_Form *ui;
};

#endif // ENCRYPT_WALLET_FORM_H
