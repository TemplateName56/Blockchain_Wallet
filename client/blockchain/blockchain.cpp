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
                                 double fee, short priority)
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
                                 double fee, short priority, QString timestamp)
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

short TransactionData::getPriority() const
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

TransactionData Block::getBlockData()
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
    if(he_is_new)
    {
        if(is_reciever)
        {
            users_balance.push_back(Balance(address, block_data.getAmount(), BWC));
        }
        else
        {
            users_balance.push_back(Balance(address, -(block_data.getAmount() + block_data.getFee()), BWC));
        }
    }
}

Block::~Block()
{

}

Blockchain::Blockchain()
{
    //createGenesisBlock();
    readChain();
}

void Blockchain::createGenesisBlock()
{
    Block genesis(0, TransactionData("genesis", "BW0000000000000000000", 10000, BWC, 0, 1), "0");
    this->chain.push_back(genesis);
    chain.last().setUserBalance(chain.last().getBlockData().getReciever(), true);
}

QVector<Block> Blockchain::getChain()
{

    readChain();
    return this->chain;
}

Block Blockchain::getBlock(int index)
{
    if(index >= 0 && index < chain.length())
    {
        return chain[index];
    }
    throw ProgramException(OUT_OF_RANGE, "Blockchauin::getBlock()");
}

Block Blockchain::getLastBlock()
{
    return this->chain.last();
}

int Blockchain::getChainLenght()
{
    return this->chain.length();
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
        JSON file("chain.json");

        bool genesis = true;
        for(int index = 0; index < file.new_get_array_size_blockchain(); index++)
        {
            if(index > 0)
            {
                genesis = false;
            }
            addBlock(file.new_get_id(index),
                     TransactionData(file.new_get_sender(index),
                                     file.new_get_reciever(index),
                                     file.new_get_amount(index),
                                     toCoinsType(file.new_get_CoinsType(index)),
                                     file.new_get_fee(index),
                                     file.new_get_priority(index),
                                     file.new_get_timestamp(index)),
                     file.new_get_prev_hash(index),
                     file.new_get_hash(index),
                     genesis);
        }
    }  catch (ProgramException &error) {
        error.getError();
    }
}


void Blockchain::addBlock(int index, TransactionData data, QString prev_hash)
{
    this->chain.push_back(Block(index, data, prev_hash));
    chain.last().users_balance = chain[chain.length() - 2].users_balance;
    chain.last().setUserBalance(chain.last().getBlockData().getSender());
    chain.last().setUserBalance(chain.last().getBlockData().getReciever(), true);
}

void Blockchain::addBlock(int index, TransactionData data, QString prev_hash, QString hash, bool genesis)
{
    this->chain.push_back(Block(index, data, prev_hash, hash));
    if(!genesis)
    {
        chain.last().users_balance = chain[chain.length() - 2].users_balance;
        chain.last().setUserBalance(chain.last().getBlockData().getSender());
    }
    chain.last().setUserBalance(chain.last().getBlockData().getReciever(), true);
}

void Blockchain::addBlock(Block new_block)
{
    this->chain.push_back(new_block);
    chain.last().users_balance = chain[chain.length() - 2].users_balance;
    chain.last().setUserBalance(chain.last().getBlockData().getSender());
    chain.last().setUserBalance(chain.last().getBlockData().getReciever(), true);
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
        qDebug() << chain[index].getBlockData().getSender();
        qDebug() << chain[index].getBlockData().getReciever();
        qDebug() << chain[index].getBlockData().getAmount();
        qDebug() << chain[index].getBlockData().getCoinsType();
        qDebug() << chain[index].getBlockData().getTimeStamp();
        qDebug() << "------------------------------------------";
    }
}

Blockchain::~Blockchain()
{

}

Validator::Validator(QObject *parent) : QObject(parent)
{

}

void Validator::addTransaction(TransactionData new_transaction)
{
    chain.addBlock(chain.getLastBlock().getIndex() + 1, new_transaction, chain.getLastBlock().getBlockHash());

    JSON json_file("chain.json");

    //json_file.write_all_chain(chain.getChain());
    json_file.write_all_chain(chain.getLastBlock());
    //chain.writeChain();
    authority += 1;

    emit sendTransaction(chain.getLastBlock().getBlockData().getReciever(), chain.getLastBlock().getBlockData());
}

Blockchain Validator::getBlockChain()
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
