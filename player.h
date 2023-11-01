#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include "pos.h"
#include "config.h"

class Player : public QObject
{
    Q_OBJECT
private:
    Pos pos; //位置
    int id; //玩家ID
    int score = 0; //分数
    QVector<Pos> boxTriggered; //激活的砖块
    bool freeze = false; //是否被冻结
    bool dizzy = false; //是否被眩晕
    bool face = true; //朝右

public:
    Player(int ID);

    //激活砖块
    void setBoxTriggered(const Pos &_pos);
    void clearBoxTriggered(){boxTriggered.clear();}
    const QVector<Pos> getBoxTriggered(){return boxTriggered;}

    //坐标相关  
    int PosX()const{return pos.x;}
    int PosY()const{return pos.y;}
    Pos getPos()const{return pos;}
    void setPosX(const int _x){pos.x = _x;}
    void setPosY(const int _y){pos.y = _y;}
    void setPos(const int _x, const int _y){pos.x = _x; pos.y = _y;}
    void setPos(const Pos &p){pos = p;}

    //分数相关
    void addScore(int value);
    void setScore(int value);
    int getScore()const{return score;}

    //状态相关
    void Freeze(const int freezeTime);
    bool isFrozen()const{return freeze;}
    void setDizzy(const int dizzyTime);
    bool isDizzy()const{return dizzy;}

    //朝向
    void setFace(const bool flag){face = flag;}
    bool getFace()const{return face;}

public slots:
    void unfreeze();
    void undizzy();

Q_SIGNALS:
signals:
    void updateScore(int, int);
    void checkBox(Pos, Pos, Player*); //检查砖块激发能否消除
    void update();
};

#endif // PLAYER_H
