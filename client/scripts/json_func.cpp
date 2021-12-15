#include "json_func.h"
#include "client/blockchain/blockchain.h"
//#include "client/classes/users.cpp"
//#include "client/blockchain/blockchain.cpp"


JSON::JSON(QString fileName)
{
    /*
         QString path = QDir::currentPath();
         QString str = "Blockchain_Wallet/doc/";
         QString str2 = "build-Blockchain_Wallet-Desktop_Qt_6_2_2_MinGW_64_bit-Debug";
         path.replace(path.length()-str2.length(), str2.length(), str);
         path += fileName;
         qDebug() << path;
     */
         //filename = path;
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
        //qDebug() << "\n\ndoc_constructor :" << doc;
}

//void JSON::read_all_chain(){
//    JSON file(filename);
//    bool genesis = true;
//    qDebug() << "\narray_size:" << file.new_get_array_size_blockchain();
//    for(int index = 0; index < file.new_get_array_size_blockchain(); index++)
//    {

//            if(index > 0)
//            {
//                genesis = false;
//            }
//            qDebug() << "\nreadChain:";
//            qDebug() << "Amount:" << file.new_get_amount(index);
//            qDebug() << "Reciever:" << file.new_get_reciever(index);
//            qDebug() << "Sender:" << file.new_get_sender(index);
//            qDebug() << "TimeStamp:" << file.new_get_timestamp(index);
//            addBlock(file.new_get_id(index),
//                     TransactionData(file.new_get_sender(index),
//                                     file.new_get_reciever(index),
//                                     file.new_get_amount(index),
//                                     toCoinsType(file.new_get_CoinsType(index)),
//                                     file.new_get_fee(index),
//                                     file.new_get_priority(index),
//                                     file.new_get_timestamp(index)),
//                    file.new_get_prev_hash(index),
//                    file.new_get_hash(index),
//                     genesis);


//    }
//}

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

            //qDebug() << "i: "<< i;
            jsonArray.replace(i, jsonObj3);
            //qDebug() << "=-=-=-=-Set_language-=-=-="<< jsonArray;
            //qDebug() << "address from file: "<< str;
            //qDebug() << "address from function: "<< address;
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


}

int JSON::get_array_size_users(){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    return jsonArray.size();
}

