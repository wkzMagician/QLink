#pragma once
#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "game4test.h"

class TestGame : public QObject
{
    Q_OBJECT
private:
    Game4Test *game4test;
private slots:
    void checkElimination();
    void checkElimination_data();
public:
    TestGame();
    ~TestGame();
};

#endif // TEST_H
