#include "settings_form.h"
#include "ui_settings_form.h"

settings_Form::settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings_Form)
{
    ui->setupUi(this);
}

settings_Form::~settings_Form()
{
    delete ui;
}
