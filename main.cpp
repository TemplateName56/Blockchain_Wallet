#include "client/gui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication Blockchain(argc, argv);
    MainWindow window;

    QCoreApplication::setOrganizationName("KNT-120_3");
    QCoreApplication::setApplicationName("Blockchain Wallet");

    window.setWindowTitle("My Wallet");
    window.display();

    return Blockchain.exec();
}
