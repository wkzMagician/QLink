#include "gamewidget.h"

GameWidget::~GameWidget()
{
    delete timeLabel;
    delete player1ScoreLabel;
    delete player2ScoreLabel;
    delete messageBox;
    delete loadButton;
    delete saveButton;
    delete pauseButton;
    delete returnButton;
    delete continueButton;
    delete audioManager;
}

GameWidget::GameWidget(int m, int n, int _time, int numBox, bool _dual, QWidget *parent) :
    QWidget(parent), M(m), N(n)
{
    //背景音乐
    audioManager = new AudioManager;
    audioManager->playBGM();
    //游戏逻辑设置
    if(!_dual) game = new Game(m, n, _time, numBox);
    else game = new TPGame(m, n, _time, numBox);

    //信号
    connect(game, &Game::playSound, audioManager, &AudioManager::playSoundEffect);
    connect(game, &Game::endGame, this, &GameWidget::endGame);
    connect(game, &Game::displayTime, this, &GameWidget::displayTime);
    connect(game, &Game::displayScore, this, &GameWidget::displayScore);
    connect(game, &Game::update, this, QOverload<>::of(&GameWidget::update));
    connect(game, &Game::displayMessage, this, &GameWidget::displayMessage);
    connect(game, &Game::resize, this, &GameWidget::resize);

    //窗口设置
    setWindowTitle("Game");
    setAutoFillBackground(true);
    setFocusPolicy(Qt::StrongFocus);
    setMinimumSize((M + 5) * BLOCK_SIZE, N * BLOCK_SIZE);

    initLabel(); //标签显示
    initButton(); //按钮设置

    displayTime(_time);
    displayScore(0, 0);
    displayScore(0, 1);

    update(); //更新
    if(!game->isSolvable()) endGame(); //判断是否可解
}

void GameWidget::initLabel()
{
    //标签设置
    timeLabel = new QLabel(this);
    timeLabel->setFont(QFont("Arial", 16));
    player1ScoreLabel = new QLabel(this);
    player1ScoreLabel->setFont(QFont("Arial", 16));
    player2ScoreLabel = new QLabel(this);
    player2ScoreLabel->setFont(QFont("Arial", 16));
    messageBox = new QLabel(this);
    messageBox->setFont(QFont("Arial", 16));
    messageBox->setStyleSheet("color: red;"); //红色字体
    //位置
    timeLabel->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, 0, BLOCK_SIZE * 4, BLOCK_SIZE);
    player1ScoreLabel->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 1, BLOCK_SIZE * 4, BLOCK_SIZE);
    player2ScoreLabel->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 2, BLOCK_SIZE * 4, BLOCK_SIZE);
    messageBox->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 6, BLOCK_SIZE * 4, BLOCK_SIZE);
}

void GameWidget::initButton()
{
    //构造
    pauseButton = new QPushButton(this);
    pauseButton->setFont(QFont("Arial", 16));
    continueButton = new QPushButton(this);
    continueButton->setFont(QFont("Arial", 16));
    saveButton = new QPushButton(this);
    saveButton->setFont(QFont("Arial", 16));
    loadButton = new QPushButton(this);
    loadButton->setFont(QFont("Arial", 16));
    returnButton = new QPushButton(this);
    returnButton->setFont(QFont("Arial", 16));
    //文字
    pauseButton->setText("暂停");
    continueButton->setText("继续");
    saveButton->setText("存档");
    loadButton->setText("读档");
    returnButton->setText("回到主菜单");
    //位置
    pauseButton->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 3, BLOCK_SIZE * 2, BLOCK_SIZE);
    continueButton->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 3, BLOCK_SIZE * 2, BLOCK_SIZE);
    saveButton->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 4, BLOCK_SIZE * 1.5, BLOCK_SIZE);
    loadButton->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE * 3, BLOCK_SIZE * 4, BLOCK_SIZE * 1.5, BLOCK_SIZE);
    returnButton->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 5, BLOCK_SIZE * 3, BLOCK_SIZE);
    //有些按钮暂不显示
    continueButton->hide();
    saveButton->hide();
    loadButton->hide();
    returnButton->hide();
    //信号的连接
    connect(pauseButton, &QPushButton::clicked, this, &GameWidget::pauseGame);
    connect(continueButton, &QPushButton::clicked, this, &GameWidget::continueGame);
    connect(saveButton, &QPushButton::clicked, game, &Game::save);
    connect(loadButton, &QPushButton::clicked, game, &Game::load);
    connect(returnButton, &QPushButton::clicked, this, &GameWidget::returnToMain);
}


