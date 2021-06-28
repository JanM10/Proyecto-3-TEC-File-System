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


private slots:

    void on_botonEnviar_clicked();

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
