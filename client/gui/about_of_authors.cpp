#include "about_of_authors.h"
#include "ui_about_of_authors.h"

about_of_authors::about_of_authors(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::about_of_authors)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("icons/programIcon.png"));
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

about_of_authors::~about_of_authors()
{
    delete ui;
}

void about_of_authors::aboutAuth()
{
    this->show();
}
