#include "json_func.h"
#include "client/blockchain/blockchain.h"
//#include "client/classes/users.cpp"
//#include "client/blockchain/blockchain.cpp"
#include "client/classes/users.h"

languages tolanguages1(int language)
{
    switch (language) {
    case 0:
        return ENGLISH;
        break;
    case 1:
        return UKRANIAN;
        break;
    case 2:
        return RUSSIAN;
    default:
        return UKRANIAN; //тут по идее должно быть что-то типа languageTypeERROR как в функции toCoinsType
        break;
    }
}

CoinsType toCoinsType1(int CoinId)
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


JSON::JSON(QString fileName)
{
         filename = fileName;
         fileExists(filename);
         QString val2;

         QFile json_file(filename);

         if(!json_file.open(QIODevice::ReadOnly | QIODevice::Text))
         {
             throw ProgramException(FILE_READ_ERROR);
         }
         val2 = json_file.readAll();
         json_file.close();

         doc = QJsonDocument::fromJson(val2.toUtf8());
}

void JSON::read_all_chain(Blockchain &a){
    JSON file(filename);

    bool genesis = true;
    qDebug() << "\narray_size:" << file.get_array_size_blockchain();
    for(int index = 0; index < file.get_array_size_blockchain(); index++)
    {

            if(index > 0)
            {
                genesis = false;
            }
            qDebug() << "Index: " << index;
            qDebug() << "\nreadChain:";
            qDebug() << "Amount:" << file.get_amount(index);
            qDebug() << "Reciever:" << file.get_reciever(index);
            qDebug() << "Sender:" << file.get_sender(index);
            qDebug() << "TimeStamp:" << file.get_timestamp(index);
            a.addBlock(file.get_id(index),
                     TransactionData(file.get_sender(index),
                                     file.get_reciever(index),
                                     file.get_amount(index),
                                     toCoinsType1(file.get_CoinsType(index)),
                                     file.get_fee(index),
                                     file.get_priority(index),
                                     file.get_timestamp(index)),
                    file.get_prev_hash(index),
                    file.get_hash(index),
                     genesis);


    }
}

void JSON::read_all_chain(Validator &a){
    JSON file(filename);

    bool genesis = true;
    qDebug() << "\narray_size:" << file.get_array_size_blockchain();
    for(int index = 0; index < file.get_array_size_blockchain(); index++)
    {

            if(index > 0)
            {
                genesis = false;
            }
            qDebug() << "Index: " << index;
            qDebug() << "\nreadChain:";
            qDebug() << "Amount:" << file.get_amount(index);
            qDebug() << "Reciever:" << file.get_reciever(index);
            qDebug() << "Sender:" << file.get_sender(index);
            qDebug() << "TimeStamp:" << file.get_timestamp(index);

            a.getBlockChain().addBlock(file.get_id(index),
                     TransactionData(file.get_sender(index),
                                     file.get_reciever(index),
                                     file.get_amount(index),
                                     toCoinsType1(file.get_CoinsType(index)),
                                     file.get_fee(index),
                                     file.get_priority(index),
                                     file.get_timestamp(index)),
                    file.get_prev_hash(index),
                    file.get_hash(index),
                     genesis);


    }
}


void JSON::set_language_user(QString address, int language){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();

    QJsonObject GBjsonObj;
    GBjsonObj = doc.object();

    for(int i = 0; i <  jsonArray.size(); i++){
        QJsonObject subtree = jsonArray.at(i).toObject();
        QString str = subtree.value("address").toString();
        if(str == address){
            QJsonObject subtree = jsonArray.at(i).toObject();
            QString address_file = subtree.value("address").toString();
            int admin = subtree.value("admin").toInt();
            QString walletKey = subtree.value("walletKey").toString();
            //int language_file = subtree.value("language").toInt();

            QJsonObject jsonObj3;
            jsonObj3.insert("address", address_file);
            jsonObj3.insert("admin", admin);
            jsonObj3.insert("walletKey", walletKey);
            jsonObj3.insert("language", language );
            jsonArray.replace(i, jsonObj3);
        }
    }
    GBjsonObj["users"] = jsonArray;
    doc.setObject(GBjsonObj);

    if(!json_file.open(QFile::WriteOnly))
    {
        throw ProgramException(FILE_WRITE_ERROR);
    }
    json_file.write(doc.toJson());
}

int JSON::get_language_user(QString address){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    for(int i = 0; i <  jsonArray.size(); i++){
        QJsonObject subtree = jsonArray.at(i).toObject();
        QString str = subtree.value("address").toString();
        if(str == address){
            int language_file = subtree.value("language").toInt();
            //qDebug() << "-=-=-=-Get_language-=-=-=" <<jsonArray;
            return language_file ;
        }
    }
    return 0;

}

