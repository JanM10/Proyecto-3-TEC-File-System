#ifndef CONTROLLERNODESOCKET_H
#define CONTROLLERNODESOCKET_H

#include <QTcpSocket>
using namespace std;

///
/// \brief The ControllerNodeSocket class
///
class ControllerNodeSocket : public QTcpSocket
{
    Q_OBJECT
public:
    ///
    /// \brief ControllerNodeSocket
    /// \param handle
    /// \param parent
    ///
    ControllerNodeSocket(qintptr handle, QObject *parent = nullptr);
signals:
    ///
    /// \brief ControllerReadyRead
    ///
    void ControllerReadyRead(ControllerNodeSocket *);

    ///
    /// \brief ControllerStateChanged
    ///
    void ControllerStateChanged(ControllerNodeSocket *, int);
};

#endif // CONTROLLERNODESOCKET_H
