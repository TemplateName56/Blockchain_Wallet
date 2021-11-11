#include "blockchain.h"

Block::Block(int index, TransactionData data, QString prev_hash)
{
    this->id = index;
    this->block_data = data;
    this->hash = generateHash();
    this->prev_hash = prev_hash;
}

QString Block::generateHash()
{
    QString to_hash = (block_data.sender + block_data.reciever + QString::number(block_data.amount) + block_data.timestamp);

    return to_hash;
}

int Block::getIndex()
{
    return this->id;
}

QString Block::getBlockHash()
{
    return this->hash;
}

QString Block::getPrevBlockHash()
{
    return this->prev_hash;
}

Balance Block::getUserBalance(QString address)
{
    for(int index = 0; index < users_balance.length(); index++)
    {
        if(address == users_balance[index].address)
        {
            return users_balance[index];
        }
    }
}

void Block::setUserBalance(QString address)
{
    for(int index = 0; index < users_balance.length(); index++)
    {
        if(address == users_balance[index].address)
        {
            switch (block_data.coins_type) {
            case BWC:
                users_balance[index].balance_amount_BWC += block_data.amount;
                break;
            case BWC_N:
                users_balance[index].balance_amount_BWC_N += block_data.amount;
                break;
            case BWC_Q:
                users_balance[index].balance_amount_BWC_Q += block_data.amount;
                break;
            default:
                break;
            }
        }
    }
}

Blockchain::Blockchain()
{

}

QVector<Block> Blockchain::getChain()
{

}

Block Blockchain::getLastBlock()
{

}

void Blockchain::readChain()
{

}

bool Blockchain::isChainValid()
{

}

void Blockchain::addBlock()
{

}

Blockchain::~Blockchain()
{

}