void JSON::changed_passphrase_oldkey(QString old_walletKey, QString new_walletKey){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();

    QJsonObject GBjsonObj;
    GBjsonObj = doc.object();
    algoritms use_algoritm;

    for(int i = 0; i <  jsonArray.size(); i++){
        QJsonObject subtree = jsonArray.at(i).toObject();
        QString str = subtree.value("walletKey").toString();
        QString str_old = QString::fromStdString(use_algoritm.Hash(old_walletKey.toStdString()));
        if(str == str_old){
            QJsonObject subtree = jsonArray.at(i).toObject();
            QString address = subtree.value("address").toString();
            int admin = subtree.value("admin").toInt();

            QJsonObject jsonObj3;
            jsonObj3.insert("address", address);
            jsonObj3.insert("admin", admin);
            jsonObj3.insert("walletKey", QString::fromStdString(use_algoritm.Hash(new_walletKey.toStdString())));

            jsonArray.replace(i, jsonObj3);
            //qDebug() << jsonArray;
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

void JSON::changed_passphrase_address(QString address, QString new_walletKey){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();

    QJsonObject GBjsonObj;
    GBjsonObj = doc.object();
    algoritms use_algoritm;

    for(int i = 0; i <  jsonArray.size(); i++){
        QJsonObject subtree = jsonArray.at(i).toObject();
        QString str = subtree.value("address").toString();
        //QString address = QString::fromStdString(use_algoritm.Hash(address.toStdString()));
        if(str == address){
            QJsonObject subtree = jsonArray.at(i).toObject();
            QString address_file = subtree.value("address").toString();
            int admin = subtree.value("admin").toInt();
            int language_file = subtree.value("language").toInt();

            QJsonObject jsonObj3;
            jsonObj3.insert("address", address_file);
            jsonObj3.insert("admin", admin);
            jsonObj3.insert("walletKey", QString::fromStdString(use_algoritm.Hash(new_walletKey.toStdString())));
            jsonObj3.insert("language", language_file);

            jsonArray.replace(i, jsonObj3);
            //qDebug() << jsonArray;
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

void JSON::write_all_chain(QVector<Block> chain)
{
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    QJsonObject GBjsonObj;
     GBjsonObj = doc.object();
     QJsonDocument document = doc;

     QJsonObject jsonObj1;

     QJsonArray jsonArray2;
     QJsonObject jsonObj3;
     jsonObj3.insert("Amount", chain[1].getBlockData().getAmount());
     jsonObj3.insert("Coins Type", chain[1].getBlockData().getCoinsType());
     jsonObj3.insert("Fee", chain[1].getBlockData().getFee());
     jsonObj3.insert("Priority", chain[1].getBlockData().getPriority());
     jsonObj3.insert("Reciever", chain[1].getBlockData().getReciever());
     jsonObj3.insert("Sender", chain[1].getBlockData().getSender());
     jsonObj3.insert("TimeStamp", chain[1].getBlockData().getTimeStamp());
     jsonArray2.append(jsonObj3);

     QJsonArray balances;
     QJsonObject balance;
     for(int j = 0; j < chain[1].users_balance.length(); j++){
         balance.insert("Address", chain[1].users_balance[j].getAddress());
         balance.insert("Balance BWC", chain[1].users_balance[j].getBalance(BWC));
         balance.insert("Balance BWC-N", chain[1].users_balance[j].getBalance(BWC_N));
         balance.insert("Balance BWC-Q", chain[1].users_balance[j].getBalance(BWC_Q));
         balances.append(balance);
     }

     jsonObj1.insert("Balances", balances);

     jsonObj1.insert("Id", chain[1].getIndex());
     jsonObj1.insert("Hash", chain[1].getBlockHash());
     jsonObj1.insert("Previous Hash", chain[1].getPrevBlockHash());
//    chain.getLastBlock().getIndex();
     jsonObj1.insert("Blockchain",jsonArray2);
    //qDebug() << jsonObj1;
//    qDebug() << "\nBlock Data:";
//    qDebug() << "Amount:" << chain[0].getBlockData().getAmount();
//    qDebug() << "Reciever:" << chain[0].getBlockData().getReciever();
//    qDebug() << "Sender:" << chain[0].getBlockData().getSender();
//    qDebug() << "TimeStamp:" << chain[0].getBlockData().getTimeStamp();

//    qDebug() << "\nBlock Data:";
//    qDebug() << "Amount:" << chain[1].getBlockData().getAmount();
//    qDebug() << "Reciever:" << chain[1].getBlockData().getReciever();
//    qDebug() << "Sender:" << chain[1].getBlockData().getSender();
//    qDebug() << "TimeStamp:" << chain[1].getBlockData().getTimeStamp();

     jsonArray.append(jsonObj1);
     //qDebug() << "\ndoc_before_set :" << doc;
     GBjsonObj["Blockchain"] = jsonArray;
     document.setObject(GBjsonObj);
     //qDebug() << "\ndoc_after_set :" << doc;
     if(!json_file.open(QFile::WriteOnly))
     {
         throw ProgramException(FILE_WRITE_ERROR);
     }
     json_file.write(document.toJson());
}


void JSON::write_all_chain(Block chain){
    chain.getBlockData().getAmount();

    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    QJsonObject GBjsonObj;
     GBjsonObj = doc.object();
     QJsonDocument document = doc;

     QJsonObject jsonObj1;

     //QJsonArray jsonArray2;
     QJsonObject jsonObj3;
     jsonObj3.insert("Amount", chain.getBlockData().getAmount());
     jsonObj3.insert("Coins Type", chain.getBlockData().getCoinsType());
     jsonObj3.insert("Fee", chain.getBlockData().getFee());
     jsonObj3.insert("Priority", chain.getBlockData().getPriority());
     jsonObj3.insert("Reciever", chain.getBlockData().getReciever());
     jsonObj3.insert("Sender", chain.getBlockData().getSender());
     jsonObj3.insert("TimeStamp", chain.getBlockData().getTimeStamp());
     //jsonArray2.append(jsonObj3);

     QJsonArray balances;
     QJsonObject balance;
     for(int j = 0; j < chain.users_balance.length(); j++){
         balance.insert("Address", chain.users_balance[j].getAddress());
         balance.insert("Balance BWC", chain.users_balance[j].getBalance(BWC));
         balance.insert("Balance BWC-N", chain.users_balance[j].getBalance(BWC_N));
         balance.insert("Balance BWC-Q", chain.users_balance[j].getBalance(BWC_Q));
         balances.append(balance);
     }

     jsonObj1.insert("Balances", balances);

     jsonObj1.insert("Id", chain.getIndex());
     jsonObj1.insert("Hash", chain.getBlockHash());
     jsonObj1.insert("Previous Hash", chain.getPrevBlockHash());
//    chain.getLastBlock().getIndex();
     jsonObj1.insert("Block Data",jsonObj3);
    //qDebug() << jsonObj1;
    //qDebug() << "\nBlock Data:";
    //qDebug() << "Amount:" << chain.getBlockData().getAmount();
    //qDebug() << "Reciever:" << chain.getBlockData().getReciever();
    //qDebug() << "Sender:" << chain.getBlockData().getSender();
    //qDebug() << "TimeStamp:" << chain.getBlockData().getTimeStamp();


     jsonArray.append(jsonObj1);
     //qDebug() << "\ndoc_before_set :" << doc;
     GBjsonObj["Blockchain"] = jsonArray;
     document.setObject(GBjsonObj);
     //qDebug() << "\ndoc_after_set :" << doc;
     if(!json_file.open(QFile::WriteOnly))
     {
         throw ProgramException(FILE_WRITE_ERROR);
     }
     json_file.write(document.toJson());
}

void JSON:: write_chain_json(){
    QJsonObject jsonObj3;
    //jsonObj3.insert("Sender", chain[1].getBlockData().getSender());
}



QString JSON:: new_get_hash(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    QJsonValue value = jsonArray.at(number_block);
    QString address = value["Hash"].toString();;
    return address;
}

QString JSON:: new_get_prev_hash(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    QJsonValue value = jsonArray.at(number_block);
    QString Prev_hash = value["Previous Hash"].toString();;
    return Prev_hash;
}

int JSON:: new_get_id(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    QJsonValue value = jsonArray.at(number_block);
    int id = value["Id"].toInt();
    return id;
}

QString JSON:: new_get_address(int number_block, int num_balance){
    QJsonObject root = doc.object();
    QJsonArray tlmtArray = root.value("Blockchain").toArray();
    QJsonObject obj = tlmtArray[number_block-1].toObject();
    QJsonArray gps_array = obj.value("Balances").toArray();
    QJsonObject gps_obj = gps_array[num_balance].toObject();
    QJsonValue value2 = gps_array.at(num_balance);
    QString adress = value2["Address"].toString();
    return adress ;
}

double JSON:: new_get_BWC_balance(int number_block, int num_balance){
    QJsonObject root = doc.object();
    QJsonArray tlmtArray = root.value("Blockchain").toArray();
    QJsonObject obj = tlmtArray[number_block-1].toObject();
    QJsonArray gps_array = obj.value("Balances").toArray();
    QJsonObject gps_obj = gps_array[num_balance].toObject();
    QJsonValue value2 = gps_array.at(num_balance);
    double BWC_balance = value2["Balance BWC"].toDouble();
    return BWC_balance;
}

double JSON:: new_get_BWC_N_balance(int number_block, int num_balance){
    QJsonObject root = doc.object();
    QJsonArray tlmtArray = root.value("Blockchain").toArray();
    QJsonObject obj = tlmtArray[number_block-1].toObject();
    QJsonArray gps_array = obj.value("Balances").toArray();
    QJsonObject gps_obj = gps_array[num_balance].toObject();
    QJsonValue value2 = gps_array.at(num_balance);
    double BWC_N_balance = value2["Balance BWC-N"].toDouble();
    return BWC_N_balance;
}

double JSON:: new_get_BWC_Q_balance(int number_block, int num_balance){
    QJsonObject root = doc.object();
    QJsonArray tlmtArray = root.value("Blockchain").toArray();
    QJsonObject obj = tlmtArray[number_block-1].toObject();
    QJsonArray gps_array = obj.value("Balances").toArray();
    QJsonObject gps_obj = gps_array[num_balance].toObject();
    QJsonValue value2 = gps_array.at(num_balance);
    double BWC_Q_balance = value2["Balance BWC-Q"].toDouble();
    return BWC_Q_balance;
}

double JSON:: new_get_amount(int number_block){
    QJsonObject root = doc.object();
    QJsonArray tlmtArray = root.value("Blockchain").toArray();
    QJsonObject obj = tlmtArray[number_block].toObject();

    QJsonValue value = tlmtArray.at(number_block);
    QJsonObject obj1 = value["Block Data"].toObject();
    double amount = obj1["Amount"].toDouble();

//    QJsonArray gps_array = obj.value("Block Data").toArray();
//    QJsonObject gps_obj = gps_array[num_data].toObject();
//    QJsonValue value2 = gps_array.at(num_data);
//    double amount = value2["Amount"].toDouble();
    return amount;
}

double JSON:: new_get_fee(int number_block){
    QJsonObject root = doc.object();
    QJsonArray tlmtArray = root.value("Blockchain").toArray();
    QJsonObject obj = tlmtArray[number_block].toObject();

    QJsonValue value = tlmtArray.at(number_block);
    QJsonObject obj1 = value["Block Data"].toObject();
    double fee = obj1["Fee"].toDouble();

//    QJsonArray gps_array = obj.value("Block Data").toArray();
//    QJsonObject gps_obj = gps_array[num_data].toObject();
//    QJsonValue value2 = gps_array.at(num_data);
//    double fee = value2["Fee"].toDouble();
    return fee;
}

int JSON:: new_get_priority(int number_block){
    QJsonObject root = doc.object();
    QJsonArray tlmtArray = root.value("Blockchain").toArray();
    QJsonObject obj = tlmtArray[number_block].toObject();
   //QJsonArray gps_array = obj.value("Block Data").toArray();

    QJsonValue value = tlmtArray.at(number_block);
    QJsonObject obj1 = value["Block Data"].toObject();
    int priority = obj1["Priority"].toInt();

//    QJsonObject gps_obj = gps_array[num_data].toObject();
//    QJsonValue value2 = gps_array.at(num_data);
//    int priority = value2["Priority"].toInt();
    return priority;
}

QString JSON:: new_get_reciever(int number_block){
    QJsonObject root = doc.object();
    QJsonArray tlmtArray = root.value("Blockchain").toArray();
    QJsonObject obj = tlmtArray[number_block].toObject();

    QJsonValue value = tlmtArray.at(number_block);
    QJsonObject obj1 = value["Block Data"].toObject();
    QString reciever = obj1["Reciever"].toString();

//    QJsonArray gps_array = obj.value("Block Data").toArray();
//    QJsonObject gps_obj = gps_array[num_data].toObject();
//    QJsonValue value2 = gps_array.at(num_data);
//    QString reciever = value2["Reciever"].toString();
    return reciever;
}

QString JSON:: new_get_sender(int number_block){
    QJsonObject root = doc.object();
    QJsonArray tlmtArray = root.value("Blockchain").toArray();
    QJsonObject obj = tlmtArray[number_block].toObject();

    QJsonValue value = tlmtArray.at(number_block);
    QJsonObject obj1 = value["Block Data"].toObject();
    QString sender = obj1["Sender"].toString();

//    QJsonArray gps_array = obj.value("Block Data").toArray();
//    QJsonObject gps_obj = gps_array[num_data].toObject();
//    QJsonValue value2 = gps_array.at(num_data);
//    QString sender = value2["Sender"].toString();
    return sender;
}

QString JSON:: new_get_timestamp(int number_block){
    QJsonObject root = doc.object();
    QJsonArray tlmtArray = root.value("Blockchain").toArray();
    QJsonObject obj = tlmtArray[number_block].toObject();

    QJsonValue value = tlmtArray.at(number_block);
    QJsonObject obj1 = value["Block Data"].toObject();
    QString timestamp = obj1["TimeStamp"].toString();

//    QJsonArray gps_array = obj.value("Block Data").toArray();
//    QJsonObject gps_obj = gps_array[num_data].toObject();
//    QJsonValue value2 = gps_array.at(num_data);
//    QString timestamp = value2["TimeStamp"].toString();
    return timestamp;
}


int JSON:: new_get_CoinsType(int number_block){
    QJsonObject root = doc.object();
    QJsonArray tlmtArray = root.value("Blockchain").toArray();
    QJsonObject obj = tlmtArray[number_block].toObject();

    QJsonValue value = tlmtArray.at(number_block);
    QJsonObject obj1 = value["Block Data"].toObject();
    int coins_type = obj1["Coins Type"].toInt();

//    QJsonArray gps_array = obj.value("Block Data").toArray();
//    QJsonObject gps_obj = gps_array[num_data].toObject();
//    QJsonValue value2 = gps_array.at(num_data);
//    int coins_type = value2["Coins Type"].toInt();
    return coins_type ;
}


void JSON:: new_print(){
    QJsonObject root = doc.object();
    //QJsonArray tlmtArray = root.value("A").toArray();
    QJsonArray tlmtArray = root.value("Blockchain").toArray();

    for(int i = 0; i < tlmtArray.size(); ++i)
    {
        QJsonObject obj = tlmtArray[i].toObject();
        QJsonArray gps_array = obj.value("Block Data").toArray();
        QJsonArray gps_array2 = obj.value("Balances").toArray();

        QString Hash = obj.value("Hash").toString();
        int Id = obj.value("Id").toInt();
        QString prev_hash =obj.value("Previous Hash").toString();
//        qDebug() <<"Hash:" << Hash  ;
//        qDebug() <<"Previous Hash:" << prev_hash  ;
//        qDebug() <<"Id:" << Id  ;
//         qDebug() <<"Blockchain array size:" << tlmtArray.size()  ;
//         qDebug() <<"Balances array size:" << gps_array2.size()  ;
//         qDebug() <<"Block Data array size:" << gps_array.size()  ;

//        std::cout << "----\n";
        for(int j = 0; j < gps_array.size(); ++j)
        {

            QJsonObject gps_obj = gps_array[j].toObject();
            QJsonValue value2 = gps_array.at(j);
            //QString address_recipient = value2["address_recipient"].toString();
//            qDebug() <<"Amount:" << value2["Amount"].toDouble();
//            qDebug() <<"Coins Type:"  << value2["Coins Type"].toInt();
//            qDebug() <<"Fee:"  << value2["Fee"].toDouble();
//            qDebug() <<"Priority:"  << value2["Priority"].toInt();
//            qDebug() <<"Reciever:"  << value2["Reciever"].toString();
//            qDebug() <<"Sender:"  << value2["Sender"].toString();
//            qDebug() <<"TimeStamp:"  << value2["TimeStamp"].toString();
//            std::cout << "\n";
        }
//        std::cout << "--\n";
        for(int j = 0; j < gps_array2.size(); ++j)
        {

            QJsonObject gps_obj = gps_array2[j].toObject();
            QJsonValue value2 = gps_array2.at(j);
            //QString address_recipient = value2["address_recipient"].toString();
//            qDebug() <<"Address:" << value2["Address"].toString();
//            qDebug() <<"Balance BWC:"  << value2["Balance BWC"].toDouble();
//            qDebug() <<"Balance BWC-N:"  << value2["Balance BWC-N"].toDouble();
//            qDebug() <<"Balance BWC-Q:"  << value2["Balance BWC-Q"].toDouble();

//            std::cout << "\n";
        }
//        std::cout << "-------------------------------------------------------------\n\n";
    }
}

int JSON:: new_get_array_size_blockchain(){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    return jsonArray.size();
}

int JSON:: new_get_array_size_balances(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    QJsonObject obj = jsonArray[number_block-1].toObject();
    QJsonArray gps_array = obj.value("Balances").toArray();
    return gps_array.size();
}

int JSON:: new_get_array_size_block_data(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    QJsonObject obj = jsonArray[number_block-1].toObject();
    QJsonArray gps_array = obj.value("Block Data").toArray();
    return gps_array.size();
}

void JSON:: new_append_balances(int num_user){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    QJsonValue value = jsonArray.at(num_user-1);
    QJsonArray jsonArray2 = value["Balances"].toArray();

    QJsonObject GBjsonObj;
    GBjsonObj = doc.object();
    QJsonObject jsonObj3;
    jsonObj3.insert("Address", "BW0756471");
    jsonObj3.insert("Balance BWC", "0");
    jsonObj3.insert("Balance BWC-N", "100");
    jsonObj3.insert("Balance BWC-Q", "0");
    jsonArray2.append(jsonObj3);
    QJsonValue value_array = jsonArray2;

    QJsonObject o_arr_frist = jsonArray[num_user-1].toObject();
    o_arr_frist.insert("Balances", value_array);
    jsonArray[num_user-1] = o_arr_frist;
    json.insert("Blockchain", jsonArray);
    GBjsonObj = json;
    doc.setObject(GBjsonObj);
    if(!json_file.open(QFile::WriteOnly))
    {
        throw ProgramException(FILE_WRITE_ERROR);
    }
    json_file.write(doc.toJson());
}

void JSON::  new_write_block_data(int num_user){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    QJsonValue value = jsonArray.at(num_user-1);
    QJsonArray jsonArray2 = value["Block Data"].toArray();
    QJsonObject GBjsonObj;
    GBjsonObj = doc.object();
    QJsonObject jsonObj3;
    jsonObj3.insert("Amount", "BW0756471");
    jsonObj3.insert("Coins Type", "0");
    jsonObj3.insert("Fee", "100");
    jsonObj3.insert("Priority", "0");
    jsonObj3.insert("Reciever", "0");
    jsonObj3.insert("Sender", "100");
    jsonObj3.insert("TimeStamp", "0");
    jsonArray2.append(jsonObj3);
    //jsonArray2.insert(0,jsonObj3);

    QJsonValue value_array = jsonArray2;

    QJsonObject o_arr_frist = jsonArray[num_user-1].toObject();
    o_arr_frist.insert("Block Data", value_array);
    jsonArray[num_user-1] = o_arr_frist;
    json.insert("Blockchain", jsonArray);
    GBjsonObj = json;
    doc.setObject(GBjsonObj);
    json_file.open(QFile::WriteOnly);
    json_file.write(doc.toJson());
}

void JSON:: new_append_hash2_id(){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();

    QJsonObject GBjsonObj;
    GBjsonObj = doc.object();

    QJsonObject jsonObj3;
    jsonObj3.insert("Hash", "dg36456");
    jsonObj3.insert("Id", "2");
    jsonObj3.insert("Previous Hash", "0");

    jsonArray.append(jsonObj3);
    GBjsonObj["Blockchain"] = jsonArray;
    doc.setObject(GBjsonObj);

    if(!json_file.open(QFile::WriteOnly))
    {
        throw ProgramException(FILE_WRITE_ERROR);
    }
    json_file.write(doc.toJson());
}

void JSON::  new_append_hash2_id(QString hash, int id, QString prev_hash){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();

    QJsonObject GBjsonObj;
    GBjsonObj = doc.object();

    QJsonObject jsonObj3;
    jsonObj3.insert("Hash", hash);
    jsonObj3.insert("Id", id);
    jsonObj3.insert("Previous Hash", prev_hash);

    jsonArray.append(jsonObj3);
    GBjsonObj["Blockchain"] = jsonArray;
    doc.setObject(GBjsonObj);

    if(!json_file.open(QFile::WriteOnly))
    {
        throw ProgramException(FILE_WRITE_ERROR);
    }
    json_file.write(doc.toJson());
}

void JSON:: new_write_block_data(int num_user, QString sender, QString reciever,
                          int amount, int coins_type, double fee,
                          int priority, QString time_stamp){

    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    QJsonValue value = jsonArray.at(num_user-1);
    QJsonArray jsonArray2 = value["Block Data"].toArray();
    QJsonObject GBjsonObj;
    GBjsonObj = doc.object();
    QJsonObject jsonObj3;
    jsonObj3.insert("Amount", amount);
    jsonObj3.insert("Coins Type", coins_type);
    jsonObj3.insert("Fee", fee);
    jsonObj3.insert("Priority", priority);
    jsonObj3.insert("Reciever", reciever);
    jsonObj3.insert("Sender", sender);
    jsonObj3.insert("TimeStamp", time_stamp);
    jsonArray2.append(jsonObj3);
    //jsonArray2.insert(0,jsonObj3);

    QJsonValue value_array = jsonArray2;

    QJsonObject o_arr_frist = jsonArray[num_user-1].toObject();
    o_arr_frist.insert("Block Data", value_array);
    jsonArray[num_user-1] = o_arr_frist;
    json.insert("Blockchain", jsonArray);
    GBjsonObj = json;
    doc.setObject(GBjsonObj);
    if(!json_file.open(QFile::WriteOnly))
    {
        throw ProgramException(FILE_WRITE_ERROR);
    }
    json_file.write(doc.toJson());
}

void JSON:: new_append_balances(int num_user, QString address, double balance_bwc,
                         double balance_bwc_n, double balance_bwc_q){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["Blockchain"].toArray();
    QJsonValue value = jsonArray.at(num_user-1);
    QJsonArray jsonArray2 = value["Balances"].toArray();

    QJsonObject GBjsonObj;
    GBjsonObj = doc.object();
    QJsonObject jsonObj3;
    jsonObj3.insert("Address", address);
    jsonObj3.insert("Balance BWC", balance_bwc);
    jsonObj3.insert("Balance BWC-N", balance_bwc_n);
    jsonObj3.insert("Balance BWC-Q", balance_bwc_q);
    jsonArray2.append(jsonObj3);
    QJsonValue value_array = jsonArray2;

    QJsonObject o_arr_frist = jsonArray[num_user-1].toObject();
    o_arr_frist.insert("Balances", value_array);
    jsonArray[num_user-1] = o_arr_frist;
    json.insert("Blockchain", jsonArray);
    GBjsonObj = json;
    doc.setObject(GBjsonObj);
    if(!json_file.open(QFile::WriteOnly))
    {
        throw ProgramException(FILE_WRITE_ERROR);
    }
    json_file.write(doc.toJson());

}

void JSON:: registerNewUser(QString address, QString walletKey){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();

    QJsonObject GBjsonObj;
    GBjsonObj = doc.object();

    algoritms use_algoritm;

    QJsonObject jsonObj3;
    jsonObj3.insert("address", address);
    jsonObj3.insert("walletKey", QString::fromStdString(use_algoritm.Hash(walletKey.toStdString())));
    jsonObj3.insert("admin", 0);
    jsonObj3.insert("language", 1);

    jsonArray.append(jsonObj3);

    GBjsonObj["users"] = jsonArray;
    doc.setObject(GBjsonObj);

    if(!json_file.open(QFile::WriteOnly))
    {
        throw ProgramException(FILE_WRITE_ERROR);
    }
    json_file.write(doc.toJson());

}

QString JSON::get_address_user(int num){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    QString address_file;
    QJsonObject subtree = jsonArray.at(num).toObject();
    address_file = subtree.value("address").toString();
    return address_file;


}

QString JSON::get_wallet_key_user(int num){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    QString wallet_key;
    QJsonObject subtree = jsonArray.at(num).toObject();
     wallet_key = subtree.value("walletKey").toString();
    return wallet_key;


}

bool JSON::get_admin_user(int num){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    bool admin;
    QJsonObject subtree = jsonArray.at(num).toObject();
    admin = subtree.value("admin").toInt();
    return admin;
}

int JSON::get_language_user(int num){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    int language;
    QJsonObject subtree = jsonArray.at(num).toObject();
    language = subtree.value("language").toInt();
    return language;
}
/*
void JSON::read_users_file(Users &a) //Идеальный метод класса для Табунщик но я хз куда его вставлять в коде
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
    a.users_infomation.push_back(User(address_file,
                                    wallet_key,
                                    tolanguages(language),
                                    admin));
    }
}
*/
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

QVector<QString> getUsersInfo(getInfo what_u_need)
{
    try {
        fileExists("users.json");
    }  catch (ProgramException &error) {
        error.getError();
    }
    QFileInfo file_info("users.json");
    QDir::setCurrent(file_info.path());
    QFile json_file("users.json");

    if (!json_file.open(QIODevice::ReadOnly))
    {
        throw ProgramException(FILE_READ_ERROR);
    }

    QJsonDocument json_document(QJsonDocument::fromJson(json_file.readAll()));
    json_file.close();

    QJsonObject temp = json_document.object();
    QJsonArray json_array = temp["users"].toArray();

    QVector <QString> valid_information;
    switch (what_u_need)
    {
    case KEY:
        for(int index = 0; index < json_array.size(); index++)
        {
            QJsonObject subtree = json_array.at(index).toObject();
            valid_information.append(subtree.value("walletKey").toString());
        }
        break;
    case ADDRESS:
        for(int index = 0; index < json_array.size(); index++)
        {
            QJsonObject subtree = json_array.at(index).toObject();
            valid_information.append(subtree.value("address").toString());
        }
        break;
    case ADMIN:
        for(int index = 0; index < json_array.size(); index++)
        {
            QJsonObject subtree = json_array.at(index).toObject();
            valid_information.append(QString::number(subtree.value("admin").toInt()));
        }
        break;
    default:
        break;
    }

    return valid_information;
}

//void registerNewUsers(QString wallet_address, QString wallet_key)
//{
//    try {
//        fileExists("users.json");
//    }  catch (ProgramException &error) {
//        error.getError();
//    }

//    algoritms use_algoritm;

//    QFileInfo file_info("users.json");
//    QDir::setCurrent(file_info.path());
//    QFile json_file("users.json");

//    if (!json_file.open(QIODevice::ReadOnly))
//    {
//        throw ProgramException(FILE_READ_ERROR);
//    }

//    QJsonObject new_user;

//    new_user["address"] = wallet_address;
//    new_user["walletKey"] = QString::fromStdString(use_algoritm.Hash(wallet_key.toStdString()));
//    new_user["admin"] = 0;

//    QJsonDocument json_document(QJsonDocument::fromJson(json_file.readAll()));
//    json_file.close();

//    QJsonObject current_json = json_document.object();
//    QJsonArray json_array = current_json["users"].toArray();

//    json_array.push_back(new_user);
//    current_json["users"] = json_array;
//    if (!json_file.open(QIODevice::WriteOnly))
//    {
//        throw ProgramException(FILE_WRITE_ERROR);
//    }

//    json_file.write(QJsonDocument(current_json).toJson(QJsonDocument::Indented));
//    json_file.close();
//}
