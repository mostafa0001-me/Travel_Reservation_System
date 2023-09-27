#include "signin.h"

#include <QApplication>

#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGuiApplication::setQuitOnLastWindowClosed(false);
    signin w;
    w.show();
    return a.exec();
}
