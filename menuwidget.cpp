#include "menuwidget.h"
#include "ui_menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWidget)
{
    ui->setupUi(this);

    inputM = findChild<QLineEdit*>("M");
    inputN = findChild<QLineEdit*>("N");
    inputTime = findChild<QLineEdit*>("time");
    inputNumBox = findChild<QLineEdit*>("numBox");
}

MenuWidget::~MenuWidget()
{
    delete ui;
}

void MenuWidget::on_singleButton_clicked()
{

    int M = inputM->text().toInt();
    int N = inputN->text().toInt();
    int time = inputTime->text().toInt();
    int numBox = inputNumBox->text().toInt();
    //读取输入，开始游戏
    emit startGame(M, N, time, numBox, false);
}

void MenuWidget::on_dualButton_clicked()
{
    int M = inputM->text().toInt();
    int N = inputN->text().toInt();
    int time = inputTime->text().toInt();
    int numBox = inputNumBox->text().toInt();
    emit startGame(M, N, time, numBox, true);
}

void MenuWidget::on_M_editingFinished()
{
    bool ok;
    int M = inputM->text().toInt(&ok);
    //输入不合法，重置为默认值
    if(!ok) inputM->setText("10");
    else if(M < 7) inputM->setText("7");
    else if(M > 20) inputM->setText("20");
}

void MenuWidget::on_N_editingFinished()
{
    bool ok;
    int N = inputN->text().toInt(&ok);
    //输入不合法，重置为默认值
    if(!ok) inputN->setText("10");
    else if(N < 7) inputN->setText("7");
    else if(N > 20) inputN->setText("20");
}

void MenuWidget::on_time_editingFinished()
{
    bool ok;
    int t = inputTime->text().toInt(&ok);
    //输入不合法，重置为默认值
    if(!ok) inputTime->setText("60");
    else if(t < 1) inputTime->setText("1");
    else if(t > 60 * 60 * 24) inputTime->setText(QString::number(60 * 60 * 24));
}

void MenuWidget::on_numBox_editingFinished()
{
    bool ok;
    int n = inputNumBox->text().toInt(&ok);
    //输入不合法，重置为默认值
    if(!ok) inputNumBox->setText("4");
    else if(n < 3) inputNumBox->setText("3");
    else if(n > 8) inputNumBox->setText("8");
}
