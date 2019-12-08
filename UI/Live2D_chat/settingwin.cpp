#include "settingwin.h"
#include "settingwin.h"
#include "ui_setting.h"
#include "setting.h"
SettingWin::SettingWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWin)
{
    ui->setupUi(this);
    //Apply funtion
    QObject::connect(ui->lineEdit_Name,&QLineEdit::textChanged,this,&SettingWin::canApply);
	//TODO: Name check
    QObject::connect(ui->lineEdit_ListenPort,&QLineEdit::textChanged,this,&SettingWin::canApply);
    QObject::connect(ui->lineEdit_CallPort,&QLineEdit::textChanged,this,&SettingWin::canApply);
	QObject::connect(ui->lineEdit_AudioPort, &QLineEdit::textChanged, this, &SettingWin::canApply);
	ui->lineEdit_ListenPort->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
	ui->lineEdit_CallPort->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
	ui->lineEdit_AudioPort->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    QObject::connect(ui->comboBox_ProfilePhoto,&QComboBox::currentTextChanged,this,&SettingWin::canApply);
    QObject::connect(ui->comboBox_Model,&QComboBox::currentTextChanged,this,&SettingWin::canApply);
    QObject::connect(ui->comboBox_Camera,&QComboBox::currentTextChanged,this,&SettingWin::canApply);

    QObject::connect(ui->spinBox_MaxCallQueue, QOverload<int>::of(&QSpinBox::valueChanged),this,&SettingWin::canApply);

    QObject::connect(ui->checkBox_Debug_Console,&QCheckBox::stateChanged,this,&SettingWin::canApply);
    QObject::connect(ui->checkBox_Debug_ShowCamera,&QCheckBox::stateChanged,this,&SettingWin::canApply);
    QObject::connect(ui->checkBox_Debug_ShowFEI,&QCheckBox::stateChanged,this,&SettingWin::canApply);

    //QObject::connect(ui->pushButton_Apply,&QPushButton::clicked,this,&Setting::applyFun);


}

SettingWin::~SettingWin()
{
    delete ui;
}

void SettingWin::canApply(){
    ui->pushButton_Apply->setEnabled(true);
}

void SettingWin::on_pushButton_Apply_clicked(){
    //Do something
	Setting* setting = Setting::getSetting();
	setting->setName(ui->lineEdit_Name->text().toStdString());
	setting->setListenPort(ui->lineEdit_ListenPort->text().toInt());
	setting->setCallPort(ui->lineEdit_CallPort->text().toInt());
	setting->setAudioPort(ui->lineEdit_AudioPort->text().toInt());
	setting->setProfile(ui->comboBox_ProfilePhoto->currentText().toStdString());
	setting
    ui->pushButton_Apply->setEnabled(false);
}
void SettingWin::on_pushButton_ProfilePhoto_clicked(){
    //Do something
    ui->pushButton_Apply->setEnabled(true);
}
void SettingWin::on_pushButton_Model_clicked(){
    //Do something
    ui->pushButton_Apply->setEnabled(true);
}
