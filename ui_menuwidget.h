/********************************************************************************
** Form generated from reading UI file 'menuwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWIDGET_H
#define UI_MENUWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuWidget
{
public:
    QLabel *label;
    QLineEdit *M;
    QLineEdit *N;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *time;
    QPushButton *singleButton;
    QPushButton *dualButton;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *numBox;

    void setupUi(QWidget *MenuWidget)
    {
        if (MenuWidget->objectName().isEmpty())
            MenuWidget->setObjectName(QString::fromUtf8("MenuWidget"));
        MenuWidget->resize(788, 788);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(30, 240, 233, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        MenuWidget->setPalette(palette);
        MenuWidget->setAutoFillBackground(true);
        MenuWidget->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(MenuWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 230, 161, 41));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QPalette palette1;
        QBrush brush2(QColor(0, 255, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        label->setPalette(palette1);
        QFont font;
        font.setFamily(QString::fromUtf8("Berlin Sans FB Demi"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAutoFillBackground(false);
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/ChoiceBox.png")));
        M = new QLineEdit(MenuWidget);
        M->setObjectName(QString::fromUtf8("M"));
        M->setGeometry(QRect(380, 240, 81, 31));
        M->setFont(font);
        N = new QLineEdit(MenuWidget);
        N->setObjectName(QString::fromUtf8("N"));
        N->setGeometry(QRect(530, 240, 101, 31));
        N->setFont(font);
        label_2 = new QLabel(MenuWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(180, 360, 161, 51));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setFont(font);
        label_3 = new QLabel(MenuWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(490, 250, 21, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(24);
        label_3->setFont(font1);
        time = new QLineEdit(MenuWidget);
        time->setObjectName(QString::fromUtf8("time"));
        time->setGeometry(QRect(370, 370, 113, 31));
        time->setFont(font);
        singleButton = new QPushButton(MenuWidget);
        singleButton->setObjectName(QString::fromUtf8("singleButton"));
        singleButton->setGeometry(QRect(110, 650, 231, 51));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Berlin Sans FB Demi"));
        font2.setPointSize(24);
        font2.setBold(true);
        font2.setWeight(75);
        singleButton->setFont(font2);
        singleButton->setAutoFillBackground(false);
        dualButton = new QPushButton(MenuWidget);
        dualButton->setObjectName(QString::fromUtf8("dualButton"));
        dualButton->setGeometry(QRect(460, 650, 221, 51));
        dualButton->setFont(font2);
        dualButton->setMouseTracking(false);
        dualButton->setAutoFillBackground(false);
        label_4 = new QLabel(MenuWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(290, 50, 231, 81));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Berlin Sans FB Demi"));
        font3.setBold(true);
        font3.setWeight(75);
        label_4->setFont(font3);
        label_5 = new QLabel(MenuWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(180, 500, 161, 51));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setFont(font);
        numBox = new QLineEdit(MenuWidget);
        numBox->setObjectName(QString::fromUtf8("numBox"));
        numBox->setGeometry(QRect(370, 510, 113, 31));
        numBox->setFont(font);

        retranslateUi(MenuWidget);

        QMetaObject::connectSlotsByName(MenuWidget);
    } // setupUi

    void retranslateUi(QWidget *MenuWidget)
    {
        MenuWidget->setWindowTitle(QCoreApplication::translate("MenuWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("MenuWidget", "<html><head/><body><p><span style=\" color:#ff0000;\">\345\234\260\345\233\276\345\244\247\345\260\217\357\274\232</span></p></body></html>", nullptr));
        M->setText(QCoreApplication::translate("MenuWidget", "10", nullptr));
        N->setText(QCoreApplication::translate("MenuWidget", "10", nullptr));
        label_2->setText(QCoreApplication::translate("MenuWidget", "<html><head/><body><p><span style=\" color:#ff0000;\">\345\200\222\350\256\241\346\227\266\351\225\277\357\274\232</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MenuWidget", "*", nullptr));
        time->setText(QCoreApplication::translate("MenuWidget", "60", nullptr));
        singleButton->setText(QCoreApplication::translate("MenuWidget", "\345\215\225\344\272\272\346\250\241\345\274\217", nullptr));
        dualButton->setText(QCoreApplication::translate("MenuWidget", "\345\217\214\344\272\272\346\250\241\345\274\217", nullptr));
        label_4->setText(QCoreApplication::translate("MenuWidget", "<html><head/><body><p><span style=\" font-size:36pt; color:#ff0000;\">\350\277\236\350\277\236\347\234\213</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("MenuWidget", "<html><head/><body><p><span style=\" color:#ff0000;\">\346\226\271\345\235\227\346\225\260\351\207\217\357\274\232</span></p></body></html>", nullptr));
        numBox->setText(QCoreApplication::translate("MenuWidget", "4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuWidget: public Ui_MenuWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUWIDGET_H
