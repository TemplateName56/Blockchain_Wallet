#ifndef USERS_H
#define USERS_H

#include <QString>
#include <QMap>
#include <QVector>

#include "client/tests/program_exception.h"
#include "client/gui/settings_form.h"
#include "client/scripts/json_func.h"

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

    const QString& getAddress() const&;

    const QString& getPassword() const&;
    void setPassword(QString password);

    const languages &getUserLanguage() const&;

    bool isAdmin();

    ~User();
};

class Users
{
     //friend class JSON;
    QVector<User> users_infomation;
public:
    Users();

    const QVector<User>& getUsersInformation() const&;

    const User& getUser(int index) const&;
    const User& getUser(QString address) const&;


    void addUser(User new_user);

    bool isPasswordExists(QString password);
    bool isAddressExists(QString address);

    void read_file();

    ~Users();
};

#endif // USERS_H
