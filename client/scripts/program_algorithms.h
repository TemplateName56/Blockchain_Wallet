#ifndef PROGRAM_ALGORITHMS_H
#define PROGRAM_ALGORITHMS_H
#include<string>

using namespace std;

class algoritms
{
 public:
    string Hash(string str);
    int ConvertIntoLetter(int rezult);
    void Sort(int *arr,int n);
    string Encryption(string str, int key);
    string Decryption(string str, int key);
};
/*
void sort();
string hashMySTR(string str);
int ConvertIntoLetter(int rezult);*/


#endif // PROGRAM_ALGORITHMS_H
