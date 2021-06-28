#ifndef CONTROLLERNODESERVER_H
#define CONTROLLERNODESERVER_H

#include <QTcpServer>
#include <QList>
using namespace std;

class ControllerNodeSocket;

///
/// \brief The ControllerNodeServer class
///
class ControllerNodeServer : public QTcpServer
{
public:
    ///
    /// \brief ControllerNodeServer
    /// \param parent
    ///
    ControllerNodeServer(QObject *parent = nullptr);

    ///
    /// \brief startServer
    /// \param port
    /// \return
    ///
    bool startServer(quint16 port);
protected:

    ///
    /// \brief incomingConnection
    /// \param handle
    ///
    void incomingConnection(qintptr handle);
private:

    ///
    /// \brief mSockets
    ///
    QList<ControllerNodeSocket *> mSockets;
};

#endif // CONTROLLERNODESERVER_H
