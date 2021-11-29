#ifndef PROGRAM_ALGORITHMS_H
#define PROGRAM_ALGORITHMS_H
#include<string>

using std::string;
using std::swap;

class algoritms
{
public:
    string Hash(string str);
    int ConvertIntoLetter(int rezult);
    void Sort(int *arr,int n);
    string Encryption(string str, int key);
    string Decryption(string str, int key);
    int Consensus(int comission);
};

#endif // PROGRAM_ALGORITHMS_H