int JSON::get_array_size_users(){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    return jsonArray.size();
}

void JSON::write_all_chain(Block chain){
    //chain.getBlockData().getAmount();

    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    QJsonObject Blockchain_obj = doc.object();
     QJsonDocument document = doc;

     QJsonObject block_obj;

     //QJsonArray jsonArray2;
     QJsonObject block_data_obj;
     block_data_obj.insert("Amount", chain.getBlockData().getAmount());
     block_data_obj.insert("Coins Type", chain.getBlockData().getCoinsType());
     block_data_obj.insert("Fee", chain.getBlockData().getFee());
     block_data_obj.insert("Priority", chain.getBlockData().getPriority());
     block_data_obj.insert("Reciever", chain.getBlockData().getReciever());
     block_data_obj.insert("Sender", chain.getBlockData().getSender());
     block_data_obj.insert("TimeStamp", chain.getBlockData().getTimeStamp());

     QJsonArray balances;
     QJsonObject balance;
     for(int j = 0; j < chain.users_balance.length(); j++){
         balance.insert("Address", chain.users_balance[j].getAddress());
         balance.insert("Balance BWC", chain.users_balance[j].getBalance(BWC));
         balance.insert("Balance BWC-N", chain.users_balance[j].getBalance(BWC_N));
         balance.insert("Balance BWC-Q", chain.users_balance[j].getBalance(BWC_Q));
         balances.append(balance);
     }

     block_obj.insert("Balances", balances);

     block_obj.insert("Id", chain.getIndex());
     block_obj.insert("Hash", chain.getBlockHash());
     block_obj.insert("Previous Hash", chain.getPrevBlockHash());
     block_obj.insert("Block Data",block_data_obj);
     jsonArray.append(block_obj);

     Blockchain_obj["Blockchain"] = jsonArray;
     document.setObject(Blockchain_obj);
     //qDebug() << "\ndoc_after_set :" << doc;
     if(!json_file.open(QFile::WriteOnly))
     {
         throw ProgramException(FILE_WRITE_ERROR);
     }
     json_file.write(document.toJson());
}


QString JSON:: get_hash(int number_block){
    QJsonObject root = doc.object();
    QJsonArray jsonArray = root["Blockchain"].toArray();
    QJsonValue value = jsonArray.at(number_block);
    QString address = value["Hash"].toString();;
    return address;
}

QString JSON:: get_prev_hash(int number_block){
    QJsonObject root = doc.object();
    QJsonArray jsonArray = root["Blockchain"].toArray();
    QJsonValue value = jsonArray.at(number_block);
    QString Prev_hash = value["Previous Hash"].toString();;
    return Prev_hash;
}

int JSON:: get_id(int number_block){
    QJsonObject root = doc.object();
    QJsonArray jsonArray = root["Blockchain"].toArray();
    QJsonValue value = jsonArray.at(number_block);
    int id = value["Id"].toInt();
    return id;
}

double JSON:: get_amount(int number_block){
    QJsonObject root = doc.object();
    QJsonArray jsonArray = root.value("Blockchain").toArray();
    QJsonValue value = jsonArray.at(number_block);
    QJsonObject obj_data = value["Block Data"].toObject();
    double amount = obj_data["Amount"].toDouble();
    return amount;
}

double JSON:: get_fee(int number_block){
    QJsonObject root = doc.object();
    QJsonArray jsonArray = root.value("Blockchain").toArray();
    QJsonValue value = jsonArray.at(number_block);
    QJsonObject obj_data = value["Block Data"].toObject();
    double fee = obj_data["Fee"].toDouble();
    return fee;
}

int JSON:: get_priority(int number_block){
    QJsonObject root = doc.object();
    QJsonArray jsonArray = root.value("Blockchain").toArray();
    QJsonValue value = jsonArray.at(number_block);
    QJsonObject obj_data = value["Block Data"].toObject();
    int priority = obj_data["Priority"].toInt();
    return priority;
}

QString JSON:: get_reciever(int number_block){
    QJsonObject root = doc.object();
    QJsonArray jsonArray = root.value("Blockchain").toArray();
    QJsonValue value = jsonArray.at(number_block);
    QJsonObject obj_data = value["Block Data"].toObject();
    QString reciever = obj_data["Reciever"].toString();
    return reciever;
}

QString JSON:: get_sender(int number_block){
    QJsonObject root = doc.object();
    QJsonArray jsonArray = root.value("Blockchain").toArray();
    QJsonValue value = jsonArray.at(number_block);
    QJsonObject obj_data = value["Block Data"].toObject();
    QString sender = obj_data["Sender"].toString();
    return sender;
}

