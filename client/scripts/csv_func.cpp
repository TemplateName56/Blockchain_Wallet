#include "csv_func.h"

CSV::CSV(QString fileName)
{
    filename = fileName;
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        throw ProgramException(FILE_READ_ERROR, filename);
    }
    int counter = 0;
    while (!file.atEnd())
    {
        QString line = file.readLine();
        lines.append(line);
        counter++;
    }
    file.close();
}

QVector<QString> CSV::getList()
{

    return this->lines;
}

QVector<QString> CSV::get_tr(int language_index){
    QVector <QString> words;
    for(int i = 0; i < lines.size(); i++){
        words.append(lines.at(i).section(',', language_index, language_index));
    }
    return words;
}

void CSV:: append_csv_request(QString link, QString message, QString amount,QString type_amount, QString reciever){

    QFile file_out(filename);
    if (!file_out.open(QFile::Append) )
    {
        throw ProgramException(FILE_READ_ERROR, filename);
    } else {
        QTextStream out(&file_out);
            out << link << "," << message << "," << amount << "," << type_amount << "," << reciever << "," << "\n";
        QString line = link + "," + message + "," + amount + "," + type_amount+"," + reciever + ",";
        lines.append(line);
        file_out.close();
    }
}

int CSV:: get_amount_row(){
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        throw ProgramException(FILE_READ_ERROR, filename);
    }
    int counter = 0;
    while (!file.atEnd())
    {
        QString line = file.readLine();
        counter++;
    }
    file.close();
    return counter;
}

QVector<QString> CSV:: find_user(QString str_user){
    QString str1;
    QVector <QString> user;
    for(int i = 0; i < lines.size(); i++){
        for(int j = 0; j < 5; j++){
            if(lines.at(i).section(',', j, j) == str_user){
                str1 = lines.at(i);
                user.append(lines.at(i));
            }
        }
    }
    return user;
}

QString CSV:: get_message_csv(int row){
    QString str;
    str = lines.at(row).section(',', 2, 2);
    return str;
}

QString CSV::  get_label_csv(int row){
    QString str;
    str = lines.at(row).section(',', 1, 1);
    return str;
}

QString CSV::  get_date_csv(int row){
    QString str;
    str = lines.at(row).section(',', 0, 0);
    return str;
}

QString CSV::  get_money_csv(int row){
    QString str;
    str = lines.at(row).section(',', 3, 3);
    return str;
}
