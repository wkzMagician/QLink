#include "game.h"

Game::Game(int m, int n, int _time, int _numBox) : Game4Test(m, n), time(_time), numBox(_numBox)
{
    itemNum = 3;

    generateRandomMap(); //随机生成地图

    //玩家初始化
    player1 = new Player(0);
    connect(player1, &Player::checkBox, this, &Game::checkBox);
    connect(player1, &Player::updateScore, this, &Game::updateScore);
    connect(player1, &Player::update, this, &Game::update);
    Game::initPlayer(); //随机玩家位置

    //计时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::timeCount);
    timer->start(1000);

    createTimer = new QTimer(this);
    connect(createTimer, &QTimer::timeout, this, &Game::generateItem);
    createTimer->start(createGap * 1000);

    hintTimer = new QTimer(this);
    connect(hintTimer, &QTimer::timeout, this, &Game::stopHint);
}

Game::~Game()
{
    delete player1;
    delete timer;
    delete createTimer;
    delete hintTimer;
}

void Game::generateRandomMap()
{
    QVector<Element> v;
    //先有序生成砖块
    for (int i = 0; i < M * N * 2 / 3; ++i) {
        int x = rand() % numBox;
        switch (x)
        {
        case 0:
            v.push_back(Box1);
            break;
        case 1:
            v.push_back(Box2);
            break;
        case 2: 
            v.push_back(Box3);
            break;
        case 3:
            v.push_back(Box4);
            break;
        case 4:
            v.push_back(Box5);
            break;
        case 5:
            v.push_back(Box6);
            break;
        case 6:
            v.push_back(Box7);
            break;
        case 7:
            v.push_back(Box8);
            break;
        default:
            break;
        }
    }
    //剩下的位置填充空地
    for (int i = M * N * 2 / 3; i < M * N; ++i)
        v.push_back(None);
    //重排，达到随机效果
    shuffle(v);
    //将结果存入map
    for (int i = 0; i < M * N; ++i) {
        int x = i % M;
        int y = i / M;
        map[x][y] = v[i];
    }
}

void Game::initPlayer()
{
    int x = rand() % M;
    int y = rand() % N;
    player1->setPos(x, y);
    map[x][y] = Player1;
    //清空旁边砖块
    for(int i = 0; i < 4; ++i){
        Pos p = player1->getPos() + Pos(dirt[i][0], dirt[i][1]);
        if(!outOfBoundary(p)){
            map[p.x][p.y] = None;
        }
    }
    //遍历能走到的砖块，如果砖块之间消不掉，就清除砖块
    QVector<Pos> box = getReachableBox(player1->getPos());
    QVector<Pos>::iterator head;
    while(!box.empty()){
        head = box.begin();
        for(QVector<Pos>::iterator b = head + 1; b < box.end(); ++b){
            if(checkElimination(*head, *b, false)) return;
        }
        map[head->x][head->y] = None;
        box.pop_front();
    }
}


//简单算法
void Game::shuffle(QVector<Element> &v)
{
    //Fisher-Yates 洗牌算法
    int size = v.size();
    for (int i = 0; i < size; i++)
    {
        int j = rand() % size;

        //不是玩家
        if(v[i] != Player1 && v[i] != Player2 && v[j] != Player1 && v[j] != Player2)
            v.swapItemsAt(i, j); //随机交换
    }
}

void Game::shuffle(QVector<Pos> &v)
{
    //Fisher-Yates 洗牌算法
    int size = v.size();
    for (int i = 0; i < size; i++)
    {
        int j = rand() % size;
        v.swapItemsAt(i, j); //随机交换
    }
}


//与道具交互模块
void Game::checkBox(const Pos& p1, const Pos& p2, Player *player)
{
    //砖块type不同，则玩家的boxTriggered置空
    if(map[p1.x][p1.y] != map[p2.x][p2.y]){
        player->clearBoxTriggered();
        return;
    }

    //否则执行消除判定
    if(!checkElimination(p1, p2, true)){
        //不能消除，玩家的boxTriggered置空
        player->clearBoxTriggered();
        return;
    }

    //可消除
    //一段时间后消除
    QTimer::singleShot(150, this, &Game::eliminate);
    //更新得分
    player->addScore(5);
    //音效
    emit playSound("Ring");
    //若有提示的砖块被消除了至少一个，则重新设置Hint
    if(p1 == hintBox[0] || p1 == hintBox[1] || p2 == hintBox[0] || p2 == hintBox[1]){
        if(hint) {
            QTimer::singleShot(150, this, &Game::setHint);
        }
    }

    emit update(); //更新显示
}

