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

#include <iostream>
#include <QtDebug>

using namespace std;

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
    void append_users();
    void append_users_transactions();
    void append_users_2(QString address, QString walletKey);

private:
    //QJsonObject json;

    QString filename;
    QJsonDocument doc;

};


enum getInfo
{
    ADDRESS,
    KEY
};

void fileExists(const QString &file_path);

QVector<QString> getUsersInfo(getInfo what_u_need);

void registerNewUsers(QString wallet_address, QString wallet_key);


#endif // JSON_FUNC_H
