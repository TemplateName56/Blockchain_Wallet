#include "program_algorithms.h"

#include "client/classes/blockchain.h"
#include <QVector>



string algoritms::Hash(string str)
{
    string rezult;
       int minimallenght = 32;
       int realminimallenght = 32;
       int lenghtStr = (str.size());

       while (minimallenght < lenghtStr)
       {
           minimallenght *= 2;
       }
       if ((minimallenght - lenghtStr) < minimallenght)
       {
           minimallenght *= 2;
       }

       int Counter = minimallenght - lenghtStr;

       for (int i = 0; i < Counter; i++)
       {
           str += ConvertIntoLetter(str[i] + str[i + 1]);
       }



       while (str.size() != realminimallenght)
       {
           for (int i = 0, center = str.size() / 2; i < center; i++)
           {
               rezult += ConvertIntoLetter(str[center - i] + str[center + i]);
           }
           str = rezult;
           rezult.clear();
       }

       int DelSymbols = realminimallenght - 16;

       for (int i = 0, Compresss = realminimallenght / DelSymbols; rezult.size() < 16; i++)
       {
           if (i % Compresss == 0)
           {
               rezult += ConvertIntoLetter(str[i] + str[++i]);
           }
           else
           {
               rezult += str[i];
           }
       }

       return rezult;
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

string algoritms::GenerateLink(string link)
{
    for (int i = 0; i < link.size(); i++)
        {

            if(link[i]==46)
            {
                link[i]= 125;
                continue;
            }if (link[i]>=97&&link[i]<=118)
            {
                link[i]= link[i] + 4;
                continue;
            }if (link[i] >= 65 && link[i] <= 86)
            {
                link[i] = link[i] + 4;
                continue;
            }
            if (link[i]>=119&&link[i]<=122)
            {
                link[i] = link[i] - 22;
                continue;
            }
            if (link[i] >= 87 && link[i] <= 90)
            {
                link[i] = link[i] - 22;
                continue;
            }
            if (link[i] >= 48 && link[i] <= 55)
            {
                link[i] = link[i] +2;
                continue;
            }
            if (link[i] >= 56 && link[i] <= 57)
            {
                link[i] = link[i] - 8;
                continue;
            }
            if (link[i] == 59)
            {
                link[i] = link[i] - 12;
                continue;
            }

            link[i] = link[i] + 2;
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
        for (int i = 8; i < link.length(); i++)
        {
            tmp += link[i];
        }
        for (int i = 0; i < tmp.length() - 3; i++)
        {
            result += tmp[i];
        }

        for (int i = 0; i < result.size(); i++)
        {
            if(result[i]==125)
            {
                result[i]= 46;
                continue;
            }if (result[i] >= 101 && result[i] <= 122)
            {
                result[i] = result[i] - 4;
                continue;
            }if (result[i] >= 69 && result[i] <= 90)
            {
                result[i] = result[i] - 4;
                continue;
            }
            if (result[i] >= 97 && result[i] <= 100)
            {
                result[i] = result[i] + 22;
                continue;
            }
            if (result[i] >= 65 && result[i] <= 68)
            {
                result[i] = result[i] + 22;
                continue;
            }
            if (result[i] >= 50 && result[i] <= 57)
            {
                result[i] = result[i] - 2;
                continue;
            }
            if (result[i] >= 48 && result[i] <= 50)
            {
                result[i] = result[i] + 8;
                continue;
            }
            if (result[i] == 47)
            {
                result[i] = result[i] + 12;
                continue;
            }


            result[i] = result[i] - 2;
        }
        return result;
}


