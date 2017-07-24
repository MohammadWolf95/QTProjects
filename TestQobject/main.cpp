#include "mainwindow.h"
#include <QApplication>
#include "board.h"
#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Board b, c;
    QObject::connect(&b, SIGNAL(valueChanged(int)),
                           &c, SLOT(setValue(int));

    b.setValue(12);

    qDebug()<<"Hello World"<<endl;

    MainWindow w;
    w.show();

    return a.exec();
}
