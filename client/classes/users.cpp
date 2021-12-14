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

const QString& User::getAddress() const&
{
    return this->address;
}

const QString& User::getPassword() const&
{
    return this->password;
}

void User::setPassword(QString password)
{
    if(password.length() < 8)
    {
        throw ProgramException(NOT_VALID_PASSWORD);
    }
    this->password = password;
}

const languages& User::getUserLanguage() const&
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
    // file read func
}

const QVector<User>& Users::getUsersInformation() const&
{
    return this->users_infomation;
}

const User& Users::getUser(int index) const&
{
    if(index >= 0 && index < users_infomation.length())
    {
        return this->users_infomation[index];
    }
    else
    {
        throw ProgramException(OUT_OF_RANGE, "Users Vector");
    }
}

const User& Users::getUser(QString address) const&
{
    for(int index = 0; index < getUsersInformation().length(); index++)
    {
        if(getUser(index).getAddress() == address)
        {
            return getUser(index);
        }
    }
    throw ProgramException(USER_NOT_EXIST);
}

void Users::addUser(User new_user)
{
    this->users_infomation.push_back(new_user);
}

bool Users::isPasswordExists(QString password)
{
    for(int index = 0; index < getUsersInformation().length(); index++)
    {
        if(getUser(index).getPassword() == password)
        {
            return true;
        }
    }
    return false;
}

bool Users::isAddressExists(QString address)
{
    for(int index = 0; index < getUsersInformation().length(); index++)
    {
        if(getUser(index).getAddress() == address)
        {
            return true;
        }
    }
    return false;
}

Users::~Users()
{
    // file save func
}
