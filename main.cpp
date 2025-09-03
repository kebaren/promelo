#include <QApplication>
#include "promelowindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PromeloWindow w;
    w.show();

    return a.exec();
}
