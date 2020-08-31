#include "Tower.h"
#include "Bullet.h"
#include "Game.h"
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QTimer>
#include <QList>
#include "Enemy.h"
extern Game *game;

Tower::Tower(QGraphicsItem *parent):QObject(),QGraphicsPixmapItem(parent)
{
    //setPixmap(QPixmap(":/images/grey_tower.png"));//設定塔的圖片

    QVector<QPointF> points;//存放點座標的vector
    points<<QPointF(1,0)<<QPointF(2,0)<<QPointF(3,1)<<QPointF(3,2)<<QPointF(2,3)
          <<QPointF(1,3)<<QPointF(0,2)<<QPointF(0,1);//將點座標存入

    int SCALE_FACTOR=65;//縮放倍數
    for(int n=0;n<points.size();n++)//將每一點都放大65倍
    {
        points[n]*=SCALE_FACTOR;
    }

    QPolygonF polygon(points);//利用points建立一個多邊形
    attack_range=new QGraphicsPolygonItem(polygon,this);//利用polygon建造QGraphicsPolygonItem物件
    attack_range->setPen(QPen(Qt::DotLine));//將邊線設定為點

    QPointF poly_center(1.5,1.5);//polygon的中心座標
    poly_center*=SCALE_FACTOR;//放大65倍
    poly_center=mapToScene(poly_center);//將此座標對應到場景中
    QPointF tower_center(x()+44,y()+44);//塔的中心
    QLineF line(poly_center,tower_center);//用QLineF來算出兩個中心的座標差距
    attack_range->setPos(x()+line.dx(),y()+line.dy());//設定攻擊範圍

    QTimer *timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(acquire_target()));//連接timerc和acquire_target
    timer->start(1000);

    attack_destination=QPointF(800,0);//設定攻擊目標位置
}

double Tower::distanceTo(QGraphicsItem *item)
{
    QLineF line(pos(),item->pos());
    return line.length();
}

void Tower::fire()//攻擊
{
    Bullet *bullet=new Bullet();//建立子彈物件
    bullet->setPos(x()+44,y()+44);//設定子彈位置

    QLineF line(QPointF(x()+44,y()+44),attack_destination);//建立子彈到目標的線
    int angle=-1*line.angle();//乘上-1是為了順時針旋轉
    bullet->setRotation(angle);//旋轉子彈角度
    game->scene->addItem(bullet);//將子彈加入場景
}

void Tower::acquire_target()
{
    QList <QGraphicsItem *> colliding_items=attack_range->collidingItems();//存放撞到攻擊範圍的物件
    if(colliding_items.size()==1)//如果攻擊範圍內沒有敵人，則中斷
    {
        has_target=false;
        return;
    }

    double closest_distance=300.0;
    QPointF closest_point(0,0);
    for(int n=0;n<colliding_items.size();n++)
    {
        /*dynamic_cast會自動偵測是否可以轉型，如果可以就會直接轉，這裡是用來檢查
          colliding_items是否能變成敵人物件*/
        Enemy *enemy=dynamic_cast<Enemy *>(colliding_items[n]);
        if(enemy)//如果轉型成功，則進入
        {
            double this_distance=distanceTo(enemy);//到敵人的距離
            if(this_distance<closest_distance)//如果目前距離小於最小距離，則將資訊更新
            {
                closest_distance=this_distance;
                closest_point=colliding_items[n]->pos();
                has_target=true;
            }
        }
    }

    attack_destination=closest_point;//設定攻擊目標
    fire();//攻擊
}
