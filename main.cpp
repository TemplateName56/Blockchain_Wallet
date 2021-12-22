#include "client/gui/mainwindow.h"

#include <QApplication>

#include "client/classes/blockchain.h"
#include "client/classes/users.h"

int main(int argc, char *argv[])
{
    QApplication BlockchainWallet(argc, argv);
    MainWindow window;

    window.setWindowTitle("My Wallet");
    window.setWindowIcon(QIcon("icons/programIcon.png"));
    window.display();

    return BlockchainWallet.exec();
}
