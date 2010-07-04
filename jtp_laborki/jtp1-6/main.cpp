#include <qapplication.h>
#include "drawview.h"

using namespace kpfp;

int main(int argc, char **argv) {
	QApplication app(argc,argv);
	DrawView *draw = new DrawView();
	draw->setWindowTitle("JTP1-6");
	draw->show();
	return app.exec();
}

