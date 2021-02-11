#include "JAProject.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    srand((unsigned)time(0));
    QApplication a(argc, argv);    
    JAProject w;
    w.show();
    return a.exec();
}

