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
#include "client/classes/program_exception.h"
#include "client/scripts/program_algorithms.h"
#include "client/classes/blockchain.h"
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

    int get_id(int number_block);
    QString get_sender(int number_block);
    QString get_reciever(int number_block);
    QString get_timestamp(int number_block);
    double get_amount(int number_block);
    double get_fee(int number_block);
    int get_CoinsType(int number_block);
    int get_array_size_blockchain();
    void set_prefer_coins_type_user(QString address, int prefer_coins_type);
    void set_language_user(QString address, int language);
    int get_array_size_users();

    QVector<QString> get_users_info(getInfo what_u_need);
    void read_all_chain(Blockchain &a);
    void write_all_chain(Block block);
    void read_users_file(Users &a);
    void write_users_file(Users &a);
private:
    QString filename;
    QJsonDocument doc;

};

void fileExists(const QString &file_path);

#endif // JSON_FUNC_H
