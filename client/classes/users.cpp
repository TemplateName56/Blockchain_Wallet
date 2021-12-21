#include "users.h"

languages tolanguages(int language)
{
    switch (language) {
    case 0:
        return ENGLISH;
        break;
    case 1:
        return UKRANIAN;
        break;
    case 2:
        return RUSSIAN;
    default:
        break;
    }
}


User::User()
{

}

User::User(QString address, QString password, bool hash_password)
{
    this->address = address;

    if(hash_password)
    {
        algoritms use_algoritm;
        password = QString::fromStdString(use_algoritm.Hash(password.toStdString() + "SALT"));
    }

    this->password = password;

    this->user_language = UKRANIAN;
    this->coins_type_index = 0;
    this->admin = false;
}

User::User(QString address, QString password, languages user_language, bool admin, int coins_type_index)
{
    this->address = address;
    this->password = password;
    this->user_language = user_language;
    this->coins_type_index = coins_type_index;
    this->admin = admin;
}

const QString& User::getAddress() const
{
    return this->address;
}

const QString& User::getPassword() const
{
    return this->password;
}

void User::setPassword(QString password, bool hash_pass)
{
    try {
        if(password.length() < 8)
        {
            throw ProgramException(NOT_VALID_PASSWORD);
        }
        if(hash_pass)
        {
            algoritms use_algoritm;
            password = QString::fromStdString(use_algoritm.Hash(password.toStdString() + "SALT"));
        }
        this->password = password;
    }  catch (ProgramException &error) {
        error.getError();
    }
}

bool User::isPasswordCorrect(QString password) const
{
    algoritms use_algoritm;
    password = QString::fromStdString(use_algoritm.Hash(password.toStdString() + "SALT"));
    if(this->password == password)
    {
        return true;
    }
    return false;
}

const languages& User::getUserLanguage() const
{
    return this->user_language;
}

const int& User::getUserPreferCoinsType() const
{
    return this->coins_type_index;
}

int User::isAdmin() const
{
    return this->admin;
}

User::~User()
{

}

Users::Users()
{

}

const QVector<User>& Users::getUsersInformation() const
{
    return this->users_information;
}

const User& Users::getUser(int index) const&
{
    try {
        if(index >= 0 && index < users_information.length())
        {
            return this->users_information[index];
        }
        else
        {
            throw ProgramException(OUT_OF_RANGE, "Users Vector");
        }
    }  catch (ProgramException &error) {
        error.getError();
    }
}

User Users::getUser(int index) &&
{
    try {
        if(index >= 0 && index < users_information.length())
        {
            return std::move(users_information[index]);
        }
        else
        {
            throw ProgramException(OUT_OF_RANGE, "Users Vector");
        }
    }  catch (ProgramException &error) {
        error.getError();
    }
}

const User& Users::getUser(QString password) const&
{
    algoritms use_algoritm;
    password = QString::fromStdString(use_algoritm.Hash(password.toStdString() + "SALT"));
    for(int index = 0; index < getUsersInformation().length(); index++)
    {
        if(users_information[index].getPassword() == password)
        {
            return users_information[index];
        }
    }
    throw ProgramException(USER_NOT_EXIST);
}

User Users::getUser(QString password) &&
{
    algoritms use_algoritm;
    password = QString::fromStdString(use_algoritm.Hash(password.toStdString() + "SALT"));
    for(int index = 0; index < getUsersInformation().length(); index++)
    {
        if(users_information[index].getPassword() == password)
        {
            return std::move(users_information[index]);
        }
    }
    throw ProgramException(USER_NOT_EXIST);
}

void Users::setUserPassword(QString address, QString password)
{
    for(int index = 0; index < getUsersInformation().length(); index++)
    {
        if(users_information[index].getAddress() == address)
        {
            users_information[index].setPassword(password, false);
        }
    }
}

void Users::addUser(User new_user)
{
    this->users_information.push_back(new_user);
}

bool Users::isPasswordExists(QString password)
{
    algoritms use_algoritm;
    password = QString::fromStdString(use_algoritm.Hash(password.toStdString() + "SALT"));
    for(int index = 0; index < getUsersInformation().length(); index++)
    {
        if(users_information[index].getPassword() == password)
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
        if(users_information[index].getAddress() == address)
        {
            return true;
        }
    }
    return false;
}

Users::~Users()
{

}
