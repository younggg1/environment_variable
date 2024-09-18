#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("Java & Maven Environment Configurator");
    w.show();
    return a.exec();
}
