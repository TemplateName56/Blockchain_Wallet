#include "send_by_request_form.h"
#include "ui_send_by_request_form.h"

send_by_request_form::send_by_request_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::send_by_request_form)
{
    ui->setupUi(this);
}

send_by_request_form::~send_by_request_form()
{
    delete ui;
}

void send_by_request_form::setMode(Mode current_mode)
{
    switch(current_mode)
    {
    case SEND:
        ui->requestLabel->setText("Put your Reference");
        ui->requestReference->setReadOnly(false);
        break;
    case RECIEVE:
        ui->requestLabel->setText("Your Reference");
        ui->requestReference->setReadOnly(true);
        break;
    default:
        break;
    }
}

void send_by_request_form::requestFormShow()
{
    this->show();
}


void send_by_request_form::on_requestButton_clicked()
{

}

