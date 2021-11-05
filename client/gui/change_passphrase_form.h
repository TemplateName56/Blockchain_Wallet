#ifndef CHANGE_PASSPHRASE_FORM_H
#define CHANGE_PASSPHRASE_FORM_H

#include <QWidget>

namespace Ui {
class change_passphrase_Form;
}

class change_passphrase_Form : public QWidget
{
    Q_OBJECT

public:
    explicit change_passphrase_Form(QWidget *parent = nullptr);
    ~change_passphrase_Form();

public slots:
    void changePassphraseShow();

private:
    Ui::change_passphrase_Form *ui;
};

#endif // CHANGE_PASSPHRASE_FORM_H
