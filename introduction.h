#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <QWidget>

namespace Ui {
class Introduction;
}

class Introduction : public QWidget
{
    Q_OBJECT

public:
    explicit Introduction(QWidget *parent = 0);
    ~Introduction();

private:
    Ui::Introduction *ui;
};

#endif // INTRODUCTION_H
