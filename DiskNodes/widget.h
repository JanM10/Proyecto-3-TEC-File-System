#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QApplication>
#include <QtCore>
#include <QtXml/QtXml>
#include <QtDebug>
#include <tinyxml2.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QTcpSocket;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void on_Enviar_clicked();
    void on_Conectar_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *mSocket;
};
#endif // WIDGET_H
