#include "VideoWindow.h"
#include "ui_VideoWindow.h"

VideoWindow::VideoWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::VideoWindow)
{
	ui->setupUi(this);
}

VideoWindow::~VideoWindow()
{
	delete ui;
}