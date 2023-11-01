#include "game4test.h"

Game4Test::Game4Test(int m, int n) : M(m), N(n)
{
    initMap();
}

Game4Test::~Game4Test(){}

bool Game4Test::checkElimination(const Pos &p1, const Pos &p2)
{
    //越界，不处理
    if(outOfBoundary(p1) || outOfBoundary(p2)) return false;
    //非砖块，不处理
    if(!isBox(p1) || !isBox(p2)) return false;
    //两个点相同，不处理
    if(p1 == p2) return false;
    //种类不同，不处理
    if(map[p1.x][p1.y] != map[p2.x][p2.y]) return false;
    //可直接到达
    if(reachIn0Turn(p1, p2)) return true;
    //可通过一次折弯到达
    Pos p;
    p = reachIn1Turn(p1, p2);
    if(p != Pos(-1, -1)) return true;
    //可通过两次折弯到达
    QVector<Pos> v = reachIn2Turn(p1, p2);
    if(!v.empty()) return true;
    return false;
}

void Game4Test::initMap()
{
    //地图初始化
    map.clear();
    map.resize(M);
    for (int i = 0; i < M; ++i) {
        map[i].resize(N);
    }
}

void Game4Test::setMap()
{
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            map[i][j] = static_cast<Element>(defaultMap[i][j]);
        }
    }
}

bool Game4Test::reachIn0Turn(const Pos &p1, const Pos &p2)
{
    if(p1.x == p2.x){ //横坐标相等
        int max = p1.y > p2.y ? p1.y : p2.y;
        int min = p1.y < p2.y ? p1.y : p2.y;
        for(int y = min + 1; y < max; ++y){
            //连线上有方块，不可达
            if(isBox(p1.x, y)) return false;
        }
        return true;
    }
    else if(p1.y == p2.y){ //纵坐标相等
        int max = p1.x > p2.x ? p1.x : p2.x;
        int min = p1.x < p2.x ? p1.x : p2.x;
        for(int x = min + 1; x < max; ++x){
            if(isBox(x, p1.y)) return false;
        }
        return true;
    }
    else return false;
}

Pos Game4Test::reachIn1Turn(const Pos &p1, const Pos &p2)
{
    //矩形另外的两个顶点
    Pos p3 = Pos(p1.x, p2.y);
    Pos p4 = Pos(p2.x, p1.y);
    //折点不是方块，且两条折线都可达
    if(!isBox(p3) && reachIn0Turn(p1, p3) && reachIn0Turn(p3, p2)) return p3;
    else if(!isBox(p4) && reachIn0Turn(p1, p4) && reachIn0Turn(p4, p2)) return p4;
    else return Pos(-1, -1);
}

QVector<Pos> Game4Test::reachIn2Turn(const Pos &p1, const Pos &p2)
{
    QQueue<Pos> pp;
    Pos p;
    //将所有p1能走到的坐标入队
    for(int i = 0; i < 4; ++i){
        p = p1 + Pos(dirt[i][0], dirt[i][1]);
        while(!outOfBoundary(p)){
            //是方块
            if(isBox(p)) break;
            pp.push_back(p);
            p += Pos(dirt[i][0], dirt[i][1]);
        }
    }

    Pos rp;
    while(!pp.empty()){
        //逐个出队
        p = pp.head();
        pp.pop_front();
        rp = reachIn1Turn(p, p2);
        //p和p2能用一次折线连接
        if(rp != Pos(-1, -1)){
            QVector<Pos> v;
            v << p1 << p << rp << p2;
            return v;
        }
    }
    //无法相连，返回空容器
    return QVector<Pos>();
}

bool Game4Test::outOfBoundary(const Pos &p)
{
    if (p.x < 0 || p.x >= M || p.y < 0 || p.y >= N)
        return true;
    else
        return false;
}

bool Game4Test::isBox(const Pos &p)
{
    return isBox(p.x, p.y);
}

bool Game4Test::isBox(int x, int y)
{
    switch (map[x][y]) {
    case Box1:
    case Box2:
    case Box3:
    case Box4:
    case Box5:
    case Box6:
    case Box7:
    case Box8:
        return true;
        break;
    default:
        return false;
    }
}
