#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication Blockchain(argc, argv);
    MainWindow window;
    window.show();
    return Blockchain.exec();
}
