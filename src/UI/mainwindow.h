#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingwin.h"
#include "about.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void updateInfo();


private slots:
    void on_pushButton_Call_clicked();
    void endProgram();
private:
    SettingWin* settingWin;
    About* aboutWin;
    Ui::MainWindow *ui;
    QThread* listener;
};
#endif // MAINWINDOW_H
