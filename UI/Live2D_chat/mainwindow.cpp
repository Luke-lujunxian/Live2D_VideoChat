#include "mainwindow.h"
#include "ui_mainwindow.h"

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
