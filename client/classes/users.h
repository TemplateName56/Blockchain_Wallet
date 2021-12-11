#ifndef USERS_H
#define USERS_H

#include <QString>
#include <QMap>
#include <QVector>

class User
{
    QString address;
    QString password;
    bool admin;
public:
    User();
    User(QString address, QString password, bool admin);

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

    User getUser(QString password);

    bool isPasswordExists(QString password);

    void changePassword(QString address);

    ~Users();
};

#endif // USERS_H
