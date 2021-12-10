#include "csv_func.h"

CSV::CSV(QString fileName)
{
    filename = fileName;
    QFile file(filename);
     file.open(QFile::ReadOnly | QFile::Text);
    //QTextStream in(&file);
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

QString CSV::get_tr(int row, int language){
    QString str;
    //str = line.section(';', 2, 2);
    str = lines.at(row).section(';', language, language);
    return str;
}

QString CSV::get_tr(int row, languages_csv language){
    QString str;
    //str = line.section(';', 2, 2);
    str = lines.at(row).section(';', language, language);
    return str;
}

QString CSV::get_tr(QString word, int language){
    QString str;
    for(int i = 0; i < lines.size(); i++){
        if(lines.at(i).section(';', 0, 0) == word){
            str = lines.at(i).section(';', language, language);
        }
    }
    return str;
}

QVector<QString> CSV::get_tr(languages_csv language){
    QVector <QString> words;
    qDebug() << lines.size();
    for(int i = 0; i < lines.size(); i++){
        words.append(lines.at(i).section(';', language, language));
    }
    return words;
}


void CSV:: append_csv_request(QString date, QString message, QString label, double amount){

    QFile file_out(filename);
    if ( !file_out.open(QFile::Append) ) {
        cout << "File not exists\n";
    } else {
         cout << "File exists\n";
        QTextStream out(&file_out);
        for(int i = 0; i < 1; i++){
            out << date << ";" << message << ";" << label << ";" << amount << ";" << "\n";
        }
        QString line = date + ";" + message + ";" + label + ";" + QString::number(amount)+";";
        lines.append(line);
        file_out.close();
    }
}

int CSV:: get_amount_row(){
    QFile file(filename);
     file.open(QFile::ReadOnly | QFile::Text);
    //QTextStream in(&file);
    int counter = 0;
    while (!file.atEnd())
    {
        QString line = file.readLine();
        counter++;
        // qDebug() << line << counter;
    }
    file.close();
    return counter;
}

QVector<QString> CSV:: find_user(QString str_user){
    //QString str1;
    QVector <QString> user;
    qDebug() << lines.size();
    for(int i = 0; i < lines.size(); i++){
        for(int j = 0; j < 4; j++){
            if(lines.at(i).section(';', j, j) == str_user){
                //str1 = lines.at(i);
                user.append(lines.at(i));
                //qDebug() << str1;
            }
        }
    }

    return user;
}

//QString CSV:: get_message_csv(int row){
//    QFile file(filename);
//    file.open(QFile::ReadOnly | QFile::Text);
//    QString str;
//    QString line;
//    for(int i = 0; i < row; i++){
//        line = file.readLine();
//        str = line.section(';', 2, 2);
//    }
//    file.close();
//    return str;
//}

QString CSV:: get_message_csv(int row){
    QString str;
    //str = line.section(';', 2, 2);
    str = lines.at(row).section(';', 2, 2);
    return str;
}

//QString CSV::  get_label_csv(int row){
//    QFile file(filename);
//    file.open(QFile::ReadOnly | QFile::Text);
//    QString str;
//    QString line;
//    for(int i = 0; i < row; i++){
//        line = file.readLine();
//        str = line.section(';', 1, 1);
//    }
//    file.close();
//    return str;
//}

QString CSV::  get_label_csv(int row){
    QString str;
    str = lines.at(row).section(';', 1, 1);
    return str;
}

//QString CSV::  get_date_csv(int row){
//    QFile file(filename);
//    file.open(QFile::ReadOnly | QFile::Text);
//    QString str;
//    QString line;
//    for(int i = 0; i < row; i++){
//        line = file.readLine();
//        str = line.section(';', 0, 0);
//    }
//    file.close();
//    return str;
//}

QString CSV::  get_date_csv(int row){
    QString str;
    str = lines.at(row).section(';', 0, 0);
    return str;
}

//QString CSV::  get_money_csv(int row){
//    QFile file(filename);
//    file.open(QFile::ReadOnly | QFile::Text);
//    QString str;
//    QString line;
//    for(int i = 0; i < row; i++){
//        line = file.readLine();
//        str = line.section(';', 3, 3);
//    }
//    file.close();
//    return str;
//}


QString CSV::  get_money_csv(int row){
    QString str;
    str = lines.at(row).section(';', 3, 3);
    return str;
}
