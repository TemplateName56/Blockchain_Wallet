#include "program_algorithms.h"
#include "client/blockchain/blockchain.h"
#include <QVector>

void algoritms::Sort(int *arr,int n)
{
    for(int i = 1; i < n; ++i)
    {
        for(int j = 0; j < n-i; j++)
        {
            if(arr[j] > arr[j+1])
            {
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

string algoritms::Hash(string str)
{
    string rezult;
       int lenghthash =16;
       int minimallenght = 32;//длина 2^n степени
       int lenghtstr = (str.size()); // длинна строки

       if ((minimallenght - lenghtstr) < minimallenght) //получение минимально длинны превышающей строку
       {
           minimallenght *= 2;
       }
       int Count = minimallenght - lenghtstr;

       for (int i = 0; i < Count; i++)
       {
           str += ConvertIntoLetter(str[i] + str[i + 1]);
       }

       while (str.size() != lenghthash) // получение хеша длинной 16 символов
       {
           for (int i = 0, center = str.size() / 2; i < center; i++)
           {
               rezult += ConvertIntoLetter(str[center - i] + str[center + i]);
           }
           str = rezult;
           rezult.clear();
       }
       return str;
}

int algoritms::ConvertIntoLetter(int rezult)
{
    while (!(((rezult <= 57) && (rezult >= 48)) || ((rezult <= 90) && (rezult >= 65)) || ((rezult <= 122) && (rezult >= 97))))
    {
        if (rezult < 48)
        {
            rezult += 24;
        }
        else
        {
            rezult -= 47;
        }
    }
    return rezult;
}

string algoritms::Encryption(string str, int key)
{
    int code = key;
    code *= 3;
    code += 1;
    code += 6;
    for (int i = 0; i < str.size(); i++)
    {
        str[i] = str[i] + (key+code+i);
    }
    return str;
}

string algoritms::Decryption(string str, int key)
{
    int code = key;
    code *= 3;
    code += 1;
    code += 6;
    for (int i = 0; i < str.size(); i++)
    {
        str[i] = str[i] - (key + code + i);
    }
    return str;
}

string algoritms::GenerateLink(string link)
{
    for (int i = 0; i < link.size(); i++)
    {
        link[i] = link[i] + 4;
    }
    string prevlink = "https://";
    string nextlink = ".ua";
    prevlink += link;
    prevlink += nextlink;
    return prevlink;
}

string algoritms::DecryptionLink(string link)
{
    string result;
    string tmp;
    for (size_t i = 8; i < link.length(); i++)
    {
        tmp += link[i];
    }
    for (int i = 0; i < tmp.length()-3; i++)
    {
        result += tmp[i];
    }

    for (int i = 0; i < result.size(); i++)
    {
        result[i] = result[i] - 4;
    }
    return result;
}


