#include "System.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Individual work");

    System testing;

    QString name="test";
    name.toStdString().data();
    testing.addCategory((char*)name.toStdString().data());
    w.show();

    return a.exec();
}
