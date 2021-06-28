#include "controllernodesocket.h"

///
/// \brief ControllerNodeSocket::ControllerNodeSocket
/// \param handle
/// \param parent
///
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
