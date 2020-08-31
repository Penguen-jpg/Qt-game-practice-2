#ifndef BROWNTOWER_H
#define BROWNTOWER_H
#include "Tower.h"
class GreyTower:public Tower
{
    Q_OBJECT
    public:
        GreyTower(QGraphicsItem *parent=0);
        void fire();
    public slots:
        void acquire_target();
};

#endif // BROWNTOWER_H
