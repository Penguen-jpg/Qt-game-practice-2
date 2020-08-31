#include "Enemy.h"
#include <QTimer>
#include <qmath.h>
Enemy::Enemy(QList<QPointF> pointsToFollow,QGraphicsItem *parent)
{
    setPixmap((QPixmap(":/images/enemy.png")));//設定敵人圖片

    points=pointsToFollow;//輸入目的地
    point_index=0;//目的地index
    destination=points[0];//第一個目的地
    rotateToPoint(destination);//轉向第一個目的地

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move_forward()));//連接timer跟move_forward
    timer->start(150);//每0.15秒做一次
}

void Enemy::rotateToPoint(QPointF point)
{
    QLineF line(pos(),point);//建立目前位置與point的線
    setRotation(-1*line.angle());//順時間轉向point
}

void Enemy::move_forward()
{
    QLineF line(pos(),destination);//建立目前位置與destination的線(用來偵測是否已到達目的地)
    if(line.length()<5)//如果線的長度小於5，則代表到達目的地
    {
        point_index++;
        if(point_index>=points.size())//如果到達最後的目的地，則中斷
        {
           return;
        }
        destination=points[point_index];
        rotateToPoint(destination);
    }

    int STEP_SIZE=5;//每次移動距離
    double theta=rotation();//旋轉"角度"
    double dy=STEP_SIZE*qSin(qDegreesToRadians(theta));//用三角函數算出y的位移(要先將角度轉弧度)
    double dx=STEP_SIZE*qCos(qDegreesToRadians(theta));//用三角函數算出x的位移(要先將角度轉弧度)

    setPos(x()+dx,y()+dy);//移動敵人
}
