/********************************************************************************
** Form generated from reading UI file 'errorwin.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRORWIN_H
#define UI_ERRORWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ErrorWin
{
public:
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *ErrorWin)
    {
        if (ErrorWin->objectName().isEmpty())
            ErrorWin->setObjectName(QString::fromUtf8("ErrorWin"));
        ErrorWin->setWindowModality(Qt::ApplicationModal);
        ErrorWin->resize(272, 128);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ErrorWin->sizePolicy().hasHeightForWidth());
        ErrorWin->setSizePolicy(sizePolicy);
        label = new QLabel(ErrorWin);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 30, 101, 16));
        pushButton = new QPushButton(ErrorWin);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(100, 80, 75, 23));

        retranslateUi(ErrorWin);
        QObject::connect(pushButton, SIGNAL(clicked()), ErrorWin, SLOT(close()));

        QMetaObject::connectSlotsByName(ErrorWin);
    } // setupUi

    void retranslateUi(QWidget *ErrorWin)
    {
        ErrorWin->setWindowTitle(QCoreApplication::translate("ErrorWin", "Error", nullptr));
        label->setText(QCoreApplication::translate("ErrorWin", "Invalid Setting!", nullptr));
        pushButton->setText(QCoreApplication::translate("ErrorWin", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ErrorWin: public Ui_ErrorWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRORWIN_H
