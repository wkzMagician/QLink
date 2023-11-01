#include "tpgame.h"

TPGame::TPGame(int m, int n, int _time, int _numBox) : Game(m, n, _time, _numBox)
{
    //双人游戏特色：第二名玩家
    player2 = new Player(1);
    connect(player2, &Player::checkBox, this, &TPGame::checkBox);
    connect(player2, &Player::updateScore, this, &TPGame::updateScore);
    connect(player2, &Player::update, this, &Game::update);
    this->initPlayer();
    //额外道具
    itemNum = 5;
}

TPGame::~TPGame()
{
    //多释放玩家2
    delete player2;
}

void TPGame::initPlayer()
{
    //多初始化玩家2
    int x = rand() % M;
    int y = rand() % N;
    player2->setPos(x, y);
    map[x][y] = Player2;
    //清空旁边砖块
    for(int i = 0; i < 4; ++i){
        Pos p = player2->getPos() + Pos(dirt[i][0], dirt[i][1]);
        if(!outOfBoundary(p)){
            map[p.x][p.y] = None;
        }
    }
    //遍历能走到的砖块，如果砖块之间消不掉，就清除砖块
    QVector<Pos> box = getReachableBox(player2->getPos());
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

void TPGame::setHint()
{
    //获得能够走到的所有方块
    QVector<Pos> box = getReachableBox(player1->getPos());
    //加上玩家2能够走到的所有方块
    box << getReachableBox(player2->getPos());

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

void TPGame::eliminate()
{
    connectPath.clear(); //清空折线
    QVector<Pos> boxes = player1->getBoxTriggered();
    if(boxes.size() >= 2){ //激活的方块达两个（即还未消除）
        for(const auto box : boxes)
            map[box.x][box.y] = None; //地图中消除
        player1->clearBoxTriggered(); //玩家的boxTriggered置空
    }
    //对玩家2同样操作
    boxes = player2->getBoxTriggered();
    if(boxes.size() >= 2){
        for(const auto box : boxes)
            map[box.x][box.y] = None;
        player2->clearBoxTriggered();
    }
    //更新显示
    emit update();
    //检查地图是否可解
    if(!isSolvable()) emit endGame();
}

void TPGame::move(int dx, int dy, int playerID)
{
    Player *player = (playerID == 0) ? player1 : player2;
    //如果冻结，则直接返回
    if(player->isFrozen()) return;
    //如果dizzy，则方向取反
    Pos newPos;
    if(!player->isDizzy()) newPos = player->getPos() + Pos(dx, dy);
    else newPos = player->getPos() - Pos(dx, dy);
    //翻转判定
    if(!player->isDizzy()){
        if(dx < 0) player->setFace(false);
        else if(dx > 0) player->setFace(true);
    }
    else{
        if(dx > 0) player->setFace(false);
        else if(dx < 0) player->setFace(true);
    }
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
    {
        Player* anotherPlayer = (playerID == 1) ? player1 : player2;
        //查找对方是否已经点亮该砖块
        int index = anotherPlayer->getBoxTriggered().indexOf(newPos);
        //找到，则不处理
        if(index != -1) return;
        player->setBoxTriggered(newPos); //否则点亮该砖块
        return;
        break;
    }
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
    case Freeze:
    {
        Player* anotherPlayer = (playerID == 1) ? player1 : player2;
        anotherPlayer->Freeze(freezeTime);
        emit playSound("Item");
        break;
    }
    case Dizzy:
    {
        Player* anotherPlayer = (playerID == 1) ? player1 : player2;
        anotherPlayer->setDizzy(dizzyTime);
        emit playSound("Item");
        break;
    }
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

bool TPGame::isSolvable()
{
    //获得能够走到的所有方块
    QVector<Pos> box = getReachableBox(player1->getPos());
    box << getReachableBox(player2->getPos());

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

const QVector<Player *> TPGame::getPlayer()
{
    QVector<Player*> players;
    players << player1 << player2;
    return players;
}

void TPGame::save()
{
    QJsonObject json;
    QJsonArray mapData;

   json["time"] = time;
   json["player1Score"] = player1->getScore();
    json["player2Score"] = player2->getScore();
    //玩家坐标
    json["player1PosX"] = player1->PosX();
    json["player1PosY"] = player1->PosY();
    json["player2PosX"] = player2->PosX();
    json["player2PosY"] = player2->PosY();
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
    file.setFileName("dual.json");

   if (file.open(QIODevice::WriteOnly)) {
       file.write(data);
       file.close();
         emit displayMessage("存档已保存");
   } else {
       qDebug() << "Failed to save game";
   }
}

void TPGame::load()
{
    QFile file;
    file.setFileName("dual.json");
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
            player2->setScore(json["player2Score"].toInt());
            player2->setPosX(json["player2PosX"].toInt());
            player2->setPosY(json["player2PosY"].toInt());

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
