#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include "connectiondialog.h"
#include <QTextStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);

    connect(mSocket, &QTcpSocket::readyRead, [&](){
        QTextStream T(mSocket);
        auto text = T.readAll();
        ui->textEdit->append(text);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_botonEnviar_clicked()
{
    QTextStream T(mSocket);
    T << ui->Nickname->text() << ": " << ui->Mensaje->text();
    mSocket->flush();
    ui->Mensaje->clear();
}

void Widget::on_botonConectar_clicked()
{
    ConnectionDialog D(this);
    if(D.exec() == QDialog::Rejected){
        return;
    }
    mSocket->connectToHost(D.hostname(),D.port());
}
