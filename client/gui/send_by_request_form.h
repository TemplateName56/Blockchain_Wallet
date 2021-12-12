#ifndef SEND_BY_REQUEST_FORM_H
#define SEND_BY_REQUEST_FORM_H

#include <QWidget>

enum Mode{
    SEND,
    RECIEVE
};

namespace Ui {
class send_by_request_form;
}

class send_by_request_form : public QWidget
{
    Q_OBJECT

public:
    explicit send_by_request_form(QWidget *parent = nullptr);
    ~send_by_request_form();

    void setMode(Mode current_mode);

public slots:
    void requestFormShow();

private slots:
    void on_requestButton_clicked();

private:
    Ui::send_by_request_form *ui;
};

#endif // SEND_BY_REQUEST_FORM_H
