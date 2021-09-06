#include "mainwindow.h"
#include "iniciarregistrar.h"
#include "players.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    iniciarregistrar IR;
    IR.show();
    //players in;
    //in.show();
    //MainWindow w;
    //w.show();

    return a.exec();
}
