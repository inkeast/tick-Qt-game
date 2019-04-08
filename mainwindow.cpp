#include "mainwindow.h"
#include "game.h"
#include "ui_mainwindow.h"
#include"ui_game.h"
#include"ui_introduction.h"
#include"ui_result.h"
#include<QGraphicsView>
#include<QGraphicsItem>
#include<QGraphicsScene>
#include"ui_setting.h"
#include"ui_start.h"
#include<QWidget>
#include<QPoint>
#include <QTimer>
#include <QObject>
#include<QDebug>
#include<QStackedWidget>
#include<QSize>
#include<QHBoxLayout>
#include <Windows.h>
#include <cstring>
#include<QPalette>
#include <QSound>
#include <iostream>
#include "./logic/game_logic.h"
#include "./logic/game_map.h"

#define TILE_SIZE 70

runner runner1;
catcher catcher1;
game game_contrl;
QGraphicsScene *scene;
QStackedWidget *Stack;//拥有所有界面的stack
QMediaPlayer *mp;

QTimer *timer ;
QTimer *timer_one;
QTimer *sk3timer;

Ui::Game uiG;
Ui::Introduction uiI;
Ui::Result uiR;
Ui::Setting uiSet;
Ui::Start uiSt;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1440,900);
    setMinimumHeight(900);
    setMinimumWidth(1440);




init_MediaPlayer();
    QWidget *widget1=new QWidget(this);
    QWidget *widget2=new QWidget(this);
    QWidget *widget3=new QWidget(this);
    QWidget *widget4=new QWidget(this);
    QWidget *widget5=new QWidget(this);

    uiSt.setupUi(widget1);
    uiG.setupUi(widget2);
    uiR.setupUi(widget3);
    uiI.setupUi(widget4);
    uiSet.setupUi(widget5);

    //widget2
    Stack=ui->stackedWidget;
    widget5->setAutoFillBackground(true);
        QPalette palette;
        QPixmap pixmap("://sourse/stack_1.jpg");
        palette.setBrush(QPalette::Window,QBrush(pixmap));
        widget5->setPalette(palette);

    button1_start=uiSt.pushButton;
    button2_int=uiSt.pushButton_2;
    button3_set=uiSt.pushButton_3;
    button4_quit=uiSt.pushButton_4;
    button6_re=uiG.pushButton;
    button7_re=uiI.pushButton;
    button8_re=uiSet.pushButton;
    button9_str=uiG.pushButton_2;
    button10_re=uiR.retur;
    brower1=uiI.textBrowser;
    brower2=uiI.textBrowser_2;
    brower1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    brower2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
 //   button9_str->setFont();
    graphicsView=uiG.graphicsView;
    graphicsView->resize(802,802);
    scene=new QGraphicsScene(this);
    graphicsView->setScene(scene);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    slider1=uiSet.horizontalSlider;
    slider2=uiSet.horizontalSlider_2;
    slider1->setMinimum(0);
    slider1->setMaximum(200);
    slider1->setSingleStep(1);
    slider1->setEnabled(true);

    Stack->addWidget(widget1);
    Stack->addWidget(widget2);
    Stack->addWidget(widget3);
    Stack->addWidget(widget4);
    Stack->addWidget(widget5);




    connect(button1_start,&QPushButton::clicked,this,&MainWindow::button1_start_click);
    connect(button2_int,&QPushButton::clicked,this,&MainWindow::button2_int_click);
    connect(button3_set,&QPushButton::clicked,this,&MainWindow::button3_set_click);
    connect(button4_quit,&QPushButton::clicked,this,&MainWindow::button4_quit_click);
    connect(button6_re,&QPushButton::clicked,this,&MainWindow::button6_re_click);
    connect(button7_re,&QPushButton::clicked,this,&MainWindow::button7_re_click);
    connect(button8_re,&QPushButton::clicked,this,&MainWindow::button8_re_click);
    connect(button9_str,&QPushButton::clicked,this,&MainWindow::button9_str_click);
    connect(button10_re,&QPushButton::clicked,this,&MainWindow::button10_str_click);
    //connect(slider1,SIGNAL(valueChanged(int)),this,SIGNAL(change_volumn));
    connect(slider1,&QSlider::sliderMoved,this,&MainWindow::change_volumn);
    slider1->setValue(20);

