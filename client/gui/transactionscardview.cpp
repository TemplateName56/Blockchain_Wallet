#include "transactionscardview.h"
#include "ui_transactionscardview.h"

transactionsCardView::transactionsCardView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::transactionsCardView)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

void transactionsCardView::setData(QString label, QString timeStamp, double amount, CoinsType coins_type, int transaction_type)
{
    switch (coins_type) {
    case BWC:
        ui->amount_Label->setText(QString::number(amount) + " BWC");
        break;
    case BWC_N:
        ui->amount_Label->setText(QString::number(amount) + " BWCN");
        break;
    case BWC_Q:
        ui->amount_Label->setText(QString::number(amount) + " BWCQ");
        break;
    default:
        break;
    }
    switch (transaction_type) {
    case 0:
        ui->cardIcon->setPixmap(QIcon("icons/sendIcon.png").pixmap(65,65));
        ui->amount_Label->setStyleSheet("color: red;");
        break;
    case 1:
        ui->cardIcon->setPixmap(QIcon("icons/recieveIcon.png").pixmap(64,64));
        ui->amount_Label->setStyleSheet("color: green;");
        break;
    default:
        break;
    }
    ui->timeStamp_Label->setText(timeStamp);
    ui->transactionLabel_Label->setText(label);
}

void transactionsCardView::paintEvent(QPaintEvent *event)
{
    QPainter paintIt(this);
    paintIt.drawRect(0,0, width() - 1, height() - 1);
}

transactionsCardView::~transactionsCardView()
{
    delete ui;
}
