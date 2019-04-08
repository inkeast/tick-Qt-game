#include "mainwindow.h"
#include <QApplication>
#include"ui_game.h"
//#include"ui_introduction.h"
//#include"ui_result.h"
//#include"ui_setting.h"
#include<QDialog>
//#include"ui_start.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
