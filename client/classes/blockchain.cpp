#include "blockchain.h"
#include "client/scripts/json_func.h"

#include <QCoreApplication>

CoinsType toCoinsType(int CoinId)
{
    switch (CoinId) {
    case 0:
        return BWC;
        break;
    case 1:
        return BWC_N;
        break;
    case 2:
        return BWC_Q;
        break;
    default:
        return CoinsTypeERROR;
        break;
    }
}

Balance::Balance()
{

}

Balance::Balance(QString address, double balance_amount,
                 CoinsType coins_type){
    this->address = address;
    switch (coins_type) {
    case BWC:
        this->balance_amount_BWC = balance_amount;
        break;
    case BWC_N:
        this->balance_amount_BWC_N = balance_amount;
        break;
    case BWC_Q:
        this->balance_amount_BWC_Q = balance_amount;
        break;
    default:
        break;
    }
}

Balance::Balance(QString address, double balance_amount){
    this->address = address;
    this->balance_amount_BWC = balance_amount;
    this->balance_amount_BWC_N = balance_amount;
    this->balance_amount_BWC_Q = balance_amount;
}

QString Balance::getAddress()
{
    return this->address;
}

double Balance::getBalance(CoinsType coins_type)
{
    switch (coins_type) {
    case BWC:
        return this->balance_amount_BWC;
        break;
    case BWC_N:
        return this->balance_amount_BWC_N;
        break;
    case BWC_Q:
        return this->balance_amount_BWC_Q;
        break;
    default:
        return 0;
        break;
    }
}

void Balance::setBalance(double amount, CoinsType coins_type)
{
    switch (coins_type) {
    case BWC:
        this->balance_amount_BWC += amount;
        break;
    case BWC_N:
        this->balance_amount_BWC_N += amount;
        break;
    case BWC_Q:
        this->balance_amount_BWC_Q += amount;
        break;
    default:
        break;
    }
}

TransactionData::TransactionData()
{

}

TransactionData::TransactionData(QString sender, QString reciever,
                                 double amount, CoinsType coins_type,
                                 double fee, int priority)
{
    QDateTime current_time = QDateTime::currentDateTime();
    this->sender = sender;
    this->reciever = reciever;

    this->amount = amount;
    this->coins_type = coins_type;

    this->fee_amount = fee;
    this->priority = priority;

    this->timestamp = current_time.toString();
}

TransactionData::TransactionData(QString sender, QString reciever,
                                 double amount, CoinsType coins_type,
                                 double fee, int priority, QString timestamp)
{
    this->sender = sender;
    this->reciever = reciever;

    this->amount = amount;
    this->coins_type = coins_type;

    this->fee_amount = fee;
    this->priority = priority;

    this->timestamp = timestamp;
}

QString TransactionData::getSender()
{
    return this->sender;
}

QString TransactionData::getReciever()
{
    return this->reciever;
}

double TransactionData::getAmount()
{
    return this->amount;
}

CoinsType TransactionData::getCoinsType()
{
    return this->coins_type;
}

double TransactionData::getFee()
{
    return this->fee_amount;
}

int TransactionData::getPriority()
{
    return this->priority;
}

QString TransactionData::getTimeStamp()
{
    return this->timestamp;
}

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

Block::Block(int index, TransactionData data, QString prev_hash, QString hash)
{
    this->id = index;
    this->block_data = data;
    this->hash = hash;
    this->prev_hash = prev_hash;
}

QVector<Balance> Block::getBalances()
{
    return this->users_balance;
}

void Block::setBalances(QVector<Balance> users_balance)
{
    this->users_balance = users_balance;
}

