#ifndef BUILDGREYTOWERICON_H
#define BUILDGREYTOWERICON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
class BuildGreyTowerIcon: public QGraphicsPixmapItem
{
    public:
        BuildGreyTowerIcon(QGraphicsItem* parent=0);
        void mousePressEvent(QGraphicsSceneMouseEvent* event);
};
#endif // BUILDGREYTOWERICON_H
