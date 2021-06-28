#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>


namespace Ui {
class ConnectionDialog;
}

///
/// \brief The ConnectionDialog class
///
class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    ///
    /// \brief ConnectionDialog
    /// \param parent
    ///
    explicit ConnectionDialog(QWidget *parent = nullptr);
    ~ConnectionDialog();

    ///
    /// \brief hostname
    /// \return
    ///
    QString hostname() const;

    ///
    /// \brief port
    /// \return
    ///
    quint16 port() const;

private slots:
    void on_botonAceptar_clicked();
    void on_botonCancelar_clicked();

private:
    ///
    /// \brief ui
    ///
    Ui::ConnectionDialog *ui;

    ///
    /// \brief mHostname
    ///
    QString mHostname;

    ///
    /// \brief mPort
    ///
    quint16 mPort;


};

///
/// \brief ConnectionDialog::hostname
/// \return
///
inline QString ConnectionDialog::hostname() const
{
    return mHostname;
}

///
/// \brief ConnectionDialog::port
/// \return
///
inline quint16 ConnectionDialog::port() const
{
    return mPort;
}


#endif // CONNECTIONDIALOG_H
