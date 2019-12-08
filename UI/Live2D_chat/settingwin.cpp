#include "settingwin.h"
#include "settingwin.h"
#include "ui_setting.h"
#include "setting.h"
#include "errorwin.h"
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
	bool allClear = true;
	QString errorColor = "background-color: rgba(255, 0, 0, 100)";
	//background-color: rgba(255, 0, 0, 100);
	allClear = setting->setName(ui->lineEdit_Name->text().toStdString()) ? clearError(ui->lineEdit_Name,allClear) : setError(ui->lineEdit_Name);
	allClear = setting->setListenPort(ui->lineEdit_ListenPort->text().toInt()) ? clearError(ui->lineEdit_ListenPort, allClear) : setError(ui->lineEdit_ListenPort);
	allClear = setting->setCallPort(ui->lineEdit_CallPort->text().toInt()) ? clearError(ui->lineEdit_CallPort, allClear) : setError(ui->lineEdit_CallPort);
	allClear = setting->setAudioPort(ui->lineEdit_AudioPort->text().toInt()) ? clearError(ui->lineEdit_AudioPort, allClear) : setError(ui->lineEdit_AudioPort);
	allClear = setting->setProfile(ui->comboBox_ProfilePhoto->currentText().toStdString()) ? clearError(ui->comboBox_ProfilePhoto, allClear) : setError(ui->comboBox_ProfilePhoto);
	allClear = setting->setModelID(ui->comboBox_Model->currentText().toStdString()) ? clearError(ui->comboBox_Model, allClear) : setError(ui->comboBox_Model);
	allClear = setting->setCameraID(ui->comboBox_Camera->currentText().toInt()) ? clearError(ui->comboBox_Camera, allClear) : setError(ui->comboBox_Camera);
	setting->setMaximumListenQueue(ui->spinBox_MaxCallQueue->value());
	setting->debug = ui->checkBox_Debug_Console->isChecked();
	setting->showCamera = ui->checkBox_Debug_ShowCamera->isChecked();
	setting->ShowFR = ui->checkBox_Debug_ShowFEI->isChecked();
	if(allClear)
		ui->pushButton_Apply->setEnabled(false);
	else {
		ErrorWin* temp = new ErrorWin();
		temp->setWindowFlags(Qt::Dialog);
		temp->show();
		//Error window
	}
}
void SettingWin::on_pushButton_ProfilePhoto_clicked(){
    //Do something
    ui->pushButton_Apply->setEnabled(true);
}
void SettingWin::on_pushButton_Model_clicked(){
    //Do something
    ui->pushButton_Apply->setEnabled(true);
}

bool setError(QWidget* obj) {//Hight light the error box
	obj->setStyleSheet("background-color: rgba(255, 0, 0, 100);");
	return false;
}

bool clearError(QWidget* obj, bool AC) {
	obj->setStyleSheet("");
	return AC;

}