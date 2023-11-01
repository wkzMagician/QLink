#include "audiomanager.h"

AudioManager::AudioManager(QObject *parent)
    : QObject(parent)
{
    thread = new QThread;

    bgm = new QMediaPlayer(thread);
    soundEffect = new QSoundEffect(thread);
    soundEffect2 = new QSoundEffect(thread);
    countDown = new QSoundEffect(thread);//倒计时音效
}

AudioManager::~AudioManager()
{
    delete bgm;
    delete soundEffect;
    delete soundEffect2;
    delete countDown;
    delete thread;
}

void AudioManager::playBGM()
{
    bgm->setMedia(QUrl("qrc:/sound/sounds/BGM.ogg"));
    bgm->setVolume(50); // 设置背景音乐音量
    bgm->play();
}

void AudioManager::stopBGM()
{
    bgm->stop();
}

void AudioManager::playCountDown()
{
    countDown->setSource(QUrl("qrc:/sound/sounds/CountDown.wav"));
    countDown->setVolume(100); // 设置音效音量
    countDown->play();
}

void AudioManager::stopCountDown()
{
    countDown->stop();
}

void AudioManager::playSoundEffect(const QString &name)
{
    QString filePath = "qrc:/sound/sounds/" + name + ".wav";
    //如果soundEffect正在播放，则播放soundEffect2
    if(!soundEffect->isPlaying()){
        soundEffect->setSource(QUrl(filePath));
        soundEffect->setVolume(100); // 设置音效音量
        soundEffect->play();
    }
    else{
        soundEffect2->setSource(QUrl(filePath));
        soundEffect2->setVolume(100); // 设置音效音量
        soundEffect2->play();
    }
}
