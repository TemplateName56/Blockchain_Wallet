#include "json_func.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

QVector<QString> getUserKey()
{
    QFileInfo file_info("users.json");
    QDir::setCurrent(file_info.path());
    QFile json_file("users.json");
    if (!json_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Not opened";
    }
    QByteArray save_file_info = json_file.readAll();
    json_file.close();
    QJsonDocument json_document(QJsonDocument::fromJson(save_file_info));
    qDebug() << json_document;
    QJsonObject temp = json_document.object();
    QJsonValue temp2 = temp.value("users");
    QJsonArray json_array = temp2.toArray();

    QVector <QString> valid_key;
    for(int index = 0; index < json_array.size(); index++)
    {
        QJsonObject subtree = json_array.at(index).toObject();
        qDebug() << subtree.value("walletKey").toString();
        valid_key.append(subtree.value("walletKey").toString());
    }
    return valid_key;
}

void writeUsers()
{

}
