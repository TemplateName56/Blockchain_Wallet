#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <QString>
#include <QVector>
#include "client/scripts/program_algorithms.h"

enum CoinsType{
    BWC,
    BWC_N,
    BWC_Q
};

struct Balance{
    QString address;

    double balance_amount_BWC = 0;
    double balance_amount_BWC_N = 0;
    double balance_amount_BWC_Q = 0;

    Balance(){}
    Balance(QString address, double balance_amount,
            CoinsType coins_type){
        this->address = address;
        switch (coins_type) {
        case BWC:
            this->balance_amount_BWC = balance_amount;
            break;
        case BWC_N:
            this->balance_amount_BWC_N = balance_amount;
            break;
        case BWC_Q:
            this->balance_amount_BWC_Q = balance_amount;
            break;
        default:
            break;
        }
    }
};

struct TransactionData{
    QString sender;
    QString reciever;

    double amount;
    CoinsType coins_type;

    QString timestamp;

    TransactionData(){}
    TransactionData(QString sender, QString reciever, double amount,
                    CoinsType coins_type, QString timestamp){
        this->sender = sender;
        this->reciever = reciever;
        this->amount = amount;
        this->coins_type = coins_type;
        this->timestamp = timestamp;
    }
};

class Block{
private:
    int id;

    QString hash;
    QString prev_hash;

    TransactionData block_data;

    QVector<Balance> users_balance;
public:
    Block(int index, TransactionData data, QString prev_hash);

    QString generateHash();

    int getIndex();

    QString getBlockHash();
    QString getPrevBlockHash();

    Balance getUserBalance(QString address);
    void setUserBalance(QString address);
};

class Blockchain
{
private:
    //Block GenesisBlock;

    QVector<Block> chain;
public:
    Blockchain();

    QVector<Block> getChain();

    Block getLastBlock();

    void readChain();

    bool isChainValid();

    void addBlock();


    ~Blockchain();
};

#endif // BLOCKCHAIN_H
