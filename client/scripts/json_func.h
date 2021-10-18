#ifndef JSON_FUNC_H
#define JSON_FUNC_H

#include <QString>
#include <QVector>

enum getInfo
{
    ADDRESS,
    KEY
};

QVector<QString> getUsersInfo(getInfo what_u_need);
void registerNewUsers(QString wallet_address, QString wallet_key);


#endif // JSON_FUNC_H
