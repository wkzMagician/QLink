#pragma once
#ifndef POS_H
#define POS_H

#include <QDebug>

class Pos //位置类
{
    friend Pos operator+(const Pos &p1, const Pos &p2);
    friend Pos operator-(const Pos &p1, const Pos &p2);
    friend Pos& operator+=(Pos &p1, const Pos &p2);
    friend bool operator==(const Pos &p1, const Pos &p2);
    friend bool operator!=(const Pos &p1, const Pos &p2);
    friend QDebug operator<<(QDebug debug, const Pos& pos);
public:
    int x;
    int y;
    //构造函数
    Pos(int _x, int _y):x(_x), y(_y){}
    Pos(){}
};

#endif // POS_H
