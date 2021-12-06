#include "change_passphrase_form.h"
#include "ui_change_passphrase_form.h"

change_passphrase_Form::change_passphrase_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::change_passphrase_Form)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("icons/programIcon.png"));
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

void change_passphrase_Form::changePassphraseShow()
{
    this->show();
}

change_passphrase_Form::~change_passphrase_Form()
{
    delete ui;
}
