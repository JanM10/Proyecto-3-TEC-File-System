#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <string>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class QTcpSocket;

///
/// \brief The Widget class
///
class Widget : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief Widget
    /// \param parent
    ///
    Widget(QWidget *parent = nullptr);
    ~Widget();

    ///
    /// \brief texto
    ///
    string texto = "";

private slots:
    ///
    /// \brief on_botonBuscar_clicked
    ///
    void on_botonBuscar_clicked();

    ///
    /// \brief on_botonSubir_clicked
    ///
    void on_botonSubir_clicked();

    ///
    /// \brief on_botonBuscar2_clicked
    ///
    void on_botonBuscar2_clicked();

    ///
    /// \brief on_botonMostrar_clicked
    ///
    void on_botonMostrar_clicked();

private:
    ///
    /// \brief ui
    ///
    Ui::Widget *ui;

    ///
    /// \brief mSocket
    ///
    QTcpSocket *mSocket;
};
#endif // WIDGET_H
