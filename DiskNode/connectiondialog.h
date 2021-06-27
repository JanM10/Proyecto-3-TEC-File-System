#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>


namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = nullptr);
    ~ConnectionDialog();
    QString hostname() const;
    quint16 port() const;

private slots:
    void on_botonAceptar_clicked();
    void on_botonCancelar_clicked();

private:
    Ui::ConnectionDialog *ui;
    QString mHostname;
    quint16 mPort;


};

inline QString ConnectionDialog::hostname() const
{
    return mHostname;
}

inline quint16 ConnectionDialog::port() const
{
    return mPort;
}


#endif // CONNECTIONDIALOG_H
