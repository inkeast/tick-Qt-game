#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QPushButton>
#include <QMainWindow>
#include<QStackedWidget>
#include<QLabel>
#include<QTextBrowser>
#include<QMultimedia>
#include<QMediaPlayer>
#include<QOpenGLWidget>
#include<QSlider>
#include<QGraphicsView>
#include<QGraphicsPixmapItem>
#include<QGroupBox>
#include<QTextBrowser>
#include<QtGui>
#include "game.h"
#include "./logic/game_logic.h"
#include "./logic/game_map.h"
//基本界面已经实现
//但是由于openGL和GraphicView的问题没有弄明白所现阶段没有这两个控件

extern QGraphicsScene *scene;
extern runner runner1;
extern catcher catcher1;
extern game game_contrl;
extern QMediaPlayer *mp;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



    //开始界面的button控件
    QPushButton *button1_start;
    QPushButton *button2_int;
    QPushButton *button3_set;
    QPushButton *button4_quit;
    QPushButton *button5_re;

    //游戏界面的控件
   // QOpenGLWidget *openGl;
    QGraphicsView *graphicsView;
    QPushButton *button6_re;
    QPushButton *button9_str;
    QLabel *label1;
    QLabel *label2;

    //结束界面
   QPushButton *button10_re;

   //说明界面
   QTextBrowser *Browser;
   QPushButton *button7_re;
   QTextBrowser *brower1;
   QTextBrowser *brower2;

   //设置界面
   QSlider *slider1;
   QSlider *slider2;
   QPushButton *button8_re;


   //进度条


public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
   void button1_start_click();
   void button2_int_click();
   void button3_set_click();
   void button4_quit_click();
   void button6_re_click();
   void button7_re_click();
   void button8_re_click();
   void button9_str_click();
   void button10_str_click();
   void init_Scene();
   void init_MediaPlayer();
   void change_volumn();

private:
    Ui::MainWindow *ui;
};
/*
class the_timer : public QObject{
    Q_OBJECT

public:
    key_in_timer(QObject* parent = NULL);
    ~key_in_timer();
    void  handleTimeout();  //超时处理函数
    virtual void timerEvent( QTimerEvent *event);
private:
    int m_nTimerID;

};
*/

#endif // MAINWINDOW_H
