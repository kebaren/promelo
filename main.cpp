#include <QApplication>
#include "promelowindow.h"

int main(int argc, char *argv[])
{
    QApplication::setOrganizationName("promelo");
    QApplication::setApplicationName("promelo");
    QGuiApplication::setApplicationDisplayName("promelo");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


    QApplication a(argc, argv);

    PromeloWindow w;
    w.show();

    return a.exec();
}