QString Block::generateHash()
{
    algoritms hash_block;

    QString to_hash = (block_data.getSender() +
                       block_data.getReciever() +
                       QString::number(block_data.getFee()) +
                       block_data.getTimeStamp() + "SALT");

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

TransactionData& Block::getBlockData()
{
    return this->block_data;
}

Balance Block::getUserBalance(QString address)
{
    for(int index = 0; index < users_balance.length(); index++)
    {
        if(address == users_balance[index].getAddress())
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
        if(address == users_balance[index].getAddress())
        {
            he_is_new = false;
            if(is_reciever)
            {
                users_balance[index].setBalance(block_data.getAmount(), block_data.getCoinsType());
            }
            else
            {
                users_balance[index].setBalance(-(block_data.getAmount() + block_data.getFee()), block_data.getCoinsType());
            }
        }
    }
    if(he_is_new && address != "genesis")
    {
        if(is_reciever)
        {
            users_balance.push_back(Balance(address, block_data.getAmount(), block_data.getCoinsType()));
        }
        else
        {
            users_balance.push_back(Balance(address, -(block_data.getAmount() + block_data.getFee()), block_data.getCoinsType()));
        }
    }
}

Block::~Block()
{

}

Blockchain::Blockchain()
{
    //createGenesisBlock();
}

void Blockchain::createGenesisBlock()
{
    Block genesis(0, TransactionData("genesis", "BW0000000000000000000", 10000, BWC, 0, 1), "0");
    this->chain.push_back(genesis);
    chain.last().setUserBalance(chain.last().getBlockData().getReciever(), true);
}

QVector<Block>& Blockchain::getChain()
{
    if(this->chain.length() != 0)
    {
        return this->chain;
    }
    else
    {
        throw ProgramException(CHAIN_LENGTH_ERROR, "Blockchain Class");
    }
}

Block& Blockchain::getBlock(int index)
{
    try {
        if(index >= 0 && index < chain.length())
        {
            return chain[index];
        }
        else
        {
            throw ProgramException(OUT_OF_RANGE, "Blockchauin::getBlock()");
        }
    }  catch (ProgramException &error) {
        error.getError();
    }
}

Block& Blockchain::getLastBlock()
{
    return this->chain.last();
}

int Blockchain::getChainLenght()
{
    return this->chain.length();
}

void Blockchain::isChainValid()
{
    for(int index = (chain.length() - 2); index >= 0; index--)
    {
        if(chain[index].getBlockHash() != chain[index + 1].getPrevBlockHash())
        {
            throw ProgramException(CHAIN_NOT_VALID);
        }
    }
}

void Blockchain::collisionCheck()
{
    if(chain.length() != 0)
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
                throw ProgramException(BLOCKCHAIN_HASH_COLLISION);
                break;
            }
        }
    }
}

void Blockchain::addBlock(int index, TransactionData data, QString prev_hash)
{
    try {
        this->chain.push_back(Block(index, data, prev_hash));
        collisionCheck();
        isChainValid();
        chain.last().setBalances(chain[chain.length() - 2].getBalances());
        chain.last().setUserBalance(chain.last().getBlockData().getSender());
        chain.last().setUserBalance(chain.last().getBlockData().getReciever(), true);
    }  catch (ProgramException &error) {
        error.getError();
        this->chain.pop_back();
    }
}

void Blockchain::addBlock(int index, TransactionData data, QString prev_hash, QString hash, bool genesis)
{
    try {
        this->chain.push_back(Block(index, data, prev_hash, hash));
        if(!genesis)
        {
            collisionCheck();
            isChainValid();
            chain.last().setBalances(chain[chain.length() - 2].getBalances());
            chain.last().setUserBalance(chain.last().getBlockData().getSender());
        }
        chain.last().setUserBalance(chain.last().getBlockData().getReciever(), true);
    }  catch (ProgramException &error) {
        error.getError();
        this->chain.pop_back();
    }
}

Blockchain::~Blockchain()
{

}

Validator::Validator(QObject *parent) : QObject(parent)
{
    try {
        JSON blockchain_json("chain.json");
        blockchain_json.read_all_chain(getBlockChain());
    }  catch (ProgramException &error) {
        error.getError();
    }
}

void Validator::addTransaction(TransactionData new_transaction)
{
    try {
        chain.addBlock(chain.getLastBlock().getIndex() + 1, new_transaction, chain.getLastBlock().getBlockHash());
        JSON json_file("chain.json");
        json_file.write_all_chain(chain.getLastBlock());
        authority += 1;
        emit sendTransaction(chain.getLastBlock().getBlockData().getReciever(), chain.getLastBlock().getBlockData());
    }  catch (ProgramException &error) {
        error.getError();
    }
}

Blockchain &Validator::getBlockChain()
{
    return this->chain;
}
void Validator::setBlockChain(Blockchain temp)
{
    this->chain = temp;
}

int Validator::getAuthority()
{
    return this->authority;
}

void Validator::setAuthority(int authority)
{
    this->authority = authority;
}

void Validator::loadTransactions()
{
    foreach(Block _block, getBlockChain().getChain())
    {
        emit sendTransaction(_block.getBlockData().getReciever(), _block.getBlockData());
    }
}
