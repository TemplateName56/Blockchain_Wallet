#include "client/gui/mainwindow.h"
#include <QApplication>
#include "client/blockchain/blockchain.h"
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

    // Delete after tests
    Users users;
    users.addUser(User("123", "321", UKRANIAN, false));
    qDebug() << users.getUser("123").getAddress();

    return BlockchainWallet.exec();
}
