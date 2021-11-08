#include "csv_func.h"

CSV::CSV(QString fileName)
{
    filename = fileName;

}

void CSV:: append_csv_request(QString date, QString message, QString label, double amount){

    QFile file_out(filename);
    if ( !file_out.open(QFile::Append) ) {
        cout << "File not exists\n";
    } else {
         cout << "File exists\n";
        QTextStream out(&file_out);
        for(int i = 0; i < 1; i++){
            out << date << ";" << message << ";" << label << ";" << amount << "\n";
        }
        file_out.close();
    }
}

/*
int CSV:: get_amount_row(){
    QFile file(filename);
     file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    int counter = 0;
    while (!in.atEnd())
    {
        counter++;
    }
    file.close();
    return counter;
}
*/

QString CSV:: get_message_csv(int row){
    QFile file(filename);
    file.open(QFile::ReadOnly | QFile::Text);
    QString str;
    QString line;
    for(int i = 0; i < row; i++){
        line = file.readLine();
        str = line.section(';', 2, 2);
    }
    file.close();
    return str;
}

QString CSV::  get_label_csv(int row){
    QFile file(filename);
    file.open(QFile::ReadOnly | QFile::Text);
    QString str;
    QString line;
    for(int i = 0; i < row; i++){
        line = file.readLine();
        str = line.section(';', 1, 1);
    }
    file.close();
    return str;
}

QString CSV::  get_date_csv(int row){
    QFile file(filename);
    file.open(QFile::ReadOnly | QFile::Text);
    QString str;
    QString line;
    for(int i = 0; i < row; i++){
        line = file.readLine();
        str = line.section(';', 0, 0);
    }
    file.close();
    return str;
}

QString CSV::  get_money_csv(int row){
    QFile file(filename);
    file.open(QFile::ReadOnly | QFile::Text);
    QString str;
    QString line;
    for(int i = 0; i < row; i++){
        line = file.readLine();
        str = line.section(';', 3, 3);
    }
    file.close();
    return str;
}
