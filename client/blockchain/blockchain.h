#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <QString>
#include <QVector>

struct Balance{
    QString address;

    double balance_amount_BWC;
    double balance_amount_BWC_N;
    double balance_amout_BWC_Q;
};

struct TransactionData{
    QString sender;
    QString reciever;

    double amount;
    QString coins_type;

    QString date;

    TransactionData(){}
    TransactionData(QString sender, QString reciever, double amount,
                    QString coins_type, QString date){
        this->sender = sender;
        this->reciever = reciever;
        this->amount = amount;
        this->coins_type = coins_type;
        this->date = date;
    }
};

class Block{
private:
    int index;

    QString hash;
    QString *prev_hash;

    QVector<Balance> users_balance;
public:
    Block(int index, TransactionData data);

    TransactionData block_data;
};

class Blockchain
{
private:

public:
    Blockchain();
};

#endif // BLOCKCHAIN_H
