#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <string>

using namespace std;

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
    string texto = "";

private slots:

    void on_botonBuscar_clicked();

    void on_botonSubir_clicked();

    void on_botonBuscar2_clicked();

    void on_botonMostrar_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *mSocket;
};
#endif // WIDGET_H
