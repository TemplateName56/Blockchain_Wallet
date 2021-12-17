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
    //throw ProgramException(USER_NOT_EXIST);
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
    //throw ProgramException(USER_NOT_EXIST);
}

void Users::setUserPassword(QString address, QString password)
{
    for(int index = 0; index < getUsersInformation().length(); index++)
    {
        if(users_information[index].getAddress() == address)
        {
            qDebug() << users_information[index].getAddress();
            qDebug() << users_information[index].getPassword();
            users_information[index].setPassword(password, false);
            qDebug() << users_information[index].getAddress();
            qDebug() << users_information[index].getPassword();
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

/*
void Users:: read_file(){
    JSON file_user("users.json");
    for(int index = 0; index < file_user.get_array_size_users(); index++){
        users_information.push_back(User(file_user.get_address_user(index),
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
