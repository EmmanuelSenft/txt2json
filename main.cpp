#include "txt2json.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    txt2json w;
    w.show();

    return a.exec();
}
