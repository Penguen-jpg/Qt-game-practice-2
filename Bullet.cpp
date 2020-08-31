#include "Bullet.h"
#include <QTimer>
#include <qmath.h>
#include "Game.h"
extern Game *game;

Bullet::Bullet(QGraphicsItem *parent):QObject(),QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/bullet.png"));//設定子彈圖片

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));//連接timer跟move()
    timer->start(50);//每0.05秒做一次
}

void Bullet::move()
{
    int STEP_SIZE=30;//每次移動距離
    double theta=rotation();//旋轉"角度"

    double dy=STEP_SIZE*qSin(qDegreesToRadians(theta));//用三角函數算出y的位移(要先將角度轉弧度)
    double dx=STEP_SIZE*qCos(qDegreesToRadians(theta));//用三角函數算出x的位移(要先將角度轉弧度)

    setPos(x()+dx,y()+dy);//移動子彈
}
