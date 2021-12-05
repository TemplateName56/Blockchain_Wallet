#include "about_program_form.h"
#include "ui_about_program_form.h"

about_program_Form::about_program_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::about_program_Form)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("icons/programIcon.png"));
}

about_program_Form::~about_program_Form()
{
    delete ui;
}

void about_program_Form::aboutShow()
{
    this->show();
}
