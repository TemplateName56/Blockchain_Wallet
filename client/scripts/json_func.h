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
#include "client/classes/users.h"

#include <iostream>
#include <QtDebug>



class JSON{

public:

    enum getInfo
    {
        ADDRESS,
        KEY,
        ADMIN
    };


    JSON(QString fileName);

    QString get_hash(int number_block);
    QString get_prev_hash(int number_block);
    int get_id(int number_block);

    QString get_sender(int number_block);
    QString get_reciever(int number_block);
    QString get_timestamp(int number_block);
    double get_amount(int number_block);
    double get_fee(int number_block);
    int get_CoinsType(int number_block);
    int get_priority(int number_block);
    int get_array_size_blockchain();
    int get_array_size_balances(int number_block);

    QVector<QString> get_users_info(getInfo what_u_need);
    int get_array_size_users();

    void read_all_chain(Blockchain &a);
    void read_all_chain(Validator &a);
    void write_all_chain(Block block);

    int get_language_user(QString address);
    void set_language_user(QString address, int language);

    void read_users_file(Users &a);
    void write_users_file(Users &a);
private:
    //QJsonObject json;

    QString filename;
    QJsonDocument doc;

};

void fileExists(const QString &file_path);

#endif // JSON_FUNC_H
