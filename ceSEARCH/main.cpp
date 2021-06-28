#include "widget.h"
#include <QApplication>

///
/// \brief qMain
/// \param argc
/// \param argv
/// \return
///
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
