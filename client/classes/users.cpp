#include "users.h"

User::User()
{

}

User::User(QString address, QString password)
{
    this->address = address;
    this->password = password;
}

QString User::getAddress()
{
    return this->address;
}

QString User::getPassword()
{
    return this->password;
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

Users::~Users()
{

}
