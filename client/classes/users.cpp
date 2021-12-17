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

const QString& User::getAddress() const
{
    return this->address;
}

const QString& User::getPassword() const
{
    return this->password;
}

void User::setPassword(QString password)
{
    try {
        if(password.length() < 8)
        {
            throw ProgramException(NOT_VALID_PASSWORD);
        }
        this->password = password;
    }  catch (ProgramException &error) {
        error.getError();
    }
}

const languages& User::getUserLanguage() const
{
    return this->user_language;
}

bool User::isAdmin() const
{
    return this->admin;
}

User::~User()
{

}

Users::Users()
{
    //read_file();
    // file read func
}

const QVector<User>& Users::getUsersInformation() const
{
    return this->users_infomation;
}

const User& Users::getUser(int index) const&
{
    try {
        if(index >= 0 && index < users_infomation.length())
        {
            return this->users_infomation[index];
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
        if(index >= 0 && index < users_infomation.length())
        {
            return std::move(users_infomation[index]);
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
        if(users_infomation[index].getPassword() == password)
        {
            return users_infomation[index];
        }
    }
    //throw ProgramException(USER_NOT_EXIST);
}

User Users::getUser(QString password) &&
{
    algoritms use_algoritm;
    password = QString::fromStdString(use_algoritm.Hash(password.toStdString() + "SALT"));
    for(int index = 0; index < getUsersInformation().length(); index++)
    {
        if(users_infomation[index].getPassword() == password)
        {
            return std::move(users_infomation[index]);
        }
    }
    //throw ProgramException(USER_NOT_EXIST);
}

void Users::addUser(User new_user)
{
    this->users_infomation.push_back(new_user);
}

bool Users::isPasswordExists(QString password)
{
    algoritms use_algoritm;
    password = QString::fromStdString(use_algoritm.Hash(password.toStdString() + "SALT"));
    for(int index = 0; index < getUsersInformation().length(); index++)
    {
        if(users_infomation[index].getPassword() == password)
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
        if(users_infomation[index].getAddress() == address)
        {
            return true;
        }
    }
    return false;
}

/*
void Users:: read_file(){
    JSON file_user("users.json");
    for(int index = 0; index < file_user.get_array_size_users(); index++){
        users_infomation.push_back(User(file_user.get_address_user(index),
                                        file_user.get_wallet_key_user(index),
                                        tolanguages(file_user.get_language_user(index)),
                                        file_user.get_admin_user(index)));
    }
}
*/

Users::~Users()
{
    // file save func
    //getUser(1).getAddress();
}
