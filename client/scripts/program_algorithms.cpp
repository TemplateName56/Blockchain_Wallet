#include "program_algorithms.h"

void sort()
{

}

string hashMySTR(string str)
{
    string rezult;
        int minimallenght = 2;//длина 2^n степени
        int realminimallenght = 0;
        int lenghtstr = (str.size()); // длинна строки
        while (minimallenght <= 16)//получение размера строки 32 символа
        {
            realminimallenght = (minimallenght *= 2);
        }

        if ((minimallenght - lenghtstr) < minimallenght) //получение минимально длинны превышающей строку
        {
            minimallenght *= 2;
        }

        int Count = minimallenght - lenghtstr;

        for (int i = 0; i < Count; i++)
        {
            str += ConvertIntoLetter(str[i] + str[i + 1]);
        }

       int lenghthash=realminimallenght-16;
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

int ConvertIntoLetter(int rezult)
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

