#include <QApplication>
#include "qrcode_clock.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qrcode_clock w;
    w.show();
    
    return a.exec();
}
