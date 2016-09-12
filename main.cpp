#include "mainwindow.h"
#include <QApplication>
#include <qtextcodec.h>

//#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    QFont font;
//    //font.setPointSize(55);
//    font.setFamily(("simsun"));
//    a.setFont(font);

    return a.exec();
}
