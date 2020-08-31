#ifndef TOWER_H
#define TOWER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>
class Tower:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    public:
        Tower(QGraphicsItem *parent=0);
        double distanceTo(QGraphicsItem *item);//算出物件之間的距離
        virtual void fire();//攻擊(可讓子類別改寫)
    public slots:
        void acquire_target();//找到攻擊目標
    protected:
        QGraphicsPolygonItem *attack_range;//攻擊範圍
        QPointF attack_destination;//攻擊目標的位置
        bool has_target;//是否找到目標
};

#endif // TOWER_H
