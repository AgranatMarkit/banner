#include "banner.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    QApplication a(argc, argv);
    banner w;
    w.show();

    return a.exec();
}
