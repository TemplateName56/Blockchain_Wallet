#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <QString>
#include <QVector>

struct Balances{
    QString address;
    double balance_amount_BWC;
    double balance_amount_BWC_NIKITA;
    double balance_amout_BWC_Q;
};

struct Block{
    QString hash;
    QString *pre_hash;

    long int id;

    QString sender;
    QString reciever;
    double amount;
    QString coins_type;
    QString date;

    QVector<Balances> users_balance;
};

class Blockchain
{
    Block *blocks;
    int size;
public:
    Blockchain();
};

#endif // BLOCKCHAIN_H
