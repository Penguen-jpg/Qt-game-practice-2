#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "Tower.h"
class Game:public QGraphicsView
{
    Q_OBJECT
    public:
        Game();
        void setCursor(QString filename);//設定游標圖案
        void mouseMoveEvent(QMouseEvent *event);//滑鼠移動事件
        void mousePressEvent(QMouseEvent *event);//滑鼠點擊事件
        void createEnemy(int numberOfEnemies);//建造敵人
        void createRoad();//建造道路
        QGraphicsScene *scene;//場景
        QGraphicsPixmapItem  *cursor;//游標
        Tower *build;//要建造的塔
        QTimer *spawnTimer;
        int enemiesSpawned;//敵人目前生成數量
        int maxNumberOfEnemies;//最大敵人數量
        QList<QPointF> pointsToFollow;//敵人要經過的點
    public slots:
        void spawnEnemy();//生成敵人
};
#endif // GAME_H
