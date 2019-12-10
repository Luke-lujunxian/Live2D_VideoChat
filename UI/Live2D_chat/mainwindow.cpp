#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Network.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settingWin = nullptr;
    aboutWin = nullptr;
    QObject::connect(ui->actionExit,&QAction::triggered,this,&MainWindow::endProgram);
    QObject::connect(ui->actionAbout,&QAction::triggered,this,[this](){this->aboutWin = this->aboutWin == nullptr ?  new About():this->aboutWin;this->aboutWin->show();});
    QObject::connect(ui->actionSetting,&QAction::triggered,this,[this](){this->settingWin = this->settingWin == nullptr ?  new SettingWin():this->settingWin;this->settingWin->show();});

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
        Network::getInstance()->call(host);
    }
    catch (std::string e) {
        if (e == "NO_RESPONSE") {

        }
    }
}