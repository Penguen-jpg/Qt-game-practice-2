#include "Game.h"
#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"
#include "BuildGreyTowerIcon.h"
#include "BuildGreenTowerIcon.h"
#include "BuildRedTowerIcon.h"
#include <QTimer>
#include <QGraphicsLineItem>
#include <QPen>

Game::Game()
{
    scene=new QGraphicsScene();//建立場景物件
    scene->setSceneRect(0,0,800,600);//設定場景大小
    setScene(scene);//將scene指定為場景

    cursor=nullptr;//初始化游標
    build=nullptr;//初始化
    setMouseTracking(true);//啟動滑鼠追蹤

    setFixedSize(800,600);//設定視窗大小
    //關閉卷軸
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //初始化
    spawnTimer=new QTimer(this);
    enemiesSpawned=0;
    maxNumberOfEnemies=0;
    pointsToFollow<<QPointF(800,0)<<QPointF(450,450)<<QPointF(0,600);

    //建造敵人
    createEnemy(5);

    //建立道路
    createRoad();

    //建立建造功能
    BuildGreyTowerIcon *gt=new BuildGreyTowerIcon();
    BuildGreenTowerIcon *grt=new BuildGreenTowerIcon;
    BuildRedTowerIcon *rt=new BuildRedTowerIcon();
    grt->setPos(x(),y()+100);
    rt->setPos(x(),y()+200);

    //將建造功能加入場景
    scene->addItem(gt);
    scene->addItem(grt);
    scene->addItem(rt);
}

void Game::setCursor(QString filename)
{
    if(cursor)//如果有游標，則刪除現在的游標
    {
        scene->removeItem(cursor);
        delete cursor;
    }
    cursor=new QGraphicsPixmapItem();//建立新游標
    cursor->setPixmap(QPixmap(filename));//設定游標圖片
    scene->addItem(cursor);//將游標加入場景
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if(cursor)//如果有鼠標，則將鼠標移動到目前指的位置
    {
        cursor->setPos(event->pos());
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if(build)//如果目前正在建造(預設)
    {
        //檢查是否重疊
        QList<QGraphicsItem *> items=cursor->collidingItems();//存放游標碰到的物件
        for(int n=0;n<items.size();n++)
        {
            if((Tower*)items[n])//如果碰到的是塔且與游標重疊，則中斷(不可建造)
            {
                return;
            }
        }
        scene->addItem(build);//將塔加入場景
        build->setPos(event->pos());//將圖示跟著游標移動
        cursor=nullptr;
        build=nullptr;
    }else//如果沒有，就直接將event傳下去
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void Game::createRoad()
{
    for(int n=1;n<pointsToFollow.size();n++)
    {
        QLineF line(pointsToFollow[n-1],pointsToFollow[n]);//建造兩點間的線
        QGraphicsLineItem *lineItem=new QGraphicsLineItem(line);//建立QGraphicsLineItem物件

        QPen pen;//建立QPen物件
        pen.setWidth(15);
        pen.setColor(Qt::darkGray);
        lineItem->setPen(pen);//套用pen

        scene->addItem(lineItem);//將線加入場景
    }
}

void Game::createEnemy(int numberOfEnemies)
{
    enemiesSpawned=0;
    maxNumberOfEnemies=numberOfEnemies;//更新資料
    connect(spawnTimer,SIGNAL(timeout()),this,SLOT(spawnEnemy()));//連接spawnTimer和spawnEnemy
    spawnTimer->start(1000);//每1秒生成一隻
}

void Game::spawnEnemy()
{
    //生成敵人
    Enemy *enemy=new Enemy(pointsToFollow);
    enemy->setPos(pointsToFollow[0]);
    scene->addItem(enemy);

    //更新資料
    enemiesSpawned++;

    if(enemiesSpawned>=maxNumberOfEnemies)//如果已生成所有敵人，則切斷連接
    {
        spawnTimer->disconnect();
    }
}