void Game::shuffleMap()
{
    // 将二维容器转换为一维容器
    QVector<Element> v;
    for (const auto& row : map)
        {
            for (const auto& col : row)
            {
                v.append(col);
            }
        }

    //重排
    shuffle(v);

    //将一维容器转换为二维容器（重新设置map）
    map.clear();
    for (int i = 0; i < M; i++)
    {
        QVector<Element> v2;
        for (int j = 0; j < N; j++)
        {
            v2.append(v[i * M + j]);
        }
        map.append(v2);
    }

    //由于重排，要重新设置Hint
    if(hint) setHint();

    emit update(); //更新显示
}

void Game::setHint()
{
    //获得能够走到的所有方块
    QVector<Pos> box = getReachableBox(player1->getPos());

    shuffle(box); //重排,以达到随机选择的效果

    //依次检查两个砖块能否互相消除
    QVector<Pos>::iterator head;
    while(!box.empty()){
        head = box.begin();
        for(QVector<Pos>::iterator b = head + 1; b < box.end(); ++b){
            if(checkElimination(*head, *b, false)){
                //将结果存在hintBox数组中，以待显示
                hintBox[0] = *head;
                hintBox[1] = *b;
                emit update(); //更新显示
                return;
            }
        }
        box.pop_front();
    }
    //不存在可以提示的砖块
    hintBox[0] = Pos(-1, -1);
    hintBox[1] = Pos(-1, -1);
    emit update(); //更新显示
}

void Game::eliminate()
{
    connectPath.clear(); //清空折线
    QVector<Pos> boxes = player1->getBoxTriggered();
    if(boxes.size() >= 2){ //激活的方块达两个（即还未消除）
        for(const auto box : boxes)
            map[box.x][box.y] = None; //地图中消除
        player1->clearBoxTriggered(); //玩家的boxTriggered置空
    }
    //更新显示
    emit update();
    //检查地图是否可解
    if(!isSolvable()) emit endGame();
}


//算法模块
bool Game::checkElimination(const Pos &p1, const Pos &p2, bool write)
{
    //种类不同，不处理
    if(map[p1.x][p1.y] != map[p2.x][p2.y]) return false;
    //其它异常情况都排除了
    //write为true时，将折线写入connectPath
    if(write) connectPath.clear();
    //在同一条直线上可到达
    if(reachIn0Turn(p1, p2)){
        if(write){
            connectPath << p1 << p2;
        }
        return true;
    }
    //可通过一次折弯到达
    Pos p;
    p = reachIn1Turn(p1, p2);
    if(p != Pos(-1, -1)){
        if(write){
            connectPath << p1 << p << p2;
        }
        return true;
    }
    //可通过两次折弯到达
    QVector<Pos> v = reachIn2Turn(p1, p2);
    if(!v.empty()){
        if(write) connectPath = v;
        return true;
    }
    return false;
}

bool Game::isSolvable()
{
    //获得能够走到的所有方块
    QVector<Pos> box = getReachableBox(player1->getPos());

    //依次检查两个砖块能否互相消除
    QVector<Pos>::iterator head;
    while(!box.empty()){
        head = box.begin();
        for(QVector<Pos>::iterator b = head + 1; b < box.end(); ++b){
            if(checkElimination(*head, *b, false)) return true;
        }
        box.pop_front();
    }
    return false;
}

QVector<Pos> Game::getReachableBox(const Pos &p)
{
    //获得能够走到的所有方块
    //类似于满水填充法
    //这样更符合实际，不会出现有方块能够连接但人物实际无法消除的情况
    QVector<Pos> box;
    QQueue<Pos> spaceQueue; //队列，用于广度优先搜索
    //存储已经访问过的空格
    QVector<Pos> visited;
    visited.push_back(p);
    spaceQueue.push_back(p);
    while (!spaceQueue.empty()){
        Pos p = spaceQueue.front();
        spaceQueue.pop_front();
        //向四个方向搜索
        for(int i = 0; i < 4; ++i){
            Pos np = p + Pos(dirt[i][0], dirt[i][1]);
            //越界
            while(!outOfBoundary(np)){
                //是方块且不在box中
                if(isBox(np)){
                    //箱子没访问过，则加入box
                    if(!box.contains(np)) box.push_back(np);
                    break; //撞到箱子，不再继续向该方向前进
                }
                //已经访问过，则访问下一个方向
                if(visited.contains(np)) break;
                spaceQueue.push_back(np);
                visited.push_back(np); //标记访问过
                //继续向该方向前进
                np += Pos(dirt[i][0], dirt[i][1]);
            }
        }
    }
    return box;
}


