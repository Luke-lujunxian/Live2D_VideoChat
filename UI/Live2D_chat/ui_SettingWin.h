/********************************************************************************
** Form generated from reading UI file 'SettingWin.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGWIN_H
#define UI_SETTINGWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingWin
{
public:
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_OK;
    QPushButton *pushButton_Cancel;
    QPushButton *pushButton_Apply;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QFrame *line_2;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineEdit_Name;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *comboBox_ProfilePhoto;
    QPushButton *pushButton_ProfilePhoto;
    QHBoxLayout *horizontalLayout_9;
    QComboBox *comboBox_Model;
    QPushButton *pushButton_Model;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_11;
    QComboBox *comboBox_Camera;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QLabel *label;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *Setting_ListenPort;
    QLineEdit *lineEdit_ListenPort;
    QPushButton *pushButton_TestListenPort;
    QHBoxLayout *horizontalLayout;
    QLabel *Setting_CallPort;
    QLineEdit *lineEdit_CallPort;
    QPushButton *pushButton_TestCallPort;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_AudioPort;
    QLineEdit *lineEdit_AudioPort;
    QPushButton *pushButton_AudioPortTest;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpinBox *spinBox_MaxCallQueue;
    QFrame *line_6;
    QLabel *label_2;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_4;
    QComboBox *comboBox_OutputDevice;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QComboBox *comboBox_InputDevice;
    QFrame *line_4;
    QLabel *label_10;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_Debug_ShowCamera;
    QCheckBox *checkBox_Debug_Console;
    QCheckBox *checkBox_Debug_ShowFEI;
    QFrame *line_3;

    void setupUi(QWidget *SettingWin)
    {
        if (SettingWin->objectName().isEmpty())
            SettingWin->setObjectName(QString::fromUtf8("SettingWin"));
        SettingWin->setWindowModality(Qt::ApplicationModal);
        SettingWin->resize(620, 576);
        gridLayoutWidget_3 = new QWidget(SettingWin);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(330, 490, 251, 54));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_OK = new QPushButton(gridLayoutWidget_3);
        pushButton_OK->setObjectName(QString::fromUtf8("pushButton_OK"));
        pushButton_OK->setAutoDefault(false);
        pushButton_OK->setFlat(false);

        gridLayout_3->addWidget(pushButton_OK, 1, 0, 1, 1);

        pushButton_Cancel = new QPushButton(gridLayoutWidget_3);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));

        gridLayout_3->addWidget(pushButton_Cancel, 1, 1, 1, 1);

        pushButton_Apply = new QPushButton(gridLayoutWidget_3);
        pushButton_Apply->setObjectName(QString::fromUtf8("pushButton_Apply"));
        pushButton_Apply->setEnabled(false);

        gridLayout_3->addWidget(pushButton_Apply, 1, 2, 1, 1);

        verticalLayoutWidget = new QWidget(SettingWin);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 40, 551, 441));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        line_2 = new QFrame(verticalLayoutWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        label_9 = new QLabel(verticalLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_9);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(label_6);

        label_8 = new QLabel(verticalLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(label_8);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(label_7);


        horizontalLayout_6->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lineEdit_Name = new QLineEdit(verticalLayoutWidget);
        lineEdit_Name->setObjectName(QString::fromUtf8("lineEdit_Name"));
        sizePolicy.setHeightForWidth(lineEdit_Name->sizePolicy().hasHeightForWidth());
        lineEdit_Name->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(lineEdit_Name);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        comboBox_ProfilePhoto = new QComboBox(verticalLayoutWidget);
        comboBox_ProfilePhoto->setObjectName(QString::fromUtf8("comboBox_ProfilePhoto"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox_ProfilePhoto->sizePolicy().hasHeightForWidth());
        comboBox_ProfilePhoto->setSizePolicy(sizePolicy2);
        comboBox_ProfilePhoto->setEditable(false);

        horizontalLayout_7->addWidget(comboBox_ProfilePhoto);

        pushButton_ProfilePhoto = new QPushButton(verticalLayoutWidget);
        pushButton_ProfilePhoto->setObjectName(QString::fromUtf8("pushButton_ProfilePhoto"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_ProfilePhoto->sizePolicy().hasHeightForWidth());
        pushButton_ProfilePhoto->setSizePolicy(sizePolicy3);

        horizontalLayout_7->addWidget(pushButton_ProfilePhoto);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        comboBox_Model = new QComboBox(verticalLayoutWidget);
        comboBox_Model->setObjectName(QString::fromUtf8("comboBox_Model"));
        sizePolicy2.setHeightForWidth(comboBox_Model->sizePolicy().hasHeightForWidth());
        comboBox_Model->setSizePolicy(sizePolicy2);

        horizontalLayout_9->addWidget(comboBox_Model);

        pushButton_Model = new QPushButton(verticalLayoutWidget);
        pushButton_Model->setObjectName(QString::fromUtf8("pushButton_Model"));

        horizontalLayout_9->addWidget(pushButton_Model);


        verticalLayout_3->addLayout(horizontalLayout_9);


        horizontalLayout_6->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout_6);

        line_5 = new QFrame(verticalLayoutWidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_11 = new QLabel(verticalLayoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);

        horizontalLayout_8->addWidget(label_11);

        comboBox_Camera = new QComboBox(verticalLayoutWidget);
        comboBox_Camera->addItem(QString());
        comboBox_Camera->setObjectName(QString::fromUtf8("comboBox_Camera"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(comboBox_Camera->sizePolicy().hasHeightForWidth());
        comboBox_Camera->setSizePolicy(sizePolicy4);
        comboBox_Camera->setEditable(false);
        comboBox_Camera->setCurrentText(QString::fromUtf8("System Default"));
        comboBox_Camera->setDuplicatesEnabled(false);

        horizontalLayout_8->addWidget(comboBox_Camera);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_8);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setLineWidth(1);

        verticalLayout->addWidget(label);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        Setting_ListenPort = new QLabel(verticalLayoutWidget);
        Setting_ListenPort->setObjectName(QString::fromUtf8("Setting_ListenPort"));

        horizontalLayout_3->addWidget(Setting_ListenPort);

        lineEdit_ListenPort = new QLineEdit(verticalLayoutWidget);
        lineEdit_ListenPort->setObjectName(QString::fromUtf8("lineEdit_ListenPort"));
        lineEdit_ListenPort->setInputMethodHints(Qt::ImhDigitsOnly);
        lineEdit_ListenPort->setMaxLength(5);

        horizontalLayout_3->addWidget(lineEdit_ListenPort);

        pushButton_TestListenPort = new QPushButton(verticalLayoutWidget);
        pushButton_TestListenPort->setObjectName(QString::fromUtf8("pushButton_TestListenPort"));

        horizontalLayout_3->addWidget(pushButton_TestListenPort);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Setting_CallPort = new QLabel(verticalLayoutWidget);
        Setting_CallPort->setObjectName(QString::fromUtf8("Setting_CallPort"));

        horizontalLayout->addWidget(Setting_CallPort);

        lineEdit_CallPort = new QLineEdit(verticalLayoutWidget);
        lineEdit_CallPort->setObjectName(QString::fromUtf8("lineEdit_CallPort"));
        lineEdit_CallPort->setInputMethodHints(Qt::ImhDigitsOnly);
        lineEdit_CallPort->setMaxLength(5);

        horizontalLayout->addWidget(lineEdit_CallPort);

        pushButton_TestCallPort = new QPushButton(verticalLayoutWidget);
        pushButton_TestCallPort->setObjectName(QString::fromUtf8("pushButton_TestCallPort"));

        horizontalLayout->addWidget(pushButton_TestCallPort);


        gridLayout_2->addLayout(horizontalLayout, 1, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_AudioPort = new QLabel(verticalLayoutWidget);
        label_AudioPort->setObjectName(QString::fromUtf8("label_AudioPort"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_AudioPort->sizePolicy().hasHeightForWidth());
        label_AudioPort->setSizePolicy(sizePolicy5);

        horizontalLayout_4->addWidget(label_AudioPort);

        lineEdit_AudioPort = new QLineEdit(verticalLayoutWidget);
        lineEdit_AudioPort->setObjectName(QString::fromUtf8("lineEdit_AudioPort"));
        lineEdit_AudioPort->setInputMethodHints(Qt::ImhDigitsOnly);
        lineEdit_AudioPort->setMaxLength(5);

        horizontalLayout_4->addWidget(lineEdit_AudioPort);

        pushButton_AudioPortTest = new QPushButton(verticalLayoutWidget);
        pushButton_AudioPortTest->setObjectName(QString::fromUtf8("pushButton_AudioPortTest"));

        horizontalLayout_4->addWidget(pushButton_AudioPortTest);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label_5);

        spinBox_MaxCallQueue = new QSpinBox(verticalLayoutWidget);
        spinBox_MaxCallQueue->setObjectName(QString::fromUtf8("spinBox_MaxCallQueue"));
        spinBox_MaxCallQueue->setMinimum(1);
        spinBox_MaxCallQueue->setValue(5);

        horizontalLayout_5->addWidget(spinBox_MaxCallQueue);


        verticalLayout->addLayout(horizontalLayout_5);

        line_6 = new QFrame(verticalLayoutWidget);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_6);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_2);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_10->addWidget(label_4);

        comboBox_OutputDevice = new QComboBox(verticalLayoutWidget);
        comboBox_OutputDevice->setObjectName(QString::fromUtf8("comboBox_OutputDevice"));

        horizontalLayout_10->addWidget(comboBox_OutputDevice);


        gridLayout_4->addLayout(horizontalLayout_10, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        comboBox_InputDevice = new QComboBox(verticalLayoutWidget);
        comboBox_InputDevice->setObjectName(QString::fromUtf8("comboBox_InputDevice"));

        horizontalLayout_2->addWidget(comboBox_InputDevice);


        gridLayout_4->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_4);

        line_4 = new QFrame(verticalLayoutWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        label_10 = new QLabel(verticalLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_10);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkBox_Debug_ShowCamera = new QCheckBox(verticalLayoutWidget);
        checkBox_Debug_ShowCamera->setObjectName(QString::fromUtf8("checkBox_Debug_ShowCamera"));

        gridLayout->addWidget(checkBox_Debug_ShowCamera, 2, 1, 1, 1);

        checkBox_Debug_Console = new QCheckBox(verticalLayoutWidget);
        checkBox_Debug_Console->setObjectName(QString::fromUtf8("checkBox_Debug_Console"));

        gridLayout->addWidget(checkBox_Debug_Console, 2, 0, 1, 1);

        checkBox_Debug_ShowFEI = new QCheckBox(verticalLayoutWidget);
        checkBox_Debug_ShowFEI->setObjectName(QString::fromUtf8("checkBox_Debug_ShowFEI"));

        gridLayout->addWidget(checkBox_Debug_ShowFEI, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        line_3 = new QFrame(verticalLayoutWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);


        retranslateUi(SettingWin);

        pushButton_OK->setDefault(false);


        QMetaObject::connectSlotsByName(SettingWin);
    } // setupUi

    void retranslateUi(QWidget *SettingWin)
    {
        SettingWin->setWindowTitle(QCoreApplication::translate("SettingWin", "Setting", nullptr));
        pushButton_OK->setText(QCoreApplication::translate("SettingWin", "OK", nullptr));
        pushButton_Cancel->setText(QCoreApplication::translate("SettingWin", "Calcel", nullptr));
        pushButton_Apply->setText(QCoreApplication::translate("SettingWin", "Apply", nullptr));
        label_9->setText(QCoreApplication::translate("SettingWin", "General:", nullptr));
        label_6->setText(QCoreApplication::translate("SettingWin", "Name(4-16):", nullptr));
        label_8->setText(QCoreApplication::translate("SettingWin", "Profile Photo", nullptr));
        label_7->setText(QCoreApplication::translate("SettingWin", "Model:", nullptr));
        pushButton_ProfilePhoto->setText(QCoreApplication::translate("SettingWin", "Select...", nullptr));
        pushButton_Model->setText(QCoreApplication::translate("SettingWin", "Select...", nullptr));
        label_11->setText(QCoreApplication::translate("SettingWin", "Prefered Camera:", nullptr));
        comboBox_Camera->setItemText(0, QCoreApplication::translate("SettingWin", "System Default", nullptr));

        label->setText(QCoreApplication::translate("SettingWin", "NetWork:", nullptr));
        Setting_ListenPort->setText(QCoreApplication::translate("SettingWin", "Listen Port", nullptr));
        pushButton_TestListenPort->setText(QCoreApplication::translate("SettingWin", "Test", nullptr));
        Setting_CallPort->setText(QCoreApplication::translate("SettingWin", "Call Port", nullptr));
        pushButton_TestCallPort->setText(QCoreApplication::translate("SettingWin", "Test", nullptr));
        label_AudioPort->setText(QCoreApplication::translate("SettingWin", "Audio Port:", nullptr));
        pushButton_AudioPortTest->setText(QCoreApplication::translate("SettingWin", "Test", nullptr));
        label_5->setText(QCoreApplication::translate("SettingWin", "Maximun Call Queue", nullptr));
        label_2->setText(QCoreApplication::translate("SettingWin", "Audio:", nullptr));
        label_4->setText(QCoreApplication::translate("SettingWin", "Output Device", nullptr));
        label_3->setText(QCoreApplication::translate("SettingWin", "Input Device", nullptr));
        label_10->setText(QCoreApplication::translate("SettingWin", "Debug:", nullptr));
        checkBox_Debug_ShowCamera->setText(QCoreApplication::translate("SettingWin", "Show camera", nullptr));
        checkBox_Debug_Console->setText(QCoreApplication::translate("SettingWin", "Console", nullptr));
        checkBox_Debug_ShowFEI->setText(QCoreApplication::translate("SettingWin", "Show facial recognization image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingWin: public Ui_SettingWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWIN_H
