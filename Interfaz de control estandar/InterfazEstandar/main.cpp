#include "interfazestandar.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("RoboticArmControler");
    a.setApplicationVersion("0.3");
    a.setOrganizationName("UniversidadVeracruzana");
    a.setOrganizationDomain("www.uv.com");


    InterfazEstandar w;
    w.show();
    return a.exec();
}
