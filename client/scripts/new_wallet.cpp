#include "new_wallet.h"
#include "json_func.h"
#include <QDebug>

#include "includes/effolkronium/random.hpp"
#include "program_algorithms.h"

using Random = effolkronium::random_static;

QString random_symbols = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

QString randomWalletAdress()
{
    JSON file_json("users.json");
    QVector<QString> valid_addresses = file_json.get_users_info(JSON::ADDRESS);
    QString random_address;
    QString new_address = "BW";

    bool address_in_generating = true;

    while(address_in_generating)
    {
        random_address = "";

        for(int index = 0; index < 15; index++)
        {
            random_address += random_symbols[(Random::get(0, 61))];
        }
        int index = valid_addresses.indexOf(random_address);
        if(index != -1)
        {
            qDebug() << "We have one";
        }
        else
        {
            address_in_generating = false;
            new_address += random_address;
        }
    }
    return new_address;
}

QString randomWalletKey()
{
    JSON file_json("users.json");
    QVector<QString> valid_keys = file_json.get_users_info(JSON::KEY);

    QString random_key;
    QString new_key;

    algoritms algo;

    bool password_in_generating = true;

    while(password_in_generating)
    {
        random_key = "";

        int count = 0;
        for(int index = 0; index < 19; index++)
        {
            if(count == 4)
            {
                random_key += "-";
                count = 0;
            }
            else
            {
                random_key += random_symbols[(Random::get(0, 61))];
                count++;
            }
        }
        int index = valid_keys.indexOf(QString::fromStdString(algo.Hash(random_key.toStdString())));
        if(index != -1)
        {
            qDebug() << "We have one";
        }
        else
        {
            password_in_generating = false;
            new_key = random_key;
        }
    }
    return new_key;
}
