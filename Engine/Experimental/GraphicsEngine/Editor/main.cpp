#include "AcadEditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AcadEditor w;
    w.show();
    return a.exec();
}
