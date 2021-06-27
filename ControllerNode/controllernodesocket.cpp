#include "controllernodesocket.h"

ControllerNodeSocket::ControllerNodeSocket(qintptr handle, QObject *parent)
    :QTcpSocket(parent)
{
    setSocketDescriptor(handle);

    connect(this, ControllerNodeSocket::readyRead, [&](){
        emit ControllerReadyRead(this);
    });

    connect(this, ControllerNodeSocket::stateChanged, [&](int S){
        emit ControllerStateChanged(this, S);
    });
}

