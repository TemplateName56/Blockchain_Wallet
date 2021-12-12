#include "users.h"

User::User()
{

}

User::User(QString address, QString password, bool admin)
{
    this->address = address;
    this->password = password;
    this->admin = admin;
}

User::User(QString address, QString password, languages user_language, bool admin)
{
    this->address = address;
    this->password = password;
    this->user_language = user_language;
    this->admin = admin;
}

QString User::getAddress()
{
    return this->address;
}

QString User::getPassword()
{
    return this->password;
}

languages User::getUserLanguage()
{
    return this->user_language;
}

bool User::isAdmin()
{
    return this->admin;
}

User::~User()
{

}

Users::Users()
{

}

User Users::getUser(QString address)
{

}

bool Users::isPasswordExists(QString password)
{

}

void Users::changePassword(QString address)
{

}

Users::~Users()
{

}
