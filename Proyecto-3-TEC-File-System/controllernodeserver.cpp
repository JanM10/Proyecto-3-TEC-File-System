#include "controllernodeserver.h"
#include "controllernodesocket.h"
#include <QDebug>
#include <QTextStream>

///
/// \brief ControllerNodeServer::ControllerNodeServer
/// \param parent
///
ControllerNodeServer::ControllerNodeServer(QObject *parent)
    :QTcpServer(parent)
{

}

///
/// \brief ControllerNodeServer::startServer
/// \param port
/// \return
///
bool ControllerNodeServer::startServer(quint16 port)
{
    return listen(QHostAddress::Any, port);
}

///
/// \brief ControllerNodeServer::incomingConnection
/// \param handle
///
void ControllerNodeServer::incomingConnection(qintptr handle)
{
    qDebug() << "El cliente se conecto con:" << handle;
    auto socket = new ControllerNodeSocket(handle, this);
    mSockets << socket;

    for(auto i : mSockets){
        QTextStream T(i);
        T << "Server: Se ha conectado->" << handle;
        i->flush();
    }

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
        qDebug() << "ControllerNodeStateChanged con:" << S->socketDescriptor();
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
