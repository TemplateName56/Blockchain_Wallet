#ifndef PROGRAM_ALGORITHMS_H
#define PROGRAM_ALGORITHMS_H

#include<string>
#include "client/blockchain/blockchain.h"

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
    //Validator Consensus(int comission, Validator *arr,int size, Blockchain chainblock);
    //void compareValidator(Validator &val_1, Validator &val_2);
};
#endif // PROGRAM_ALGORITHMS_H
