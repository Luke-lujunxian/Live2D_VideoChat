/********************************************************************************
** Form generated from reading UI file 'Chat.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_H
#define UI_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chat
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Stop_Capture;
    QPushButton *pushButton_End;
    QPushButton *pushButton_Mute;
    QSpacerItem *horizontalSpacer_2;
    QWidget *gridLayoutWidget;
    QGridLayout *DisplayArea;
    QOpenGLWidget *openGLWidget_3;
    QOpenGLWidget *openGLWidget;
    QOpenGLWidget *openGLWidget_2;

    void setupUi(QWidget *Chat)
    {
        if (Chat->objectName().isEmpty())
            Chat->setObjectName(QString::fromUtf8("Chat"));
        Chat->resize(638, 453);
        horizontalLayoutWidget = new QWidget(Chat);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 380, 561, 71));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_Stop_Capture = new QPushButton(horizontalLayoutWidget);
        pushButton_Stop_Capture->setObjectName(QString::fromUtf8("pushButton_Stop_Capture"));

        horizontalLayout->addWidget(pushButton_Stop_Capture);

        pushButton_End = new QPushButton(horizontalLayoutWidget);
        pushButton_End->setObjectName(QString::fromUtf8("pushButton_End"));

        horizontalLayout->addWidget(pushButton_End);

        pushButton_Mute = new QPushButton(horizontalLayoutWidget);
        pushButton_Mute->setObjectName(QString::fromUtf8("pushButton_Mute"));

        horizontalLayout->addWidget(pushButton_Mute);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        gridLayoutWidget = new QWidget(Chat);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(40, 20, 561, 361));
        DisplayArea = new QGridLayout(gridLayoutWidget);
        DisplayArea->setObjectName(QString::fromUtf8("DisplayArea"));
        DisplayArea->setContentsMargins(0, 0, 0, 0);
        openGLWidget_3 = new QOpenGLWidget(gridLayoutWidget);
        openGLWidget_3->setObjectName(QString::fromUtf8("openGLWidget_3"));

        DisplayArea->addWidget(openGLWidget_3, 2, 0, 1, 1);

        openGLWidget = new QOpenGLWidget(gridLayoutWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));

        DisplayArea->addWidget(openGLWidget, 0, 0, 1, 1);

        openGLWidget_2 = new QOpenGLWidget(gridLayoutWidget);
        openGLWidget_2->setObjectName(QString::fromUtf8("openGLWidget_2"));

        DisplayArea->addWidget(openGLWidget_2, 0, 1, 1, 1);


        retranslateUi(Chat);

        QMetaObject::connectSlotsByName(Chat);
    } // setupUi

    void retranslateUi(QWidget *Chat)
    {
        Chat->setWindowTitle(QCoreApplication::translate("Chat", "Form", nullptr));
        pushButton_Stop_Capture->setText(QCoreApplication::translate("Chat", "Stop Capture", nullptr));
        pushButton_End->setText(QCoreApplication::translate("Chat", "End", nullptr));
        pushButton_Mute->setText(QCoreApplication::translate("Chat", "Mute", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chat: public Ui_Chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_H
