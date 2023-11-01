#ifndef TPGAME_H
#define TPGAME_H

#include "game.h"

//TPGame是双人游戏类，继承于Game类
class TPGame : public Game
{
Q_OBJECT
private:
    //第二名玩家
    Player* player2;
    //双人模式独有的道具
    const int freezeTime = 3;
    const int dizzyTime = 10;

    /*
    重写的方法
    */
    //随机玩家位置
    virtual void initPlayer() override;
    //设置提示
    virtual void setHint() override;
    //消除砖块
    virtual void eliminate() override;

public:
    TPGame(int m, int n, int _time, int _numBox);
    virtual ~TPGame();

    //人物移动逻辑
    virtual void move(const int dx, const int dy, const int playerID) override;
    
    //判断地图是否可解
    virtual bool isSolvable() override;
    //返回玩家的指针容器
    virtual const QVector<Player*> getPlayer()override;

public slots:
    virtual void save()override;
    virtual void load()override;
};

#endif // TPGAME_H
