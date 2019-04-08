#ifndef GAME_H
#define GAME_H
#include<QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QWidget>

namespace Ui {
class Game;
}



class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    Ui::Game *ui;

};



#endif // GAME_H
