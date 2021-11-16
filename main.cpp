#include "client/gui/mainwindow.h"
#include <QApplication>
#include "client/blockchain/blockchain.h"

int main(int argc, char *argv[])
{
    QApplication BlockchainWallet(argc, argv);
    MainWindow window;

    QCoreApplication::setOrganizationName("KNT-120_3");
    QCoreApplication::setApplicationName("Blockchain Wallet");

    window.setWindowTitle("My Wallet");
    window.setWindowIcon(QIcon("icons/programIcon.png"));
    window.display();

    Blockchain newchain;
    for(int index = 1; index <= 3; index++)
    {
        newchain.addBlock(index,TransactionData("petya","vasya",rand() % 3,BWC), newchain.getLastBlock().getPrevBlockHash());
        Sleep(1000);
    }
    newchain.show();

    return BlockchainWallet.exec();
}
