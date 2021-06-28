#include <QCoreApplication>
#include "controllernodeserver.h"

using namespace std;

///
/// \brief main
/// \param argc
/// \param argv
/// \return
///
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ControllerNodeServer Server;
    ControllerNodeServer Server2;
    ControllerNodeServer Server3;
    if(!Server.startServer(3333)){
        qDebug() << "Error: " << Server.errorString();
        return 1;
    }
    qDebug() << "Server started1";
    if(!Server2.startServer(4444)){
        qDebug() << "Error: " << Server.errorString();
        return 1;
    }
    qDebug() << "Server started2";
    if(!Server3.startServer(5555)){
        qDebug() << "Error: " << Server.errorString();
        return 1;
    }
    qDebug() << "Server started3";
    return a.exec();
}
