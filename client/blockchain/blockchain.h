#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <QString>
#include <QVector>
#include <QDebug>
#include <QDateTime>
#include "client/scripts/program_algorithms.h"
#include "client/tests/program_exception.h"
#include "client/scripts/json_func.h"

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
    TransactionData(QString sender, QString reciever,
                    double amount, CoinsType coins_type){
        QDateTime current_time = QDateTime::currentDateTime();
        this->sender = sender;
        this->reciever = reciever;
        this->amount = amount;
        this->coins_type = coins_type;
        this->timestamp = current_time.toString();
    }
};

class Block{
    int id;

    QString hash;
    QString prev_hash;

public:
    Block();
    Block(int index, TransactionData data, QString prev_hash);

    TransactionData block_data;
    QVector<Balance> users_balance;

    QString generateHash();

    int getIndex();

    QString getBlockHash();
    QString getPrevBlockHash();

    Balance getUserBalance(QString address);
    void setUserBalance(QString address, bool is_reciever = false);
    ~Block();
};

class Blockchain
{
    void createGenesisBlock();

    QVector<Block> chain;
public:
    Blockchain();

    QVector<Block> getChain();

    Block getLastBlock();

    bool isChainValid();
    void collisionCheck();

    void readChain();
    void writeChain();

    void addBlock(int index, TransactionData data, QString prev_hash);
    void show();

    ~Blockchain();
};

#endif // BLOCKCHAIN_H
