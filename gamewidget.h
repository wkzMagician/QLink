#pragma once
#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QtWidgets>
#include <QKeyEvent>
#include <QPainter>

#include "game.h"
#include "tpgame.h"
#include "audiomanager.h"

class GameWidget : public QWidget {
    Q_OBJECT
private:
    Game *game;
    int M;
    int N;

    //方块大小
    const int BLOCK_SIZE = 64;

    bool paused = false; //是否暂停
    bool countDown = false; //是否倒计时

    //绘制
    void displayBlock(const int i, const int j, const int flag = 0, const bool flip = false);
    void displayBlock(const Pos &p, const int flag = 0, const bool flip = false);
    void setHint(const Pos p[]);
    void setTrigger(const Pos &p);
    void setPlayer();

    //ui模块
    QLabel *timeLabel;
    QLabel *player1ScoreLabel;
    QLabel *player2ScoreLabel;
    QLabel *messageBox;
    QPushButton *pauseButton;
    QPushButton *continueButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *returnButton;
    //音乐播放器
    AudioManager *audioManager;

    //初始化函数
    void initButton();
    void initLabel();

protected:
    void keyPressEvent(QKeyEvent *event)override; //按键
    void paintEvent(QPaintEvent* event) override; //绘制

public:
    explicit GameWidget(int m, int n, int _time, int numBlock, bool dual, QWidget *parent = nullptr);
    ~GameWidget();

private slots:
    //显示
    void displayTime(const int time);
    void displayScore(const int score, const int id);
    void displayMessage(const QString &message);
    void hideMessage();
    //重新设置界面布局
    void resize(int M, int N);
    //按钮
    void pauseGame();
    void continueGame();
    void returnToMain();
    void endGame();

signals:
    void return2Main();
    void setSize(const QSize &size);
};


#endif // GAMEWIDGET_H
