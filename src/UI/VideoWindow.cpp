#include "VideoWindow.h"
#include "ui_VideoWindow.h"

//#include <LApp/LAppDelegate.hpp>

VideoWindow::VideoWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::VideoWindow),
	openGLWidget(new QOpenGLWidget)
{
	ui->setupUi(this);
}

VideoWindow::~VideoWindow()
{
	delete openGLWidget;
	delete ui;
}