#include "blockchain.h"

Block::Block()
{

}

Block::Block(int index, TransactionData data, QString prev_hash)
{
    this->id = index;
    this->block_data = data;
    this->hash = generateHash();
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
    return Balance(address, 0);
}

void Block::setUserBalance(QString address, bool is_reciever)
{
    bool he_is_new = true;

    for(int index = 0; index < users_balance.length(); index++)
    {
        if(address == users_balance[index].address)
        {
            he_is_new = false;
            if(is_reciever)
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
            else
            {
                switch (block_data.coins_type) {
                case BWC:
                    users_balance[index].balance_amount_BWC -= block_data.amount;
                    break;
                case BWC_N:
                    users_balance[index].balance_amount_BWC_N -= block_data.amount;
                    break;
                case BWC_Q:
                    users_balance[index].balance_amount_BWC_Q -= block_data.amount;
                    break;
                default:
                    break;
                }
            }
        }
    }
    if(he_is_new)
    {
        if(is_reciever)
        {
            users_balance.push_back(Balance(address, block_data.amount, BWC));
        }
        else
        {
            users_balance.push_back(Balance(address, -block_data.amount, BWC));
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
    chain.last().setUserBalance(chain.last().block_data.reciever, true);
}

QVector<Block> Blockchain::getChain()
{
    readChain();
    return this->chain;
}

Block Blockchain::getLastBlock()
{
    return this->chain.last();
}

bool Blockchain::isChainValid()
{
    for(int index = (chain.length() - 2); index >= 0; index--)
    {
        if(chain[index].getBlockHash() != chain[index + 1].getPrevBlockHash())
        {
            return false;
        }
    }
    return true;
}

void Blockchain::collisionCheck()
{
    QVector<QString> hashes;
    for(int index = 0; index < chain.length(); index++)
    {
        hashes.push_back(chain[index].getBlockHash());
    }
    for(int index = 0; index < hashes.length(); index++)
    {
        if(hashes.lastIndexOf(hashes[index]) != index)
        {
            qDebug() << "We more than two, but less then four!";
            throw ProgramException(HASH_COLLISION);
        }
    }
}

void Blockchain::readChain()
{
    try {
        fileExists("chain.json");
    }  catch (ProgramException &error) {
        error.getError();
    }
    QFileInfo file_info("chain.json");
    QDir::setCurrent(file_info.path());
    QFile json_file("chain.json");

    if (!json_file.open(QIODevice::ReadOnly))
    {
        throw ProgramException(FILE_READ_ERROR);
    }
    json_file.close();
}

void Blockchain::writeChain()
{
    try {
        fileExists("chain.json");
    }  catch (ProgramException &error) {
        error.getError();
    }
    QJsonObject new_chain;
    QJsonArray chain_array;

    QJsonArray balances;
    QJsonObject balance;

    QJsonArray block_data_array;
    QJsonObject new_block_data;
    QJsonObject new_block;

    for(int index = 0; index < chain.length(); index++)
    {
        new_block_data.insert("Sender", chain[index].block_data.sender);
        new_block_data.insert("Reciever", chain[index].block_data.reciever);
        new_block_data.insert("Amount", chain[index].block_data.amount);
        new_block_data.insert("Coins Type", chain[index].block_data.coins_type);
        new_block_data.insert("TimeStamp", chain[index].block_data.timestamp);

        block_data_array.removeFirst();
        block_data_array.push_back(new_block_data);

        while(balances.count())
        {
            balances.pop_back();
        }
        for(int j = 0; j < chain[index].users_balance.length(); j++)
        {
            balance.insert("Address", chain[index].users_balance[j].address);
            balance.insert("Balance BWC", chain[index].users_balance[j].balance_amount_BWC);
            balances.push_back(balance);
        }

        new_block.insert("Block Data", block_data_array);

        new_block.insert("Id", chain[index].getIndex());
        new_block.insert("Hash", chain[index].getBlockHash());
        new_block.insert("Previous Hash", chain[index].getPrevBlockHash());

        new_block.insert("Balaces", balances);

        chain_array.push_back(new_block);
    }
    new_chain.insert("Blockchain", chain_array);

    QFileInfo file_info("chain.json");
    QDir::setCurrent(file_info.path());
    QFile json_file("chain.json");

    if(!json_file.open(QIODevice::WriteOnly))
    {
        throw ProgramException(FILE_WRITE_ERROR);
    }
    json_file.write(QJsonDocument(new_chain).toJson(QJsonDocument::Indented));
    json_file.close();
}

void Blockchain::addBlock(int index, TransactionData data, QString prev_hash)
{
    this->chain.push_back(Block(index, data, prev_hash));
    chain.last().users_balance = chain[chain.length() - 2].users_balance;
    chain.last().setUserBalance(chain.last().block_data.sender);
    chain.last().setUserBalance(chain.last().block_data.reciever, true);
}

void Blockchain::show()
{
    // temp show func
    for(int index = 0; index < chain.length(); index++)
    {
        qDebug() << "------------------------------------------";
        qDebug() << chain[index].getIndex();
        qDebug() << chain[index].getBlockHash();
        qDebug() << chain[index].getPrevBlockHash();
        qDebug() << chain[index].block_data.sender;
        qDebug() << chain[index].block_data.reciever;
        qDebug() << chain[index].block_data.amount;
        qDebug() << chain[index].block_data.coins_type;
        qDebug() << chain[index].block_data.timestamp;
        qDebug() << "------------------------------------------";
    }
}

Blockchain::~Blockchain()
{

}
