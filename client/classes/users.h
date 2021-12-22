#ifndef USERS_H
#define USERS_H

#include <QString>
#include <QMap>
#include <QVector>

#include "client/classes/program_exception.h"
#include "client/scripts/program_algorithms.h"

enum languages
{
    ENGLISH,
    UKRANIAN,
    RUSSIAN
};

class User
{
    QString address;
    QString password;

    languages user_language;

    int coins_type_index;

    bool admin;
public:
    User();
    User(QString address, QString password, bool hash_password = true);
    User(QString address, QString password, languages user_language = UKRANIAN, bool admin = 0, int coins_type_index = 0);

    QString getAddress();

    QString getPassword();
    void setPassword(QString password, bool hash_pass = true);

    bool isPasswordCorrect(QString password);

    languages getUserLanguage();
    int getUserPreferCoinsType();

    int isAdmin();

    ~User();
};

class Users
{
    friend class JSON;
    QVector<User> users_information;
public:
    Users();

    QVector<User>& getUsersInformation();

    User getUser(int index);

    User getUser(QString password);

    void setUserPassword(QString address, QString password);


    void addUser(User new_user);

    bool isPasswordExists(QString password);
    bool isAddressExists(QString address);

    ~Users();
};

#endif // USERS_H
