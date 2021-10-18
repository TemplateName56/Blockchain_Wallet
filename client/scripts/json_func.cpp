#include "json_func.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

QVector<QString> getUsersInfo(getInfo what_u_need)
{
    QFileInfo file_info("users.json");
    QDir::setCurrent(file_info.path());
    QFile json_file("users.json");

    if (!json_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Not opened";
    }

    QJsonDocument json_document(QJsonDocument::fromJson(json_file.readAll()));
    json_file.close();
    qDebug() << json_document;

    QJsonObject temp = json_document.object();
    QJsonArray json_array = temp["users"].toArray();

    QVector <QString> valid_information;
    switch (what_u_need)
    {
    case KEY:
        for(int index = 0; index < json_array.size(); index++)
        {
            QJsonObject subtree = json_array.at(index).toObject();

            qDebug() << subtree.value("walletKey").toString();

            valid_information.append(subtree.value("walletKey").toString());
        }
        break;
    case ADDRESS:
        for(int index = 0; index < json_array.size(); index++)
        {
            QJsonObject subtree = json_array.at(index).toObject();

            qDebug() << subtree.value("address").toString();

            valid_information.append(subtree.value("address").toString());
        }
        break;
    }

    return valid_information;
}

void registerNewUsers(QString wallet_address, QString wallet_key)
{
    QFileInfo file_info("users.json");
    QDir::setCurrent(file_info.path());
    QFile json_file("users.json");

    if (!json_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Not read";
    }

    QJsonObject new_user;
    new_user["address"] = wallet_address;
    new_user["walletKey"] = wallet_key;

    QJsonDocument json_document(QJsonDocument::fromJson(json_file.readAll()));
    json_file.close();

    QJsonObject current_json = json_document.object();
    QJsonArray json_array = current_json["users"].toArray();

    json_array.push_back(new_user);
    current_json["users"] = json_array;
    if (!json_file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Not write";
    }

    json_file.write(QJsonDocument(current_json).toJson(QJsonDocument::Indented));
    json_file.close();

}