QString JSON:: get_timestamp(int number_block){
    QJsonObject root = doc.object();
    QJsonArray jsonArray = root.value("Blockchain").toArray();
    QJsonValue value = jsonArray.at(number_block);
    QJsonObject obj_data = value["Block Data"].toObject();
    QString timestamp = obj_data["TimeStamp"].toString();
    return timestamp;
}


int JSON:: get_CoinsType(int number_block){
    QJsonObject root = doc.object();
    QJsonArray jsonArray = root.value("Blockchain").toArray();
    QJsonValue value = jsonArray.at(number_block);
    QJsonObject obj_data = value["Block Data"].toObject();
    int coins_type = obj_data["Coins Type"].toInt();
    return coins_type ;
}

int JSON:: get_array_size_blockchain(){
    QJsonObject root = doc.object();
    QJsonArray jsonArray = root["Blockchain"].toArray();
    return jsonArray.size();
}

int JSON:: get_array_size_balances(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    QJsonObject obj_balanse = jsonArray[number_block-1].toObject();
    QJsonArray gps_array = obj_balanse.value("Balances").toArray();
    return gps_array.size();
}



QString JSON::get_address_user(int num){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    QString address_file;
    QJsonObject address_obj = jsonArray.at(num).toObject();
    address_file = address_obj.value("address").toString();
    return address_file;


}

QString JSON::get_wallet_key_user(int num){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    QString wallet_key;
    QJsonObject walletKey_obj = jsonArray.at(num).toObject();
     wallet_key = walletKey_obj.value("walletKey").toString();
    return wallet_key;


}

bool JSON::get_admin_user(int num){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    bool admin;
    QJsonObject admin_obj = jsonArray.at(num).toObject();
    admin = admin_obj.value("admin").toInt();
    return admin;
}

int JSON::get_language_user(int num){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    int language;
    QJsonObject language_obj = jsonArray.at(num).toObject();
    language = language_obj.value("language").toInt();
    return language;
}

void JSON::read_users_file(Users &a)
    {
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();

    QString address_file;
    QString wallet_key;
    bool admin;
    int language;

    for(int index = 0; index < jsonArray.size(); index++){
        QJsonObject subtree = jsonArray.at(index).toObject();
        address_file = subtree.value("address").toString();
        wallet_key = subtree.value("walletKey").toString();
        admin = subtree.value("admin").toInt();
        language = subtree.value("language").toInt();
    a.users_information.push_back(User(address_file,
                                    wallet_key,
                                    tolanguages1(language),
                                    admin));
    }
}

void JSON::write_users_file(Users &a)
{
    QFile json_file(filename);
    //QJsonObject json = doc.object();
    //QJsonArray jsonArray = json["users"].toArray();
    QJsonObject users_obj;
    users_obj = doc.object();
    QJsonArray users_array;

    for(int i = 0; i < a.getUsersInformation().length();i++){

        QJsonObject user_obj;
        user_obj.insert("address", a.getUser(i).getAddress());
        user_obj.insert("admin", a.getUser(i).isAdmin());
        user_obj.insert("walletKey", a.getUser(i).getPassword());
        user_obj.insert("language", a.getUser(i).getUserLanguage());

        users_array.append(user_obj);

    }
    qDebug() << users_array;

    users_obj["users"] = users_array;
    doc.setObject(users_obj);

    if(!json_file.open(QFile::WriteOnly))
    {
        throw ProgramException(FILE_WRITE_ERROR);
    }
    json_file.write(doc.toJson());
}

QVector<QString> JSON:: get_users_info(getInfo what_u_need){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    QVector <QString> valid_information;

    switch (what_u_need)
    {
    case KEY:
        for(int index = 0; index < jsonArray.size(); index++)
        {
            QJsonObject subtree = jsonArray.at(index).toObject();
            valid_information.append(subtree.value("walletKey").toString());
        }
        break;
    case ADDRESS:
        for(int index = 0; index < jsonArray.size(); index++)
        {
            QJsonObject subtree = jsonArray.at(index).toObject();
            valid_information.append(subtree.value("address").toString());
        }
        break;
    case ADMIN:
        for(int index = 0; index < jsonArray.size(); index++)
        {
            QJsonObject subtree = jsonArray.at(index).toObject();
            valid_information.append(QString::number(subtree.value("admin").toInt()));
        }
        break;
    default:
        break;
    }
    return valid_information;
}

void fileExists(const QString &file_path)
{
    // ProgramExceptions Path
    QFileInfo check_file(file_path);
    if(!check_file.exists() && !check_file.isFile())
    {
        throw ProgramException(FILE_EXIST_ERROR);
    }
}
