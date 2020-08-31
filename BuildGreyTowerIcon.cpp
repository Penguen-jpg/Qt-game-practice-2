#include "BuildGreyTowerIcon.h"
#include "Game.h"
#include "GreyTower.h"
extern Game * game;

BuildGreyTowerIcon::BuildGreyTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/build_grey.png"));
}

void BuildGreyTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (!game->build)
    {
        game->build=new GreyTower();
        game->setCursor(QString(":/images/grey_tower.png"));
    }
}
