#include "blockchain.h"

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
        break;
    }
}

double Balance::setBalance(double amount, CoinsType coins_type)
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

QString Block::generateHash()
{
    algoritms hash_block;

    QString to_hash = (block_data.getSender() + block_data.getReciever() +
                       QString::number(block_data.getAmount()) + QString::number(block_data.getFee()) +
                       QString::number(block_data.getPriority()) + block_data.getTimeStamp() + "SALT");

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
    createGenesisBlock();
}

void Blockchain::createGenesisBlock()
{
    Block genesis(0, TransactionData("genesis", "BW0000000000000000000", 9999.999999, BWC, 0, 1), "0");
    this->chain.push_back(genesis);
    chain.last().setUserBalance(chain.last().block_data.getReciever(), true);
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
        new_block_data.insert("Sender", chain[index].block_data.getSender());
        new_block_data.insert("Reciever", chain[index].block_data.getReciever());
        new_block_data.insert("Amount", chain[index].block_data.getAmount());
        new_block_data.insert("Coins Type", chain[index].block_data.getCoinsType());
        new_block_data.insert("Fee", chain[index].block_data.getFee());
        new_block_data.insert("Priority", chain[index].block_data.getPriority());
        new_block_data.insert("TimeStamp", chain[index].block_data.getTimeStamp());

        block_data_array.removeFirst();
        block_data_array.push_back(new_block_data);

        while(balances.count())
        {
            balances.pop_back();
        }
        for(int j = 0; j < chain[index].users_balance.length(); j++)
        {
            balance.insert("Address", chain[index].users_balance[j].getAddress());
            balance.insert("Balance BWC", chain[index].users_balance[j].getBalance(BWC));
            balance.insert("Balance BWC-N", chain[index].users_balance[j].getBalance(BWC_N));
            balance.insert("Balance BWC-Q", chain[index].users_balance[j].getBalance(BWC_Q));
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
    chain.last().setUserBalance(chain.last().block_data.getSender());
    chain.last().setUserBalance(chain.last().block_data.getReciever(), true);
}

void Blockchain::addBlock(Block new_block)
{
    this->chain.push_back(new_block);
    chain.last().users_balance = chain[chain.length() - 2].users_balance;
    chain.last().setUserBalance(chain.last().block_data.getSender());
    chain.last().setUserBalance(chain.last().block_data.getReciever(), true);
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
        qDebug() << chain[index].block_data.getSender();
        qDebug() << chain[index].block_data.getReciever();
        qDebug() << chain[index].block_data.getAmount();
        qDebug() << chain[index].block_data.getCoinsType();
        qDebug() << chain[index].block_data.getTimeStamp();
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
    transactions_queue.push(new_transaction);
    chain.addBlock(chain.getLastBlock().getIndex(), new_transaction, chain.getLastBlock().getBlockHash());
}

bool operator<(const TransactionData& T1, const TransactionData& T2)
{
    return T1.getPriority() < T2.getPriority();
}
