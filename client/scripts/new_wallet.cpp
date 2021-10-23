#include "new_wallet.h"
#include "json_func.h"
#include <QDebug>
#include "includes/effolkronium/random.hpp"

using Random = effolkronium::random_static;

QString random_symbols = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

QString randomWalletAdress()
{
    QVector<QString> valid_addresses = getUsersInfo(ADDRESS);
    QString random_address;
    QString new_address = "BW";

    bool i_don_want_using_goto = true;

    while(i_don_want_using_goto)
    {
        random_address = "";

        for(int index = 0; index < 19; index++)
        {
            random_address += random_symbols[(Random::get(0, 61))];
        }
        int index = valid_addresses.indexOf(random_address);
        if(index != -1){
            qDebug() << "I`ts here";
        }
        else {
            i_don_want_using_goto = false;
            new_address += random_address;
        }
    }
    return new_address;
}

QString randomWalletKey()
{
    QVector<QString> valid_keys = getUsersInfo(KEY);
    QString random_key;
    QString new_key;

    bool i_don_want_using_goto = true;

    while(i_don_want_using_goto)
    {
        random_key = "";

        int count = 0;
        for(int index = 0; index < 19; index++)
        {
            if(count == 4)
            {
                random_key += "-";
                count = 0;
            } else {
                random_key += random_symbols[(Random::get(0, 61))];
                count++;
            }
        }
        int index = valid_keys.indexOf(random_key);
        if(index != -1){
            qDebug() << "I`ts here";
        }
        else {
            i_don_want_using_goto = false;
            new_key = random_key;
        }
    }
    return new_key;
}
