/********************************************************************************
** Form generated from reading UI file 'connecting.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTING_H
#define UI_CONNECTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Connecting
{
public:
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QWidget *Connecting)
    {
        if (Connecting->objectName().isEmpty())
            Connecting->setObjectName(QString::fromUtf8("Connecting"));
        Connecting->resize(328, 218);
        label = new QLabel(Connecting);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 70, 141, 41));
        label->setScaledContents(false);
        progressBar = new QProgressBar(Connecting);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(40, 140, 241, 23));
        progressBar->setValue(24);
        progressBar->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        progressBar->setTextVisible(false);
        progressBar->setInvertedAppearance(false);

        retranslateUi(Connecting);

        QMetaObject::connectSlotsByName(Connecting);
    } // setupUi

    void retranslateUi(QWidget *Connecting)
    {
        Connecting->setWindowTitle(QCoreApplication::translate("Connecting", "Form", nullptr));
        label->setText(QCoreApplication::translate("Connecting", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Connecting: public Ui_Connecting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTING_H
