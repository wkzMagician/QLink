#include "player.h"

Player::Player(int ID): id(ID){}

void Player::setBoxTriggered(const Pos &_pos){
    //砖块还未消除，不能再点亮砖块
    if(boxTriggered.size() >= 2) return;
    //查找是否是同一砖块
    int index = boxTriggered.indexOf(_pos);
    //没找到，则入队
    if(index == -1) boxTriggered.push_back(_pos);
    //找到，取消其点亮
    else boxTriggered.remove(index);
    //有两块了，执行判定（能否消除）
    if(boxTriggered.size() >= 2)
        emit checkBox(boxTriggered[0], boxTriggered[1], this);
    //更新绘图
    emit update();
}

void Player::addScore(int value)
{
    setScore(score + value);
}

void Player::setScore(int value)
{
    score = value;
    emit updateScore(score, id); //更新分数
}

void Player::Freeze(int freezeTime)
{
    freeze = true;
    QTimer::singleShot(freezeTime * 1000, this, &Player::unfreeze);
}

void Player::setDizzy(int dizzyTime)
{
    dizzy = true;
    QTimer::singleShot(dizzyTime * 1000, this, &Player::undizzy);
}

void Player::unfreeze()
{
    freeze = false;
}

void Player::undizzy()
{
    dizzy = false;
}
