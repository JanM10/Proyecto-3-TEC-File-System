#include "connectiondialog.h"
#include "ui_connectiondialog.h"


ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_botonAceptar_clicked()
{
    mHostname = ui->Hostname->text();
    mPort = ui->Port->value();
    accept();
}

void ConnectionDialog::on_botonCancelar_clicked()
{
    reject();
}
