#ifndef BUILDGREENTOWER_H
#define BUILDGREENTOWER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
class BuildGreenTowerIcon: public QGraphicsPixmapItem
{
    public:
        BuildGreenTowerIcon(QGraphicsItem *parent=0);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
};
#endif // BUILDGREENTOWER_H
