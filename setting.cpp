#include "setting.h"
#include "ui_setting.h"
#include<mainwindow.h>
Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
}

Setting::~Setting()
{
    delete ui;
}


void Setting::on_horizontalSlider_valueChanged(int value)
{
 mp->setVolume(value);
}
