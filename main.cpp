#include <QtGui/QApplication>
#include <QTranslator>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator* translator = new QTranslator();
    translator->load("lua-editor_en");

    a.installTranslator(translator);

    MainWindow w;
    w.show();
    
    return a.exec();
}
