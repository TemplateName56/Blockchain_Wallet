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

    // delete after tests
    Blockchain newchain;
    for(int index = 1; index <= 3; index++)
    {
        newchain.addBlock(index,TransactionData("petya", "vasya", rand() % 56, BWC), newchain.getLastBlock().getBlockHash());
        //Sleep(1000);
    }
    newchain.show();

    newchain.writeChain();

    qDebug() << newchain.isChainValid();

    try {
        newchain.collisionCheck();
    }  catch (ProgramException &error) {
        error.getError();
    }


    return BlockchainWallet.exec();
}
