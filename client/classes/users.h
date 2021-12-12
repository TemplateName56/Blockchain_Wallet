#ifndef USERS_H
#define USERS_H

#include <QString>
#include <QMap>
#include <QVector>
#include "client/gui/settings_form.h"

class User
{
    QString address;
    QString password;

    languages user_language;

    bool admin;
public:
    User();
    User(QString address, QString password, bool admin);
    User(QString address, QString password, languages user_language, bool admin);

    QString getAddress();
    QString getPassword();

    languages getUserLanguage();

    bool isAdmin();

    ~User();
};

class Users
{
    QMap<QString, User> users_infomation;
public:
    Users();

    User getUser(QString address);

    bool isPasswordExists(QString password);

    void changePassword(QString address);

    ~Users();
};

#endif // USERS_H
