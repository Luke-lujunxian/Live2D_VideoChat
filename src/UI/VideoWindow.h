#pragma once

#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QWindow>

namespace Ui {
	class VideoWindow;
}

class VideoWindow : public QWindow
{
	Q_OBJECT

public:
	explicit VideoWindow(QWidget *parent = nullptr);
	~VideoWindow();

private:
	Ui::VideoWindow *ui;
};

#endif // VIDEOWINDOW_H