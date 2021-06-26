#include "widget.h"
#include <QApplication>
#include <QtCore>
#include <QtXml/QtXml>
#include <QtDebug>
#include <tinyxml2.h>

using namespace tinyxml2;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    a.setStyle("fusion");
    Widget w;
    w.show();

    return a.exec();
}
