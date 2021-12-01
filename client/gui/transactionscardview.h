#ifndef TRANSACTIONSCARDVIEW_H
#define TRANSACTIONSCARDVIEW_H

#include <QWidget>
#include <QPainter>
#include <QIcon>

#include "client/blockchain/blockchain.h"

namespace Ui {
class transactionsCardView;
}

class transactionsCardView : public QWidget
{
    Q_OBJECT

public:
    explicit transactionsCardView(QWidget *parent = nullptr);
    ~transactionsCardView();

    void setData(QString label, QString timeStamp, double amount, CoinsType coins_type, int transaction_type);

private:
    Ui::transactionsCardView *ui;
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // TRANSACTIONSCARDVIEW_H
