#include "blockchain.h"

Block::Block()
{

}

Block::Block(int index, TransactionData data, QString prev_hash)
{
    this->id = index;
    this->block_data = data;
    this->hash = generateHash();
    //qDebug() << this->hash;
    this->prev_hash = prev_hash;
}

QString Block::generateHash()
{
    algoritms hash_block;

    QString to_hash = (block_data.sender + block_data.reciever + QString::number(block_data.amount) + block_data.timestamp + "BWCSALT");
    QString result = QString::fromStdString(hash_block.Hash(to_hash.toStdString()));

    return result;
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

Block::~Block()
{

}

Blockchain::Blockchain()
{
    createGenesisBlock();
}

void Blockchain::createGenesisBlock()
{
    Block genesis(0, TransactionData("genesis", "admin", 9999, BWC), "0");
    this->chain.push_back(genesis);
}

QVector<Block> Blockchain::getChain()
{
    readChain();
    return this->chain;
}



Block Blockchain::getLastBlock()
{
    return this->chain[chain.length() - 1];
}

bool Blockchain::isChainValid()
{
    return true;
}

void Blockchain::readChain()
{

}

void Blockchain::addBlock(int index, TransactionData data, QString prev_hash)
{
    Block new_block(index, data, prev_hash);
    this->chain.push_back(new_block);
}

void Blockchain::show()
{
    // temp show func
    for(int index = 0; index < chain.length(); index++)
    {
        qDebug() << chain[index].getIndex();
        qDebug() << chain[index].getBlockHash();
        qDebug() << chain[index].getPrevBlockHash();
        qDebug() << chain[index].block_data.sender;
        qDebug() << chain[index].block_data.reciever;
        qDebug() << chain[index].block_data.amount;
        qDebug() << chain[index].block_data.coins_type;
        qDebug() << chain[index].block_data.timestamp;
    }
}

Blockchain::~Blockchain()
{

}
