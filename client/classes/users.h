#ifndef USERS_H
#define USERS_H

#include <QString>
#include <QVector>

class User
{
    QString address;
    QString password;
    bool admin;
public:
    User();
    User(QString address, QString password);

    QString getAddress();
    QString getPassword();

    bool isAdmin();

    ~User();
};

class Users
{
    QVector<User> users_infomation;
public:
    Users();
    ~Users();
};

#endif // USERS_H
