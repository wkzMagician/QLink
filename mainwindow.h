#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "menuwidget.h"
#include "gamewidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void switchToGame(int m, int n, int _time, int numBlock, bool dual);
    void switchToMenu();

private:
    MenuWidget *menuWidget;
    GameWidget *gameWidget;
};

#endif // MAINWINDOW_H
