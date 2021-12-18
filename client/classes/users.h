#ifndef USERS_H
#define USERS_H

#include <QString>
#include <QMap>
#include <QVector>

#include "client/tests/program_exception.h"
#include "client/gui/settings_form.h"
#include "client/scripts/program_algorithms.h"

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

    const QString& getAddress() const;

    const QString& getPassword() const;
    void setPassword(QString password, bool hash_pass = true);

    bool isPasswordCorrect(QString password) const;

    const languages &getUserLanguage() const;
    const int &getUserPreferCoinsType() const;

    bool isAdmin() const;

    ~User();
};

class Users
{
    friend class JSON;
    QVector<User> users_information;
public:
    Users();

    const QVector<User>& getUsersInformation() const;

    const User& getUser(int index) const&;
    User getUser(int index) &&;

    const User& getUser(QString password) const&;
    User getUser( QString password) &&;

    void setUserPassword(QString address, QString password);


    void addUser(User new_user);

    bool isPasswordExists(QString password);
    bool isAddressExists(QString address);

    void read_file();

    ~Users();
};

#endif // USERS_H
