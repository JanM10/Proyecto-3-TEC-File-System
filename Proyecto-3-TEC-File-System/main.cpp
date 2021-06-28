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
    if(!Server.startServer(3333)){
        qDebug() << "Error: " << Server.errorString();
        return 1;
    }
    qDebug() << "Server started";
    return a.exec();
}
