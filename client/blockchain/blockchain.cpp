#include "blockchain.h"

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

//void Blockchain::readChain()
//{
//    try {
//        fileExists("chain.json");
//    }  catch (ProgramException &error) {
//        error.getError();
//    }
//    QFileInfo file_info("chain.json");
//    QDir::setCurrent(file_info.path());
//    QFile json_file("chain.json");

//    if (!json_file.open(QIODevice::ReadOnly))
//    {
//        throw ProgramException(FILE_READ_ERROR);
//    }
//    QJsonDocument json_document(QJsonDocument::fromJson(json_file.readAll()));
//    json_file.close();

//    QJsonObject temp = json_document.object();
//    QJsonArray json_array = temp["Blockchain"].toArray();

//    bool genesis = true;

//    for(int index = 0; index < json_array.size(); index++)
//    {
//        QJsonObject subtree_1 = json_array.at(index).toObject();
//        QJsonArray subtree_2 = subtree_1["Block Data"].toArray();

//        QJsonObject subtree = subtree_2.at(0).toObject();

//        if(index > 0)
//        {
//            genesis = false;
//        }

//        addBlock(subtree_1.value("Id").toInt(),
//                 TransactionData(subtree.value("Sender").toString(),
//                                 subtree.value("Reciever").toString(),
//                                 subtree.value("Amount").toDouble(),
//                                 toCoinsType(subtree.value("Coins Type").toInt()),
//                                 subtree.value("Fee").toDouble(),
//                                 subtree.value("Priority").toDouble(),
//                                 subtree.value("TimeStamp").toString()),
//                 subtree_1.value("Previous Hash").toString(),
//                 subtree_1.value("Hash").toString(),
//                 genesis);
//    }
//}


//void Blockchain::writeChain()
//{
//    try {
//        fileExists("chain.json");
//    }  catch (ProgramException &error) {
//        error.getError();
//    }
//    QJsonObject new_chain;
//    QJsonArray chain_array;

//    QJsonArray balances;
//    QJsonObject balance;

//    QJsonArray block_data_array;
//    QJsonObject new_block_data;
//    QJsonObject new_block;

//    for(int index = 0; index < chain.length(); index++)
//    {
//        new_block_data.insert("Sender", chain[index].getBlockData().getSender());
//        new_block_data.insert("Reciever", chain[index].getBlockData().getReciever());
//        new_block_data.insert("Amount", chain[index].getBlockData().getAmount());
//        new_block_data.insert("Coins Type", chain[index].getBlockData().getCoinsType());
//        new_block_data.insert("Fee", chain[index].getBlockData().getFee());
//        new_block_data.insert("Priority", chain[index].getBlockData().getPriority());
//        new_block_data.insert("TimeStamp", chain[index].getBlockData().getTimeStamp());

//        block_data_array.removeFirst();
//        block_data_array.push_back(new_block_data);

//        while(balances.count())
//        {
//            balances.pop_back();
//        }
//        for(int j = 0; j < chain[index].users_balance.length(); j++)
//        {
//            balance.insert("Address", chain[index].users_balance[j].getAddress());
//            balance.insert("Balance BWC", chain[index].users_balance[j].getBalance(BWC));
//            balance.insert("Balance BWC-N", chain[index].users_balance[j].getBalance(BWC_N));
//            balance.insert("Balance BWC-Q", chain[index].users_balance[j].getBalance(BWC_Q));
//            balances.push_back(balance);
//        }

//        new_block.insert("Block Data", block_data_array);

//        new_block.insert("Id", chain[index].getIndex());
//        new_block.insert("Hash", chain[index].getBlockHash());
//        new_block.insert("Previous Hash", chain[index].getPrevBlockHash());

//        new_block.insert("Balaces", balances);

//        chain_array.push_back(new_block);
//    }
//    new_chain.insert("Blockchain", chain_array);

//    QFileInfo file_info("chain.json");
//    QDir::setCurrent(file_info.path());
//    QFile json_file("chain.json");

//    if(!json_file.open(QIODevice::WriteOnly))
//    {
//        throw ProgramException(FILE_WRITE_ERROR);
//    }
//    json_file.write(QJsonDocument(new_chain).toJson(QJsonDocument::Indented));
//    json_file.close();
//}


void Blockchain::readChain()
{
    JSON file("chain.json");
    bool genesis = true;

    for(int index = 0; index < file.new_get_array_size_blockchain(); index++)
    {

            if(index > 0)
            {
                genesis = false;
            }
            addBlock(file.new_get_id(index),
                     TransactionData(file.new_get_sender(index+1,0),
                                     file.new_get_reciever(index+1,0),
                                     file.new_get_amount(index+1,0),
                                     toCoinsType(file.new_get_CoinsType(index+1, 0)),
                                     file.new_get_fee(index+1,0),
                                     file.new_get_priority(index+1,0),
                                     file.new_get_timestamp(index+1,0)),
                    file.new_get_prev_hash(index+1),
                    file.new_get_hash(index+1),
                     genesis);

    }
}

void Blockchain::writeChain()
{
    JSON file_write("chain_write.json");
    file_write.new_append_hash2_id(chain.last().getBlockHash(),
            chain.last().getIndex(), chain.last().getPrevBlockHash());

    file_write.new_write_block_data(chain.last().getIndex(),chain.last().getBlockData().getSender(),
                                    chain.last().getBlockData().getReciever(),
                                    chain.last().getBlockData().getAmount(),
                                    chain.last().getBlockData().getCoinsType(),
                                    chain.last().getBlockData().getFee(),
                                    chain.last().getBlockData().getPriority(),
                                    chain.last().getBlockData().getTimeStamp()
                                    );
    for(int j = 0; j < chain.last().users_balance.length(); j++){
        file_write.new_append_balances(chain.last().getIndex(),
                    chain.last().users_balance[j].getAddress(),
                    chain.last().users_balance[j].getBalance(BWC),
                    chain.last().users_balance[j].getBalance(BWC_N),
                    chain.last().users_balance[j].getBalance(BWC_Q));
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

    chain.writeChain();
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
