#include "FazanGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FazanGUI w;
    w.show();
    return a.exec();
}
