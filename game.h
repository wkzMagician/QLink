#pragma once
#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTimer>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QFile>
#include <QQueue>
#include <QVector>
#include <QDir>

#include "game4test.h"
#include "player.h"

class Game : public Game4Test
{
    Q_OBJECT
protected:
    const int createGap = 5; //生成道具的间隔,单位秒
    const int hintTime = 10; //提示时间

    /*
     * 游戏数据
     */
    //存储玩家
    Player* player1;
    //倒计时
    int time;
    //提示
    bool hint = false;
    //道具数
    int itemNum;
    //砖块数
    int numBox;

    /*
     * 初始化模块
     */
    //随机生成地图
    void generateRandomMap();
    //随机玩家位置
    virtual void initPlayer();

    /*
     * 与道具交互模块
     */
    //撞到箱子相关逻辑
    void checkBox(const Pos& p1, const Pos& p2, Player *player);
    //重排地图
    void shuffleMap();
    //设置提示
    virtual void setHint();
    //消除砖块
    virtual void eliminate();

    /*
     * 算法模块
     */
    //重排函数
    void shuffle(QVector<Element> &v);
    void shuffle(QVector<Pos> &v);
    //辅助函数：获得能走到的所有方块
    QVector<Pos> getReachableBox(const Pos& p);

    /*
     * 计时器
     */
    QTimer *timer;
    QTimer *createTimer;
    QTimer *hintTimer;
    int hintTimerLeft;
    void addTime(const int dt);
    void setTime(const int t);

public:
    Game(int m, int n, int _time, int _numBox);
    virtual ~Game();

    //人物移动逻辑
    virtual void move(const int dx, const int dy, const int playerID);
    
    /*下面是判断两个砖块能否消除的核心判定函数
     * 前两个参数是砖块的坐标
     * 最后的参数是是否将路径存入connectPath
     * 如果为否就仅作判断*/
    bool checkElimination(const Pos& p1, const Pos& p2, bool write);
    
    //判断地图是否可解
    virtual bool isSolvable();
    //计时器的控制
    void stopTimer();
    void startTimer();
    //获取给定坐标小方块的类型，用于显示地图
    Element getMapBlock(const int i, const int y);
    //是否处在提示下
    bool isHinted(){return hint;}
    //返回玩家的指针容器
    virtual const QVector<Player*> getPlayer();

    Pos hintBox[2]; //存储提示的方块，用于显示
    QVector<Pos>connectPath; //存储两个方块连接的通路，用于画线

private slots:
    void timeCount(); //计时
    void generateItem(); //生成道具
    void stopHint(); //Hint

protected slots:
    void updateScore(const int score, const int id); //分数

public slots:
    virtual void save();
    virtual void load();

Q_SIGNALS:
signals:
    void displayTime(int _time);
    void displayScore(int score, int id);
    void update(); //通知更新地图
    void displayMessage(const QString&); //通知显示信息
    void playSound(const QString&); //通知播放音效
    void endGame();
    void resize(const int, const int);
};

#endif // GAME_H
