#include "new_wallet.h"
#include "json_func.h"
#include <stdlib.h>
#include <time.h>


QString randomWalletAdress()
{
    QVector<QString> valid_addresses = getUsersInfo(ADDRESS);
    QString random_address;
    QString new_address = "BW";

    bool i_don_want_using_goto = true;

    while(i_don_want_using_goto)
    {
        srand(1);
        const char random_symbols[63] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        random_address = "";

        for(int index = 0; index < 19; index++)
        {
            random_address += random_symbols[(rand() % 62)];
        }
        for(int index = 0; index < valid_addresses.length(); index++)
        {
            if(random_address == valid_addresses[index])
            {
                continue;
            }
            else
            {
                new_address += random_address;
                i_don_want_using_goto = false;
                break;
            }
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
        srand(time(0));
        const char random_symbols[63] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
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
                random_key += random_symbols[(rand() % 62)];
                count++;
            }
        }
        for(int index = 0; index < valid_keys.length(); index++)
        {
            if(random_key == valid_keys[index])
            {
                continue;
            }
            else
            {
                new_key += random_key;
                i_don_want_using_goto = false;
                break;
            }
        }
    }

    return new_key;
}
