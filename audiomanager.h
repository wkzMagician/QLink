#pragma once
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>

#include <QMediaPlayer>
#include <QSoundEffect>
#include <QThread>

class AudioManager : public QObject
{
    Q_OBJECT
public:
    explicit AudioManager(QObject *parent = nullptr);
    ~AudioManager();

    void playBGM();
    void stopBGM();
    void playCountDown();
    void stopCountDown();
    void playSoundEffect(const QString &name);
private:
    QMediaPlayer *bgm;
    QSoundEffect *soundEffect;
    QSoundEffect *soundEffect2;
    QSoundEffect *countDown;
    QThread *thread;
};
#endif // AUDIOMANAGER_H
