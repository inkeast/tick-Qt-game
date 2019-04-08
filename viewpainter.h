#ifndef VIEWPAINTER_H
#define VIEWPAINTER_H
#include <QGraphicsView>


class ViewPainter : public QGraphicsView
{
public:
    ViewPainter();
    void painterEvent();
};

#endif // VIEWPAINTER_H
