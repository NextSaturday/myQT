#include "tSelection.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tSelection w;
    w.show();
    return a.exec();
}
