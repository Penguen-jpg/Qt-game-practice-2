#include "GreyTower.h"
#include <QTimer>
#include "Bullet.h"
#include "Game.h"
extern Game *game;

GreyTower::GreyTower(QGraphicsItem *parent)
{
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(acquire_target()));
    timer->start(1000);
}

void GreyTower::fire()
{
    Bullet *bullet=new Bullet();//建立子彈物件
    bullet->setPos(x()+44,y()+44);//設定子彈位置

    QLineF line(QPointF(x()+44,y()+44),attack_destination);//建立子彈到目標的線
    int angle=-1*line.angle();//乘上-1是為了順時針旋轉
    bullet->setRotation(angle);//旋轉子彈角度
    game->scene->addItem(bullet);//將子彈加入場景
}

void GreyTower::acquire_target()
{
    Tower::acquire_target();
}

