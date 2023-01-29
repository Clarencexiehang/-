#include "mainwindow.h"
#include <QApplication>
#include "pcb.h"
#include "vector"

using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //随机创建5个进程


    MainWindow w;
    w.show();

    return a.exec();
}





