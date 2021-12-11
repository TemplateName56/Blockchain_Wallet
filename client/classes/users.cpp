#include "users.h"

User::User()
{

}

User::User(QString address, QString password, bool admin)
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

User Users::getUser(QString password)
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
