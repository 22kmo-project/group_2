//#include "mainwindow.h"
#include "session.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    session* sessio;
    sessio = new session;

    return a.exec();
}