//    button1_start->setText("Start");
//    button2_int->setText("Introduction");
//    button3_set->setText("Setting");
//    button4_quit->setText("Quit");
//    button6_re->setText("Return");
//    button7_re->setText("Return");
//    button8_re->setText("Return");
//    button9_str->setText("start");

    mp=new QMediaPlayer;
    QHBoxLayout *layout=new QHBoxLayout;
    QWidget *widget=new QWidget(this);
    layout->addWidget(Stack);
    widget->setLayout(layout);
    this->setCentralWidget(widget);
    widget->show();
    Stack->setCurrentIndex(2);
}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::button1_start_click()
{
    Stack->setCurrentIndex(3);
}
void MainWindow::button2_int_click()
{
    Stack->setCurrentIndex(5);
}
void MainWindow::button3_set_click()
{
    Stack->setCurrentIndex(6);
}
void MainWindow::button4_quit_click()
{
    QApplication::quit();
}
void MainWindow::button6_re_click()
{
    Stack->setCurrentIndex(2);
}
void MainWindow::button7_re_click()
{
    Stack->setCurrentIndex(2);
}
void MainWindow::button8_re_click()
{
    Stack->setCurrentIndex(2);
}
void MainWindow::button10_str_click()
{
    Stack->setCurrentIndex(2);
}

void clear_catcher_skill_3(){
    if(catcher1.catcher_skill_3_graph_number>0){
        scene->removeItem(catcher1.graph_for_skill_3[catcher1.catcher_skill_3_graph_cache_number]);
        catcher1.catcher_skill_3_graph_cache_number++;
        if(catcher1.catcher_skill_3_graph_cache_number==catcher1.catcher_skill_3_graph_number){
           catcher1.catcher_skill_3_graph_cache_number=0;
           catcher1.catcher_skill_3_graph_number=0;
        }
    }


}
void time_in_update(){
    char cache[2]={0,0};
    unsigned int result=0;
    cache[0]=48+runner1.get_lives();
    runner1.keyboard_in();
    catcher1.keyboard_in();
    game_contrl.all_move(catcher1,runner1);
    game_contrl.all_skill(catcher1,runner1,scene);
    uiG.heart->setText(cache);
    result=game_contrl.victor_judge(catcher1,runner1);
    if(result) {
        QPixmap images;
        timer_one->stop();
        timer->stop();
        Stack->setCurrentIndex(4);
        if(result==1){
            images.load(":/sourse/runner.gif");
            uiR.image->setPixmap(images.scaled(800,800));
            uiR.txt->setText("逃亡者胜利");
        }else{
            images.load(":/sourse/monster.jpg");
            uiR.image->setPixmap(images.scaled(800,800));
            uiR.txt->setText("抓捕者胜利");
        }
    }
    game_contrl.all_skill_clear(catcher1,runner1,scene);
    if(catcher1.get_energy()>2000) uiG.pover_energy_progressBar->setValue(2000);
        else uiG.pover_energy_progressBar->setValue(catcher1.get_energy());
}

