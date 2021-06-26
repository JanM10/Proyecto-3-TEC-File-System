#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);

    connect(mSocket, &QTcpSocket::readyRead, [&](){
        QTextStream T(mSocket);
        auto text = T.readAll();
        ui->textoBuscado->append(text);
    });

    mSocket->connectToHost("localhost","3333");
}

Widget::~Widget()
{
    delete ui;
}

//void Widget::on_Enviar_clicked()
//{
//    QTextStream T(mSocket);
//    T << ui->Nickname->text() << ": " << ui->Message->text();
//    mSocket->flush();
//    ui->Message->clear();


//}

void Widget::on_Conectar_clicked()
{
    ConnectionDialog D(this);
    if(D.exec() == QDialog::Rejected){
        return;
    }
    mSocket->connectToHost(D.hostname(),D.port());
}

void Widget::on_botonBuscar_clicked()
{
    QString filter = "All File (*.*) ;; Text File (*.txt) ;; XML File (*.xml)";
    QString nombre_archivo = QFileDialog::getOpenFileName(this,"open a file","C://",filter);
    QFile archivo(nombre_archivo);

    if(!archivo.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "title", "file not open");
    }
    QTextStream in(&archivo);
    QString texto = in.readAll();
    ui->textoBuscado->setPlainText(texto);
    archivo.close();
}

void Widget::on_botonSubir_clicked()
{

}
