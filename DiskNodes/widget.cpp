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

void Widget::on_Enviar_clicked()
{
    QTextStream T(mSocket);
    T << ui->Nickname->text() << ": " << ui->Message->text();
    mSocket->flush();
    ui->Message->clear();
}

void Widget::on_Conectar_clicked()
{
    ConnectionDialog D(this);
    if(D.exec() == QDialog::Rejected){
        return;
    }
    mSocket->connectToHost(D.hostname(),D.port());
}


