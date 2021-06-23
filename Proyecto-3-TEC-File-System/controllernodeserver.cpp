#include "controllernodeserver.h"
#include "controllernodesocket.h"
#include <QDebug>
#include <QTextStream>

ControllerNodeServer::ControllerNodeServer(QObject *parent)
    :QTcpServer(parent)
{

}

bool ControllerNodeServer::startServer(quint16 port)
{
    return listen(QHostAddress::Any, port);
}

void ControllerNodeServer::incomingConnection(qintptr handle)
{
    qDebug() << "El cliente se conecto con:" << handle;
    auto socket = new ControllerNodeSocket(handle, this);
    mSockets << socket;

    connect(socket, &ControllerNodeSocket::ControllerReadyRead, [&](ControllerNodeSocket *S){
        qDebug() << "ControllerNodeReadyRead";
        QTextStream T(S);
        auto text = T.readAll();

        for(auto i : mSockets){
            QTextStream K(i);
            K << text;
            i->flush();
        }
    });

    connect(socket, &ControllerNodeSocket::ControllerStateChanged,
            [&](ControllerNodeSocket *S, int ST){
        qDebug() << "ControllerNodeStateChanged con:" << S->setSocketDescriptor();
        if(ST == QTcpSocket::UnconnectedState){
            qDebug() << "Desconectado:" << S->socketDescriptor();
            mSockets.removeOne(S);
            for(auto i : mSockets){
                QTextStream K(i);
                K << "Server: El cliente "
                <<S->socketDescriptor()
                << "se ha desconectado";
                i->flush();
            }
        }
    });
}
