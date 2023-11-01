#include "testgame.h"

TestGame::TestGame()
{
    game4test = new Game4Test(10, 10);
    game4test->setMap();
}

TestGame::~TestGame()
{
    delete game4test;
}

void TestGame::checkElimination_data()
{
    //测试数据
    //Point1_x, Point1_y, Point2_x, Point2_y, correctJudge
    //前4列为两点坐标，后1列为正确判定
    QTest::addColumn<int>("Point1_x");
    QTest::addColumn<int>("Point1_y");
    QTest::addColumn<int>("Point2_x");
    QTest::addColumn<int>("Point2_y");
    QTest::addColumn<bool>("correctJudge");

    QTest::newRow("outOfBoundary(1)") << -1 << 0 << 0 << 0 << false;
    QTest::newRow("outOfBoundary(2)") << 10 << 5 << 4 << 4 << false;

    QTest::newRow("NotBox") << 4 << 4 << 4 << 5 << false;

    QTest::newRow("SameBoxes") << 4 << 1 << 4 << 1 << false;

    QTest::newRow("DifferentType(1)") << 0 << 4 << 0 << 6 << false;
    QTest::newRow("DifferentType(2)") << 4 << 2 << 6 << 2 << false;

    QTest::newRow("LeftBoundary") << 0 << 0 << 2 << 4 << true;
    QTest::newRow("RightBoundary") << 9 << 2 << 8 << 5 << true;
    QTest::newRow("UpBoundary") << 4 << 0 << 7 << 0 << false;
    QTest::newRow("DownBoundary") << 3 << 9 << 8 << 9 << false;

    QTest::newRow("0Corner(1)") << 6 << 4 << 6 << 7 << true;
    QTest::newRow("0Corner(2)") << 7 << 2 << 7 << 9 << true;
    QTest::newRow("1Corner(1)") << 2 << 1 << 4 << 2 << true;
    QTest::newRow("1Corner(2)") << 5 << 2 << 6 << 8 << true;
    QTest::newRow("2Corner(1)") << 1 << 7 << 8 << 1 << true;
    QTest::newRow("2Corner(2)") << 4 << 2 << 5 << 9 << true;

    QTest::newRow("Fail2Link(1)") << 8 << 1 << 8 << 7 << false;
    QTest::newRow("Fail2Link(2)") << 2 << 1 << 3 << 7 << false;
    QTest::newRow("Fail2Link(3)") << 0 << 6 << 6 << 4 << false;
    QTest::newRow("Fail2Link(4)") << 4 << 8 << 6 << 9 << false;
}

void TestGame::checkElimination()
{
    QFETCH(int, Point1_x);
    QFETCH(int, Point1_y);
    QFETCH(int, Point2_x);
    QFETCH(int, Point2_y);
    QFETCH(bool, correctJudge);

    QCOMPARE(game4test->checkElimination(Pos(Point1_x, Point1_y), Pos(Point2_x, Point2_y)),
             correctJudge);
}
