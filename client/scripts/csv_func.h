#ifndef CSV_FUNC_H
#define CSV_FUNC_H

#include "client/classes/program_exception.h"

#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <QtDebug>

#include <QDate>
#include <QTime>
#include <QDateTime>

using std::cout;

class CSV {
public:

    enum languages_csv
    {
        English,
        Ukrainian,
        Russian
    };

    CSV(QString fileName);
    void append_csv_request(QString link, QString message, QString amount,QString type_amount, QString reciever);
    QString get_message_csv(int row);
    QString get_label_csv(int row);
    QString get_date_csv(int row);
    QString get_money_csv(int row);
    int get_amount_row();
    QVector<QString> find_user(QString user);
    QVector<QString> getList();

    QVector<QString> get_tr(int language_index);
private:
     QString filename;
      QVector<QString> lines;
};


#endif // CSV_FUNC_H
