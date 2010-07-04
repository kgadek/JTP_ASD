#ifndef _KPFP_DRAWVIEW
#define _KPFP_DRAWVIEW

#include <qwidget.h>
#include <qpainter.h>

namespace kpfp {

/**
  * Widget rysujący na ekranie.
  * Zaadaptowany widget z przykładowego pliku ,,QtDrawExample-v4.cpp''.
  */
class DrawView : public QWidget {
private:
	int width, height;
public:
	DrawView();
protected:
	void paintEvent( QPaintEvent * );
};

}

#endif