void time_for_one(){
    game_contrl.timer(catcher1, runner1);
    if(catcher1.get_cather_skill_1_last()){
       uiG.catcher_skill_1_label->setText("定身生效中");
       uiG.catcher_skill_1_progressBar->setRange(0,catcher_skill_1_last_time);
       uiG.catcher_skill_1_progressBar->setValue(catcher1.get_cather_skill_1_last());
    }else if(catcher1.get_skill_1_cooling()){
       uiG.catcher_skill_1_label->setText("定身冷却中");
       uiG.catcher_skill_1_progressBar->setRange(0,catcher_skill_1_initial_value);
       uiG.catcher_skill_1_progressBar->setValue(catcher_skill_1_initial_value-catcher1.get_skill_1_cooling());
    }else{
       uiG.catcher_skill_1_label->setText("定身冷却完成");
       uiG.catcher_skill_1_progressBar->setRange(0,catcher_skill_1_initial_value);
       uiG.catcher_skill_1_progressBar->setValue(catcher_skill_1_initial_value-catcher1.get_skill_1_cooling());
    }
    if(catcher1.get_cather_skill_2_last()){
       uiG.catcher_skill_2_label->setText("岩壁生效中");
       uiG.catcher_skill_2_progressBar->setRange(0,catcher_skill_2_last_time);
       uiG.catcher_skill_2_progressBar->setValue(catcher1.get_cather_skill_2_last());
    }else if(catcher1.get_skill_2_cooling()){
       uiG.catcher_skill_2_label->setText("岩壁冷却中");
       uiG.catcher_skill_2_progressBar->setRange(0,catcher_skill_2_initial_value);
       uiG.catcher_skill_2_progressBar->setValue(catcher_skill_2_initial_value-catcher1.get_skill_2_cooling());
    }else{
       uiG.catcher_skill_2_label->setText("岩壁冷却完成");
       uiG.catcher_skill_2_progressBar->setRange(0,catcher_skill_2_initial_value);
       uiG.catcher_skill_2_progressBar->setValue(catcher_skill_2_initial_value-catcher1.get_skill_2_cooling());
    }

    if(catcher1.get_skill_3_cooling()){
           uiG.catcher_skill_3_label->setText("裂地冷却中");
           uiG.catcher_skill_3_progressBar->setRange(0,catcher_skill_3_initial_value);
           uiG.catcher_skill_3_progressBar->setValue(catcher_skill_3_initial_value-catcher1.get_skill_3_cooling());
        }else{
           uiG.catcher_skill_3_label->setText("裂地冷却完成");
           uiG.catcher_skill_3_progressBar->setRange(0,catcher_skill_3_initial_value);
           uiG.catcher_skill_3_progressBar->setValue(catcher_skill_3_initial_value-catcher1.get_skill_3_cooling());
        }
    if(runner1.get_skill_1_cooling()){
           uiG.runner_skill_1_label->setText("闪现冷却中");
           uiG.runner_skill_1_progressBar->setRange(0,runner_skill_1_initial_value);
           uiG.runner_skill_1_progressBar->setValue(runner_skill_1_initial_value-runner1.get_skill_1_cooling());
        }else{
           uiG.runner_skill_1_label->setText("闪现冷却完成");
           uiG.runner_skill_1_progressBar->setRange(0,runner_skill_1_initial_value);
           uiG.runner_skill_1_progressBar->setValue(runner_skill_1_initial_value-runner1.get_skill_1_cooling());
        }
    if(runner1.get_skill_2_cooling()){
           uiG.runner_skill_2_label->setText("传送冷却中");
           uiG.runner_skill_2_progressBar->setRange(0,runner_skill_2_initial_value);
           uiG.runner_skill_2_progressBar->setValue(runner_skill_2_initial_value-runner1.get_skill_2_cooling());
        }else{
           uiG.runner_skill_2_label->setText("传送冷却完成");
           uiG.runner_skill_2_progressBar->setRange(0,runner_skill_2_initial_value);
           uiG.runner_skill_2_progressBar->setValue(runner_skill_2_initial_value-runner1.get_skill_2_cooling());
        }
    if(runner1.get_runner_skill_3_last()){
       uiG.runner_skill_3_label->setText("分身生效中");
       uiG.runner_skill_3_progressBar->setRange(0,runner_skill_3_last_time);
       uiG.runner_skill_3_progressBar->setValue(runner1.get_runner_skill_3_last());
    }else if(runner1.get_skill_3_cooling()){
       uiG.runner_skill_3_label->setText("分身冷却中");
       uiG.runner_skill_3_progressBar->setRange(0,runner_skill_3_initial_value);
       uiG.runner_skill_3_progressBar->setValue(runner_skill_3_initial_value-runner1.get_skill_3_cooling());
    }else{
       uiG.runner_skill_3_label->setText("分身冷却完成");
       uiG.runner_skill_3_progressBar->setRange(0,runner_skill_3_initial_value);
       uiG.runner_skill_3_progressBar->setValue(runner_skill_3_initial_value-runner1.get_skill_3_cooling());
    }

    //game_contrl.debug(catcher1, runner1);
}

void MainWindow::button9_str_click()
{
   game_contrl.game_init(map_data,catcher1,runner1,scene);

   if(timer){
       timer->stop();
       delete timer;
   }
   if(timer_one){
       timer_one->stop();
       delete timer_one;
   }
   if(sk3timer){
       sk3timer->stop();
       delete sk3timer;
   }

   timer   =new QTimer(this);
   connect(timer,&QTimer::timeout,this,time_in_update);
   timer->start(20);
   timer_one =new QTimer(this);
   connect(timer_one,&QTimer::timeout,this,time_for_one);
   timer_one->start(1000);
   sk3timer =new QTimer(this);
   connect(sk3timer,&QTimer::timeout,this,clear_catcher_skill_3);
   sk3timer->start(25);
   uiG.pover_energy_progressBar->setRange(0,2*energy_initial_value);
   uiG.catcher_skill_2_progressBar->setRange(0,catcher_skill_2_initial_value);
   uiG.catcher_skill_3_progressBar->setRange(0,catcher_skill_3_initial_value);
   uiG.runner_skill_1_progressBar->setRange(0,runner_skill_1_initial_value);
   uiG.runner_skill_2_progressBar->setRange(0,runner_skill_2_initial_value);
   uiG.runner_skill_3_progressBar->setRange(0,runner_skill_3_initial_value);

}
void MainWindow::init_MediaPlayer()
{
    mp=new QMediaPlayer;
      QString runPath=QCoreApplication::applicationDirPath();
      qDebug()<<"\n\n";
        qDebug()<<runPath;
        qDebug()<<"\n\n";
    QString Ap=runPath+"/BGM.mp3";
   Ap.replace(QString("/"),QString("\\"));
      QMediaPlayer *mp=new QMediaPlayer;
      mp->setMedia(QUrl::fromLocalFile(Ap));
      mp->setVolume(100);
      mp->play();

}
void MainWindow::change_volumn()
{
    mp->setVolume(slider1->value());
}


