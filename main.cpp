#include "client/gui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication Blockchain(argc, argv);
    MainWindow window;
    window.setWindowTitle("MainWindowName");
    window.display();
    return Blockchain.exec();
}
