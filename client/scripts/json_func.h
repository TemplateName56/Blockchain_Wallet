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

#include <iostream>
#include <QtDebug>

class JSON {
public:
    JSON(QString fileName);

    QJsonObject getJson();
    QJsonObject loadJson(const QString& filepath);
    QString get_hash(int number_block);
    QString get_hash_previous(int number_block);
    int get_number(int number_block);
    QString get_currency(int number_block);
    int get_time_of_creation(int number_block);
    QString get_address_recipient(int number_block);
    QString get_address_sender(int number_block);
    double get_money(int number_block);
    int get_array_size();
    int get_array_size_users();
    QString get_address_users(int num);
    QString get_walletKey_users(int num);

    void read_users_transactions();
    void saveJson_append(int index);
    void saveJson_append_2(int index, QString hash_prev, QString hash, QString btc, int time, QString adress_s, QString adress_r, double money);

    void append_users_transactions();
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
