#include "json_func.h"


JSON::JSON(QString fileName)
{
    filename = fileName;
    QString val2;
    QFile json_file(filename);
    json_file.open(QIODevice::ReadOnly | QIODevice::Text);
    val2 = json_file.readAll();
    json_file.close();

    doc = QJsonDocument::fromJson(val2.toUtf8());
     //qDebug() << "\n\ndoc_constructor :" << doc;
}

void JSON:: saveJson_append(int index){

    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["blockhain"].toArray();
    QJsonObject GBjsonObj;
     GBjsonObj = doc.object();

     QJsonObject jsonObj3;
     jsonObj3.insert("number", index);
     jsonObj3.insert("hash_previous", "zxc342");
     jsonObj3.insert("hash", "nvbn5435");
     jsonObj3.insert("currency", "btc");
     jsonObj3.insert("time_of_creation", 2214);

     QJsonObject jsonObj4;
     jsonObj4.insert("address_sender", "lkj567");
     jsonObj4.insert("address_recipient", "cb4353");
     jsonObj4.insert("money", 0.052);

     QJsonObject jsonObj1;
     jsonObj1["header"] = jsonObj3;
     jsonObj1["block"] = jsonObj4;

    jsonArray.append(jsonObj1);
    //qDebug() << "\ndoc_before_set :" << doc;
    GBjsonObj["blockhain"] = jsonArray;
    doc.setObject(GBjsonObj);
    //qDebug() << "\ndoc_after_set :" << doc;
    json_file.open(QFile::WriteOnly);
    json_file.write(doc.toJson());
}

void JSON:: saveJson_append_2(int index, QString hash_prev, QString hash, QString btc, int time, QString adress_s, QString adress_r, double money){

    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["blockhain"].toArray();
    QJsonObject GBjsonObj;
     GBjsonObj = doc.object();

     QJsonObject jsonObj3;
     jsonObj3.insert("number", index);
     jsonObj3.insert("hash_previous", hash_prev);
     jsonObj3.insert("hash", hash);
     jsonObj3.insert("currency", btc);
     jsonObj3.insert("time_of_creation", time);

     QJsonObject jsonObj4;
     jsonObj4.insert("address_sender", adress_s);
     jsonObj4.insert("address_recipient", adress_r);
     jsonObj4.insert("money", money);

     QJsonObject jsonObj1;
     jsonObj1["header"] = jsonObj3;
     jsonObj1["block"] = jsonObj4;

    jsonArray.append(jsonObj1);
    //qDebug() << "\ndoc_before_set :" << doc;
    GBjsonObj["blockhain"] = jsonArray;
    doc.setObject(GBjsonObj);
    //qDebug() << "\ndoc_after_set :" << doc;
    json_file.open(QFile::WriteOnly);
    json_file.write(doc.toJson());
}

void JSON:: append_users(){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();

    QJsonObject GBjsonObj;
    GBjsonObj = doc.object();

    QJsonObject jsonObj3;
    jsonObj3.insert("address", "BW0000000000000000003");
    jsonObj3.insert("walletKey", "Admin");

    jsonArray.append(jsonObj3);
    GBjsonObj["users"] = jsonArray;
    doc.setObject(GBjsonObj);

    json_file.open(QFile::WriteOnly);
    json_file.write(doc.toJson());
}

void JSON:: append_users_transactions(){
        int num_user = 1;
        //int num_tr = 1;
        QFile json_file(filename);
        QJsonObject json = doc.object();
        QJsonArray jsonArray = json["users"].toArray();
        QJsonValue value = jsonArray.at(num_user-1);
        QJsonArray jsonArray2 = value["transactions"].toArray();

        QJsonObject GBjsonObj;
        GBjsonObj = doc.object();

        qDebug() << "\njsonArray2 Before: "<< jsonArray2;

        QJsonObject jsonObj3;
        jsonObj3.insert("address_recipient", "BW0000000000000000001");
        jsonObj3.insert("address_sender", "lkj567");
        jsonArray2.append(jsonObj3);
        //jsonArray = jsonArray2;
        QJsonObject GBjsonObj2;
        GBjsonObj2["transactions"] = jsonArray2;

         qDebug() << "\njsonArray2 After: "<< jsonArray2;
         GBjsonObj["users"] = GBjsonObj2;
         qDebug() << "\nGBjsonObj2: "<< GBjsonObj;
         doc.setObject(GBjsonObj);

         json_file.open(QFile::WriteOnly);
         json_file.write(doc.toJson());
}

