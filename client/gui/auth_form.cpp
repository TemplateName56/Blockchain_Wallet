#include "auth_form.h"
#include "ui_auth_form.h"

auth_Form::auth_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::auth_Form)
{
    ui->setupUi(this);
}

auth_Form::~auth_Form()
{
    delete ui;
}
