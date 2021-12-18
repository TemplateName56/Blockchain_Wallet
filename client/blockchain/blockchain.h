#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <QString>
#include <QVector>
#include <QDebug>
#include <QDateTime>
#include <QObject>

#include "client/scripts/program_algorithms.h"
#include "client/tests/program_exception.h"

enum CoinsType
{
    BWC,
    BWC_N,
    BWC_Q,
    CoinsTypeERROR
};

class Balance
{
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
    void setBalance(double amount, CoinsType coins_type);
};

class TransactionData
{
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
    TransactionData(QString sender, QString reciever,
                    double amount, CoinsType coins_type,
                    double fee, short priority, QString timestamp);

    QString getSender();
    QString getReciever();

    double getAmount();
    CoinsType getCoinsType();

    double getFee();
    short getPriority() const;

    QString getTimeStamp();
};

class Block
{
     friend class JSON;
    int id;

    QString hash;
    QString prev_hash;

    TransactionData block_data;
public:
    Block();
    Block(int index, TransactionData data, QString prev_hash);
    Block(int index, TransactionData data, QString prev_hash, QString hash);


    QVector<Balance> users_balance;

    QString generateHash();

    int getIndex();

    QString getBlockHash();
    QString getPrevBlockHash();

    TransactionData getBlockData();

    Balance getUserBalance(QString address);
    void setUserBalance(QString address, bool is_reciever = false);
    ~Block();
};

class Blockchain
{
    friend class JSON;
    void createGenesisBlock();

    QVector<Block> chain;
public:
    Blockchain();

    QVector<Block> getChain();

    Block getBlock(int index);
    Block getLastBlock();
    int getChainLenght();

    bool isChainValid();
    void collisionCheck();

    void readChain();
    void writeChain();

    void addBlock(int index, TransactionData data, QString prev_hash);
    void addBlock(int index, TransactionData data, QString prev_hash, QString hash, bool genesis);
    void addBlock(Block new_block);

    void show();

    ~Blockchain();
};

class Validator : public QObject
{
    Q_OBJECT
private:
    Blockchain chain;
    int authority = 1;
    bool blocked = false;

public:
    explicit Validator(QObject *parent = nullptr);

    Blockchain getBlockChain();
    void setBlockChain(Blockchain temp);
    int getAuthority();

    void setAuthority(int authority);
signals:
    void newBlock();
    void sendTransaction(QString, TransactionData);

public slots:
    void addTransaction(TransactionData new_transaction);
};

#endif // BLOCKCHAIN_H
