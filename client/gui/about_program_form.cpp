#include "about_program_form.h"
#include "ui_about_program_form.h"

about_program_Form::about_program_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::about_program_Form)
{
    ui->setupUi(this);
}

about_program_Form::~about_program_Form()
{
    delete ui;
}