void JSON:: read_users_transactions(){
    int num_user = 1;
    int num_tr = 1;
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    QJsonValue value = jsonArray.at(num_user-1);
    QJsonArray jsonArray2 = value["transactions"].toArray();
    QJsonValue value2 = jsonArray2.at(num_tr);
    QString address_recipient = value2["address_recipient"].toString();
    double fee = value2["fee"].toDouble();

    qDebug() << address_recipient << fee;
}

void JSON:: append_users_2(QString address, QString walletKey){
    QFile json_file(filename);
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();

    QJsonObject GBjsonObj;
    GBjsonObj = doc.object();

    QJsonObject jsonObj3;
    jsonObj3.insert("address", address);
    jsonObj3.insert("walletKey", walletKey);

    jsonArray.append(jsonObj3);

    GBjsonObj["users"] = jsonArray;
    doc.setObject(GBjsonObj);

    json_file.open(QFile::WriteOnly);
    json_file.write(doc.toJson());

}

QString JSON :: get_hash(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["blockhain"].toArray();
    QJsonValue value = jsonArray.at(number_block-1);
    QJsonObject obj1 = value["header"].toObject();
    QString hash = obj1["hash"].toString();
    return hash;
}

QString JSON :: get_hash_previous(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["blockhain"].toArray();
    QJsonValue value = jsonArray.at(number_block-1);
    QJsonObject obj1 = value["header"].toObject();
    QString hash_previous = obj1["hash_previous"].toString();
    return hash_previous;
}

int JSON :: get_number(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["blockhain"].toArray();
    QJsonValue value = jsonArray.at(number_block-1);
    QJsonObject obj1 = value["header"].toObject();
    int number = obj1["number"].toInt();
    return number;
}

QString JSON :: get_currency(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["blockhain"].toArray();
    QJsonValue value = jsonArray.at(number_block-1);
    QJsonObject obj1 = value["header"].toObject();
    QString currency = obj1["currency"].toString();
    return currency;
}

int JSON :: get_time_of_creation(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["blockhain"].toArray();
    QJsonValue value = jsonArray.at(number_block-1);
    QJsonObject obj1 = value["header"].toObject();
    int time_of_creation = obj1["time_of_creation"].toInt();
    return time_of_creation;
}

QString JSON :: get_address_recipient(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["blockhain"].toArray();
    QJsonValue value = jsonArray.at(number_block-1);
    QJsonObject obj1 = value["block"].toObject();
    QString address_recipient = obj1["address_recipient"].toString();
    return address_recipient;
}

QString JSON :: get_address_sender(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["blockhain"].toArray();
    QJsonValue value = jsonArray.at(number_block-1);
    QJsonObject obj1 = value["block"].toObject();
    QString address_sender = obj1["address_sender"].toString();
    return address_sender;
}

double JSON :: get_money(int number_block){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["blockhain"].toArray();
    QJsonValue value = jsonArray.at(number_block-1);
    QJsonObject obj1 = value["block"].toObject();
    double money = obj1["money"].toDouble();
    return money;
}

int JSON :: get_array_size(){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["blockhain"].toArray();
    return jsonArray.size();
}

int JSON :: get_array_size_users(){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    return jsonArray.size();
}

QString JSON :: get_address_users(int num){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    QJsonValue value = jsonArray.at(num-1);
    QString address = value["address"].toString();;
    return address;
}

QString JSON ::  get_walletKey_users(int num){
    QJsonObject json = doc.object();
    QJsonArray jsonArray = json["users"].toArray();
    QJsonValue value = jsonArray.at(num-1);
    QString walletKey = value["walletKey"].toString();;
    return walletKey;
}





void fileExists(const QString &file_path)
{
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
    default:
        break;
    }

    return valid_information;
}

void registerNewUsers(QString wallet_address, QString wallet_key)
{
    try {
        fileExists("users.json");
    }  catch (ProgramException &error) {
        error.getError();
    }

    algoritms use_algoritm;

    QFileInfo file_info("users.json");
    QDir::setCurrent(file_info.path());
    QFile json_file("users.json");

    if (!json_file.open(QIODevice::ReadOnly))
    {
        throw ProgramException(FILE_READ_ERROR);
    }

    QJsonObject new_user;

    new_user["address"] = wallet_address;
    new_user["walletKey"] = QString::fromStdString(use_algoritm.Hash(wallet_key.toStdString()));

    QJsonDocument json_document(QJsonDocument::fromJson(json_file.readAll()));
    json_file.close();

    QJsonObject current_json = json_document.object();
    QJsonArray json_array = current_json["users"].toArray();

    json_array.push_back(new_user);
    current_json["users"] = json_array;
    if (!json_file.open(QIODevice::WriteOnly))
    {
        throw ProgramException(FILE_WRITE_ERROR);
    }

    json_file.write(QJsonDocument(current_json).toJson(QJsonDocument::Indented));
    json_file.close();
}
