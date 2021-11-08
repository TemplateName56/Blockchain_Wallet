#include "program_algorithms.h"

void sort()
{

}

string hash(string str)
{
    string rezult;
        int minimallenght = 2;
        int realminimallenght = 0;
        int lenghtstr = (str.size());
        while (minimallenght <= 16)
        {
            realminimallenght = (minimallenght *= 2);
        }
        while (minimallenght < lenghtstr)
        {
            minimallenght *= 2;
        }
        if ((minimallenght - lenghtstr) < minimallenght)
        {
            minimallenght *= 2;
        }

        int addCount = minimallenght - lenghtstr;

        for (int i = 0; i < addCount; i++)
        {
            str += ConvertIntoLetter(str[i] + str[i + 1]);
        }


        int maxlenghtstr = (str.size());
        while (str.size() != realminimallenght) // получение хеша длинной 32 символа
        {
            for (int i = 0, center = str.size() / 2; i < center; i++)
            {
                rezult += ConvertIntoLetter(str[center - i] + str[center + i]);
            }
            str = rezult;
            rezult.clear();
        }

        int rem = realminimallenght - 16;
        int tmp = 16;
        for (int i = 0, Compresss = realminimallenght / rem; rezult.size() < tmp; i++)// сжатие хеша до длинны в 16 символов
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
