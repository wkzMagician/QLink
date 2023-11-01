#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    menuWidget = new MenuWidget(this);
    setFixedSize(menuWidget->size());
    connect(menuWidget, &MenuWidget::startGame, this, &MainWindow::switchToGame);
}

void MainWindow::switchToGame(int m, int n, int _time, int numBox, bool dual)
{
    //开始游戏
    gameWidget = new GameWidget(m, n, _time, numBox, dual, this);
    //信号连接
    connect(gameWidget, &GameWidget::return2Main, this, &MainWindow::switchToMenu);
    //即时调整窗口大小
    connect(gameWidget, &GameWidget::setSize, this, QOverload<const QSize &>::of(&MainWindow::setFixedSize));
    setCentralWidget(gameWidget);
    setFixedSize(gameWidget->size()); //设置窗口大小
    gameWidget->show();
    menuWidget->hide();
}

void MainWindow::switchToMenu()
{
    //返回主菜单
    delete gameWidget;
    gameWidget = nullptr;
    menuWidget->show();
    setFixedSize(menuWidget->size()); //设置窗口大小
}
