#ifndef JSON_FUNC_H
#define JSON_FUNC_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "client/tests/program_exception.h"
#include "client/scripts/program_algorithms.h"
#include "client/blockchain/blockchain.h"

#include <iostream>
#include <QtDebug>

class JSON {
public:
    JSON(QString fileName);

    void registerNewUser(QString address, QString walletKey);

    QString new_get_hash(int number_block);
    QString new_get_prev_hash(int number_block);
    int new_get_id(int number_block);

    QString new_get_sender(int number_block, int num_data);
    QString new_get_reciever(int number_block, int num_data);
    QString new_get_timestamp(int number_block, int num_data);
    double new_get_amount(int number_block, int num_data);
    double new_get_fee(int number_block, int num_data);
    int new_get_CoinsType(int number_block, int num_data);
    int new_get_priority(int number_block, int num_data);

    QString new_get_address(int number_block, int num_balance);
    double new_get_BWC_balance(int number_block, int num_balance);
    double new_get_BWC_N_balance(int number_block, int num_balance);
    double new_get_BWC_Q_balance(int number_block, int num_balance);

    void new_print();
    int new_get_array_size_blockchain();
    int new_get_array_size_balances(int number_block);
    int new_get_array_size_block_data(int number_block);

    void new_append_balances(int num_user);
    void new_write_block_data(int num_user);
    void new_append_hash2_id();
    void write_chain_json();

    void new_append_balances(int num_user, QString address, double balance_bwc,
                             double balance_bwc_n, double balance_bwc_q);

    void new_write_block_data(int num_user, QString sender, QString reciever,
                              int amount, int coins_type, double fee, int priority,
                              QString time_stamp);

    void new_append_hash2_id(QString hash, int id, QString prev_hash);


    enum getInfo
    {
        ADDRESS,
        KEY,
        ADMIN
    };

    QVector<QString> get_users_info(getInfo what_u_need);
    void read_all_chain(Blockchain &chain);
    void write_all_chain(QVector<Block> chain);
    void write_all_chain(Block block);
private:
    //QJsonObject json;

    QString filename;
    QJsonDocument doc;

};


enum getInfo
{
    ADDRESS,
    KEY,
    ADMIN
};

void fileExists(const QString &file_path);

QVector<QString> getUsersInfo(getInfo what_u_need);

//void registerNewUsers(QString wallet_address, QString wallet_key);


#endif // JSON_FUNC_H
