#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include <QPointF>
class Enemy:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    public:
        Enemy(QList<QPointF> pointsToFollow,QGraphicsItem *parent=0);
        void rotateToPoint(QPointF point);//轉向目的地
    public slots:
        void move_forward();//移動到目的地
    private:
        QList<QPointF> points;//存放目的地的座標
        QPointF destination;//目的地座標
        int point_index;//目前在哪個目的地
};

#endif // ENEMY_H
