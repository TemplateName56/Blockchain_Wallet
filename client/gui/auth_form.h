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

private:
    Ui::auth_Form *ui;
};

#endif // AUTH_FORM_H
