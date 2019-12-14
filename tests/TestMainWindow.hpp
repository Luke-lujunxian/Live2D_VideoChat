#ifdef _TEST_RUN__

#include "mainwindow.h"
#include "detection.h"
#include <QApplication>

class TestMainWindow {
public:
	static int runTest(int argc, char *argv[]) {
		QApplication a(argc, argv);
		MainWindow w;
		w.show();
		return a.exec();
	}
};

#endif