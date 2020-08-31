#include "GreenTower.h"
#include <QTimer>
#include "Bullet.h"
#include "Game.h"
extern Game * game;

GreenTower::GreenTower(QGraphicsItem *parent)
{
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(acquire_target()));
    timer->start(1000);
}

void GreenTower::fire()
{
    // 建立子彈物件
    Bullet *bullet1=new Bullet();
    Bullet *bullet2=new Bullet();
    Bullet *bullet3=new Bullet();

    //設定子彈圖片
    bullet1->setPixmap(QPixmap(":/images/bullet.png"));
    bullet2->setPixmap(QPixmap(":/images/bullet.png"));
    bullet3->setPixmap(QPixmap(":/images/bullet.png"));

    //設定子彈位置
    bullet1->setPos(x()+44,y()+44);
    bullet2->setPos(x()+44,y()+44);
    bullet3->setPos(x()+44,y()+44);

    QLineF line(QPointF(x()+44,y()+44),attack_destination);
    int angle=-1*line.angle();

    //設定子彈角度
    bullet1->setRotation(angle);
    bullet2->setRotation(angle+10);
    bullet3->setRotation(angle-10);

    //將子彈加入場景
    game->scene->addItem(bullet1);
    game->scene->addItem(bullet2);
    game->scene->addItem(bullet3);
}

void GreenTower::aquire_target()
{
    Tower::acquire_target();
}
