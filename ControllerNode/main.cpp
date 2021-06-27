#include <QCoreApplication>
#include "controllernodeserver.h"
#include <QTcpServer>
#include <QTcpSocket>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ControllerNodeServer Server;
    if(!Server.startServer(3333)){
        qDebug() << "Error: " << Server.errorString();
        return 1;
    }
    qDebug() << "Server started";
    return a.exec();
}
