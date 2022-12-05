#include "session.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    session* sessio;
    sessio = new session;

    return a.exec();
}
