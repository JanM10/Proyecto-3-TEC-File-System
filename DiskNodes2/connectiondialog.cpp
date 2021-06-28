#include "connectiondialog.h"
#include "ui_connectiondialog.h"

///
/// \brief ConnectionDialog::ConnectionDialog
/// \param parent
///
ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
}

///
/// \brief ConnectionDialog::~ConnectionDialog
///
ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

///
/// \brief ConnectionDialog::on_botonAceptar_clicked
///
void ConnectionDialog::on_botonAceptar_clicked()
{
    mHostname = ui->Hostname->text();
    mPort = ui->Puerto->value();
    accept();
}

///
/// \brief ConnectionDialog::on_botonCancelar_clicked
///
void ConnectionDialog::on_botonCancelar_clicked()
{
    reject();
}
