#include "BuildRedTowerIcon.h"
#include "Game.h"
#include "RedTower.h"
extern Game * game;

BuildRedTowerIcon::BuildRedTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/build_red.png"));
}

void BuildRedTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (!game->build)
    {
        game->build=new RedTower();
        game->setCursor(QString(":/images/red_tower.png"));
    }
}
