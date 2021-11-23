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

class Balance{
    QString address;

    double balance_amount_BWC = 0;
    double balance_amount_BWC_N = 0;
    double balance_amount_BWC_Q = 0;
public:
    Balance();
    Balance(QString address, double balance_amount,
            CoinsType coins_type);
    Balance(QString address, double balance_amount);

    QString getAddress();

    double getBalance(CoinsType coins_type);
    double setBalance(double amount, CoinsType coins_type);
};

class TransactionData{
    QString sender;
    QString reciever;

    double amount;
    CoinsType coins_type;

    double fee_amount;
    short priority;

    QString timestamp;
public:
    TransactionData();
    TransactionData(QString sender, QString reciever,
                    double amount, CoinsType coins_type,
                    double fee, short priority);

    QString getSender();
    QString getReciever();

    double getAmount();
    CoinsType getCoinsType();

    double getFee();
    short getPriority();

    QString getTimeStamp();
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
    void addBlock(Block new_block);
    void show();

    ~Blockchain();
};

#endif // BLOCKCHAIN_H
