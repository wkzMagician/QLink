#include "mainwindow.h"

#include <QApplication>
#include <ctime>

/*
#include "testgame.h"
QTEST_MAIN(TestGame);
*/

int main(int argc, char *argv[])
{
    // 设置随机数种子，可以使用当前时间作为种子
    std::srand(std::time(nullptr));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
