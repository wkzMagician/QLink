#pragma once
#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QtWidgets>

namespace Ui {
class MenuWidget;
}

class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = nullptr);
    ~MenuWidget();

private:
    Ui::MenuWidget *ui;
    //输入的文本框
    QLineEdit *inputM;
    QLineEdit *inputN;
    QLineEdit *inputTime;
    QLineEdit *inputNumBox;

signals:
    void startGame(int, int, int, int, bool);

private slots:
    void on_singleButton_clicked();
    void on_dualButton_clicked();
    void on_M_editingFinished();
    void on_N_editingFinished();
    void on_time_editingFinished();
    void on_numBox_editingFinished();
};

#endif // MENUWIDGET_H
