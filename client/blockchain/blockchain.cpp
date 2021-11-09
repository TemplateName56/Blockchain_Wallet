#include "blockchain.h"

Blockchain::Blockchain()
{
    size = 0;
    blocks = new Block[size];
}
