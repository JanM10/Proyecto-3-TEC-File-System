#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include "connectiondialog.h"
#include <QTextStream>

#include <QtCore>
#include <QtXml/QtXml>
#include <QtDebug>
#include <tinyxml2.h>

using namespace tinyxml2;

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
    XMLDocument doc;
    doc.LoadFile("C:/Users/Tutor/OneDrive/Documentos/GitHub/Proyecto-3-TEC-File-System/DiskNodes/Infor.xml");

    auto xmlElement = doc.FirstChildElement("TECFS-Disk");
    auto headElement = xmlElement->FirstChildElement("Server");
    auto ipElement = headElement->FirstChildElement("Ip");
    auto portElement = headElement -> FirstChildElement ("Port");
    //auto bodyElement = xmlElement->FirstChildElement("File");
    //auto pElement1 = bodyElement -> FirstChildElement("Path1");
    //auto pElement2 = bodyElement -> FirstChildElement("Path2");

    mSocket->connectToHost(ipElement -> GetText(), portElement->FloatText());
}