void GameWidget::keyPressEvent(QKeyEvent *event)
{
    if(paused) return; //暂停时不响应按键
    //禁用粘滞键
    if(event->isAutoRepeat()) return;

    switch (event->key()) {
    case Qt::Key_Up:
        game->move(0, -1, 0);
        break;
    case Qt::Key_Down:
        game->move(0, 1, 0);
        break;
    case Qt::Key_Right:
        game->move(1, 0, 0);
        break;
    case Qt::Key_Left:
        game->move(-1, 0, 0);
        break;
    case Qt::Key_W:
        game->move(0, -1, 1);
        break;
    case Qt::Key_S:
        game->move(0, 1, 1);
        break;
    case Qt::Key_D:
        game->move(1, 0, 1);
        break;
    case Qt::Key_A:
        game->move(-1, 0, 1);
        break;
    default:
        break;
    }
}

void GameWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // 绘制背景矩形
    QRect targetRect(0, 0, M * BLOCK_SIZE, N * BLOCK_SIZE); // 设置矩形的位置和大小
    painter.fillRect(targetRect, Qt::cyan); // 设置矩形的背景色为蓝色
    painter.end();

    //绘制地图
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            displayBlock(i, j);
        }
    }
    //Hint
    if(game->isHinted()){
        setHint(game->hintBox);
    }
    //Trigger
    for(const auto player : game->getPlayer()){
        for(const auto &box : player->getBoxTriggered()){
            //每名玩家的每个boxTriggered都绘制
            setTrigger(box);
        }
    }
    //玩家状态
    setPlayer();
    // 绘制折线
    auto &path = game->connectPath;
    if (!path.isEmpty()) {
        painter.begin(this);
        painter.setPen(QPen(Qt::magenta, 12));
        for (int i = 0; i < path.size() - 1; ++i) {

            const Pos& startPos = path[i];
            const Pos& endPos = path[i + 1];

            // 计算起始位置和结束位置的实际像素坐标
            // 计算起始位置坐标在绘图中的实际位置
           int startX = startPos.x * BLOCK_SIZE + BLOCK_SIZE / 2;
           int startY = startPos.y * BLOCK_SIZE + BLOCK_SIZE / 2;

           // 计算结束位置坐标在绘图中的实际位置
           int endX = endPos.x * BLOCK_SIZE + BLOCK_SIZE / 2;
           int endY = endPos.y * BLOCK_SIZE + BLOCK_SIZE / 2;

            painter.drawLine(startX, startY, endX, endY);
        }
        painter.end();
    }
}

void GameWidget::displayBlock(int i, int j, int flag, bool flip)
{
    //绘制某一方块
    Element type = game->getMapBlock(i, j);
    if(type == None) return;
    const QString path = imagePath[static_cast<int>(type)]; //获取图片路径
    QImage image;
    if (!image.load(path)) {
        qDebug() << "Failed to load image!";
        return;
    }

    //是否翻转
    if(flip) image = image.transformed(QTransform().scale(-1, 1));

    QPainter imagePainter(&image);
    imagePainter.setCompositionMode(QPainter::CompositionMode_Darken);
    switch (flag) {
    case 0: // 默认
        break;
    case 1: // Trigger
        imagePainter.fillRect(image.rect(), Qt::yellow); // 设置矩形的背景色为黄色
        break;
    case 2: // Hint
        imagePainter.fillRect(image.rect(), Qt::red); // 设置矩形的背景色为红色
        break;
    case 3: // Freeze
        imagePainter.fillRect(image.rect(), Qt::blue); // 设置矩形的背景色为深蓝
        break;
    case 4: // Dizzy
        imagePainter.fillRect(image.rect(), Qt::green); // 设置矩形的背景色为绿色
        break;
    case 5: // Normal
        imagePainter.fillRect(image.rect(), Qt::white); // 设置矩形的背景色为白色
        break;
    default:
        return;
        break;
    }
    // 绘制图片
    QPainter painter(this);
    painter.drawImage(i * BLOCK_SIZE, j * BLOCK_SIZE, image, 0, 0, BLOCK_SIZE, BLOCK_SIZE);
}

