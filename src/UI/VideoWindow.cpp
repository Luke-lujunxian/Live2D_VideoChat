#include "VideoWindow.h"
#include "ui_VideoWindow.h"

VideoWindow::VideoWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::About)
{
	ui->setupUi(this);
}

VideoWindow::~VideoWindow()
{
	delete ui;
}