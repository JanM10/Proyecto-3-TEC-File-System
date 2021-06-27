#ifndef CONTROLLERNODESOCKET_H
#define CONTROLLERNODESOCKET_H

#include <QtNetwork/QTcpSocket>
using namespace std;

class ControllerNodeSocket : public QTcpSocket
{
    Q_OBJECT
public:
    ControllerNodeSocket(qintptr handle, QObject *parent = nullptr);
signals:
    void ControllerReadyRead(ControllerNodeSocket *);
    void ControllerStateChanged(ControllerNodeSocket *, int);
};

#endif // CONTROLLERNODESOCKET_H