//移动模块
void Game::move(int dx, int dy, int playerID)
{
    Player *player = player1;
    //翻转判定
    if(dx < 0) player->setFace(false);
    else if(dx > 0) player->setFace(true);
    //新位置
    Pos newPos = player->getPos() + Pos(dx, dy);
    //越界
    if (outOfBoundary(newPos)) return;

    switch (map[newPos.x][newPos.y]) {
    case Box1:
    case Box2:
    case Box3:
    case Box4:
    case Box5:
    case Box6:
    case Box7:
    case Box8:
        player->setBoxTriggered(newPos);
        return;
        break;
    case Clock:
        addTime(30);
        emit playSound("Item");
        break;
    case Shuffle:
        shuffleMap();
        emit playSound("Item");
        break;
    case Hint: //开始提示
        hintTimer->start(hintTime * 1000);
        emit playSound("Item");
        hint = true;
        setHint();
        break;
    case Player1: //双人模式下，不允许玩家1走到玩家2的位置
        if(playerID == 1) return;
        break;
    case Player2:
        if(playerID == 0) return;
        break;
    default:
        emit playSound("Walk");
        break;
    }

    //更新地图
    map[player->PosX()][player->PosY()] = None;
    map[newPos.x][newPos.y] = static_cast<Element>(playerID + Player1);
    player->setPos(newPos); //更新玩家位置

    emit update(); //更新显示
}


//计时模块
void Game::addTime(int dt)
{
    setTime(time + dt);
}

void Game::setTime(int t)
{
    time = t;
    if(time < 0) { //时间到，游戏结束
        emit endGame();
        return;
    }
    emit displayTime(time); //更新显示
}

void Game::timeCount()
{
    addTime(-1); //每秒减一
}

void Game::stopTimer()
{
    timer->stop();
    createTimer->stop();
    hintTimerLeft = hintTimer->interval();
    hintTimer->stop();
}

void Game::startTimer()
{
    timer->start(1000);
    createTimer->start(createGap * 1000);
    hintTimer->start(hintTimerLeft);
}


// 信号槽模块
void Game::generateItem()
{
    //找空地
    QVector<Pos> empty;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if(map[i][j] == None)
                empty.push_back(Pos(i, j));
        }
    }

    //随机选择一个空地
    shuffle(empty);
    Pos p = empty.front();
    //随机生成道具
    Element item = static_cast<Element>(rand() % itemNum + Clock);
    map[p.x][p.y] = item;
    emit update();
}

void Game::updateScore(int score, int id)
{
    emit displayScore(score, id);
}

void Game::stopHint()
{
    hint = false;
    emit update();
}


// 保存与读取模块
void Game::save()
{
    QJsonObject json;
    QJsonArray mapData;

    json["time"] = time;
    json["player1Score"] = player1->getScore();
    //玩家坐标
    json["player1PosX"] = player1->PosX();
    json["player1PosY"] = player1->PosY();
    //将map转换为json数组
    for (const auto& row : map) {
        QJsonArray rowData;
        //每一个row是所有相同x的元素
        //其实对应着地图中的一列
        for (const auto& col : row) {
            rowData.append(col);
        }
        mapData.append(rowData);
    }
   json["map"] = mapData;
   json["hint"] = hint;
   json["numBox"] = numBox;
    //将json对象转换为字符串
   QJsonDocument doc(json);
   QByteArray data = doc.toJson();

    //保存到文件
   QFile file;
    file.setFileName("single.json");

   if (file.open(QIODevice::WriteOnly)) {
       file.write(data);
       file.close();
         emit displayMessage("存档已保存");
   } else {
       qDebug() << "Failed to save game";
   }
}

void Game::load()
{
    QFile file;
    file.setFileName("single.json");
    if (file.open(QIODevice::ReadOnly)) {
        //读取文件
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (!doc.isNull() && doc.isObject()) {
            //解析json对象
            QJsonObject json = doc.object();
            //更新游戏数据
            setTime(json["time"].toInt());
            player1->setScore(json["player1Score"].toInt());
            player1->setPosX(json["player1PosX"].toInt());
            player1->setPosY(json["player1PosY"].toInt());

            //获取地图数据
            QJsonArray mapData = json["map"].toArray();
            //设置地图的长与宽
            N = mapData.size();
            M = mapData[0].toArray().size();
            //地图重新初始化
            initMap();
            emit resize(M, N); // 更新界面大小
            int index = 0;
            for (const QJsonValue& rowValue : mapData) {
                QJsonArray rowData = rowValue.toArray();
                for (const QJsonValue& colValue : rowData) {
                    //计算得到地图的坐标
                    //由于存储时按照相同的x作为每个子列表
                    //所以这里的每一列其实是地图中每一行
                    int y = index % N;
                    int x = index / N;
                    //更新地图
                    map[x][y] = static_cast<Element>(colValue.toInt());
                    ++index;
                }
            }

            hint = json["hint"].toBool();
            if(hint) setHint();
            numBox = json["numBox"].toInt();

            emit displayMessage("存档已读取");
        } else {
            qDebug() << "Failed to parse game data";
        }
    } else {
        qDebug() << "Failed to load game";
    }

    emit update(); //更新显示
}


Element Game::getMapBlock(int i, int j)
{
    return map[i][j];
}

const QVector<Player *> Game::getPlayer()
{
    QVector<Player*> p;
    p << player1;
    return p;
}
