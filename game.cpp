#include "game.h"
#include "ui_game.h"
#include<QGraphicsView>
#include"mainwindow.h"
#include<QGraphicsItem>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<Windows.h>
#include<QPixmap>
Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{

    ui->setupUi(this);
    graphicsView=ui->graphicsView;
    graphicsView->resize(800,800);
    scene=new QGraphicsScene(this);
    graphicsView->setScene(scene);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}



Game::~Game()
{
    delete ui;
}

