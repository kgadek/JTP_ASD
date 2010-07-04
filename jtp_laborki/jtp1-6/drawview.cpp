#include <qpainter.h>
#include "drawview.h"

using namespace kpfp;

DrawView::DrawView() {
	width = 500;
	height = 500;
	setWindowTitle("JTP1-6 by Konrad Gadek");
	resize(width, height);
}

/**
  * Przemalowanie regionu.
  * Wywoływane przy repain() lub update() lub z innych powodów.
  */
void DrawView::paintEvent( QPaintEvent * ) {
	QPainter paint(this);
	paint.setWindow(0,0,width,height);
	paint.drawLine(20,20,50,50);
}

