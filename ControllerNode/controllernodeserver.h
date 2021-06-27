#ifndef CONTROLLERNODESERVER_H
#define CONTROLLERNODESERVER_H

#include <QTcpServer>
#include <QList>
using namespace std;

class ControllerNodeSocket;

class ControllerNodeServer : public QTcpServer
{
public:
    ControllerNodeServer(QObject *parent = nullptr);
    bool startServer(quint16 port);
protected:
    void incomingConnection(qintptr handle);
private:
    QList<ControllerNodeSocket *> mSockets;
};

#endif // CONTROLLERNODESERVER_H
