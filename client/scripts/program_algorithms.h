#ifndef PROGRAM_ALGORITHMS_H
#define PROGRAM_ALGORITHMS_H

#include<string>
#include "client/classes/blockchain.h"

using std::string;
using std::swap;

class algoritms
{
public:
    string Hash(string str);
    int ConvertIntoLetter(int rezult);
    string GenerateLink(string link);
    string DecryptionLink(string link);
};
#endif // PROGRAM_ALGORITHMS_H
