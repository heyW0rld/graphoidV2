//#include "canvas.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setWindowIcon(QIcon("./images/0.png"));
    w.setMouseTracking(true);
    w.show();
    return a.exec();
}
