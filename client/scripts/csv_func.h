#ifndef CSV_FUNC_H
#define CSV_FUNC_H
#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <QtDebug>

#include <QDate>
#include <QTime>
#include <QDateTime>

using namespace std;

class CSV {
public:
    CSV(QString fileName);
    void append_csv_request(QString date, QString message, QString label, double amount);
    QString get_message_csv(int row);
    QString get_label_csv(int row);
    QString get_date_csv(int row);
    QString get_money_csv(int row);

private:
     QString filename;
};


#endif // CSV_FUNC_H
