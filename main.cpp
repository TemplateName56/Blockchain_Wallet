#include "client/gui/mainwindow.h"

#include <QApplication>

#include "client/classes/blockchain.h"
#include "client/classes/users.h"

int main(int argc, char *argv[])
{
    QApplication BlockchainWallet(argc, argv);
    MainWindow window;

    QCoreApplication::setOrganizationName("KNT-120_3");
    QCoreApplication::setApplicationName("Blockchain Wallet");

    window.setWindowTitle("My Wallet");
    window.setWindowIcon(QIcon("icons/programIcon.png"));
    window.display();

    return BlockchainWallet.exec();
}
