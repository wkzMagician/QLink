#ifndef GAME4TEST_H
#define GAME4TEST_H

#include <QObject>
#include <QVector>
#include <QQueue>

#include "pos.h"
#include "config.h"

class Game4Test : public QObject
{
    Q_OBJECT
protected:
    //地图大小
    int M;
    int N;
    //地图
    QVector<QVector<Element>> map;
    //初始化地图
    void initMap();
    /*
     * 算法模块
     */
    //判断消除的辅助函数
    bool reachIn0Turn(const Pos &p1, const Pos &p2);
    Pos reachIn1Turn(const Pos &p1, const Pos &p2);
    QVector<Pos> reachIn2Turn(const Pos &p1, const Pos &p2);
    //越界判定
    bool outOfBoundary(const Pos &p);
    //判断不是方块
    bool isBox(const Pos &p);
    bool isBox(int x, int y);
public:
    /*下面是判断两个砖块能否消除的核心判定函数
     * 前两个参数是砖块的坐标
     * 最后的参数是是否将路径存入connectPath
     * 如果为否就仅作判断*/
    bool checkElimination(const Pos &p1, const Pos &p2);
    Game4Test(int m, int n);
    virtual ~Game4Test();
    //测试用导入地图
    void setMap();
};

#endif // GAME4TEST_H