void GameWidget::displayBlock(const Pos &p, int flag, bool flip)
{
    displayBlock(p.x, p.y, flag, flip);
}

void GameWidget::setHint(const Pos p[])
{
    if(p[0] == Pos(-1, -1)) return; //不存在配对的hintBox
    displayBlock(p[0].x, p[0].y, 2);
    displayBlock(p[1].x, p[1].y, 2);
}

void GameWidget::setTrigger(const Pos &p)
{
    displayBlock(p.x, p.y, 1);
}

void GameWidget::setPlayer()
{
    for(const auto player : game->getPlayer()){
        bool flip = !player->getFace();
        displayBlock(player->getPos(), 5, flip);
        if(player->isDizzy()) displayBlock(player->getPos(), 4, flip);
        if(player->isFrozen()) displayBlock(player->getPos(), 3, flip);
    }
}


void GameWidget::displayTime(int time)
{
    if(time < 10){ // 进入读秒阶段
        audioManager->playCountDown();
        timeLabel->setStyleSheet("color: red;"); // 设置字体颜色为红色
    }
    else{
        audioManager->stopCountDown();
        timeLabel->setStyleSheet("color: black;");
    }

    // 更新倒计时显示
    timeLabel->setText("倒计时：" + QString::number(time) + "s");
}

void GameWidget::displayScore(int score, int id)
{
    if(id == 0) player1ScoreLabel->setText("玩家1得分: " + QString::number(score));
    else player2ScoreLabel->setText("玩家2得分: " + QString::number(score));
}

void GameWidget::displayMessage(const QString &message)
{
    messageBox->setText(message);
    //2s后清空
    QTimer::singleShot(2000, this, &GameWidget::hideMessage);
}

void GameWidget::hideMessage()
{
    messageBox->setText("");
}

void GameWidget::resize(int m, int n)
{
    //地图大小也要重新设置，否则地图显示不全
    M = m;
    N = n;
    //重新设置界面布局
    setFixedSize((M + 5) * BLOCK_SIZE, N * BLOCK_SIZE);
    timeLabel->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, 0, BLOCK_SIZE * 4, BLOCK_SIZE);
    player1ScoreLabel->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 1, BLOCK_SIZE * 4, BLOCK_SIZE);
    player2ScoreLabel->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 2, BLOCK_SIZE * 4, BLOCK_SIZE);
    messageBox->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 6, BLOCK_SIZE * 4, BLOCK_SIZE);
    pauseButton->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 3, BLOCK_SIZE * 2, BLOCK_SIZE);
    continueButton->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 3, BLOCK_SIZE * 2, BLOCK_SIZE);
    saveButton->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 4, BLOCK_SIZE * 1.5, BLOCK_SIZE);
    loadButton->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE * 3, BLOCK_SIZE * 4, BLOCK_SIZE * 1.5, BLOCK_SIZE);
    returnButton->setGeometry(M * BLOCK_SIZE + BLOCK_SIZE, BLOCK_SIZE * 5, BLOCK_SIZE * 3, BLOCK_SIZE);
    emit setSize(this->size());
}


void GameWidget::pauseGame()
{
    paused = true;
    game->stopTimer();
    pauseButton->hide();
    continueButton->show();
    saveButton->show();
    loadButton->show();
    returnButton->show();
    displayMessage("游戏已暂停");
}

void GameWidget::continueGame()
{
    paused = false;
    game->startTimer();
    continueButton->hide();
    pauseButton->show();
    saveButton->hide();
    loadButton->hide();
    returnButton->hide();
    displayMessage("游戏继续");
}

void GameWidget::returnToMain()
{
    //回到主菜单
    emit return2Main();
}

void GameWidget::endGame()
{
    paused = true;
    game->stopTimer(); //停止计时器

    timeLabel->setText("游戏结束"); // 显示游戏结束信息
    pauseButton->hide();
    continueButton->hide();
    saveButton->hide();
    loadButton->hide();
    returnButton->show();
    //游戏结束相关音效
    audioManager->playSoundEffect("GameOver");
    audioManager->stopBGM();
    audioManager->stopCountDown();
}
