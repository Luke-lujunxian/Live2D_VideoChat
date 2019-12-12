#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Network_QT.h>
#include <qpixmap.h>
#include<settingwin.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settingWin = nullptr;
    aboutWin = nullptr;
    QObject::connect(ui->actionExit,&QAction::triggered,this,&MainWindow::endProgram);
    QObject::connect(ui->actionAbout,&QAction::triggered,this,[this](){this->aboutWin = this->aboutWin == nullptr ?  new About():this->aboutWin;this->aboutWin->show();});
    QObject::connect(ui->actionSetting,&QAction::triggered,this,[this](){
        this->settingWin = this->settingWin == nullptr ?  new SettingWin():
            this->settingWin;this->settingWin->show(); QObject::connect(settingWin, &SettingWin::settingApplySuccess, this, &MainWindow::updateInfo, Qt::QueuedConnection);
        });
    
    updateInfo();
    Network_QT::getInstance()->networkInit();
    listener = new QThread(this);
    listener->start();
    Network_QT::getInstance()->moveToThread(listener);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::endProgram(){
    //do someting;
    delete aboutWin;
    this->close();
}

void MainWindow::on_pushButton_Call_clicked() {
    try {
        std::string host = ui->lineEdit_IP->text().toStdString();
        host.append(":").append(ui->lineEdit_Port->text().toStdString());
        Network_QT::getInstance()->call(host);
    }
    catch (std::string e) {
        if (e == "NO_RESPONSE") {

        }
    }
}

void MainWindow::updateInfo() {
    qDebug() << "Info Updated";
    QPixmap tempPixmap(QString::fromStdString(Setting::getSetting()->getProfilePath()));
    tempPixmap.scaled(ui->label_Profile->size(), Qt::KeepAspectRatio);
    ui->label_Profile->setScaledContents(true);
    ui->label_Profile->setPixmap(tempPixmap);
    ui->label_Name->setText(QString::fromStdString(Setting::getSetting()->getName()));

}