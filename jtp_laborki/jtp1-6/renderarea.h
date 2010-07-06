#ifndef DRAW_H
#define DRAW_H

#include <qt4/QtGui/QtGui>
#include "polygon.h"

/**
  * Widget RenderArea.
  */
class RenderArea : public QWidget {
        Q_OBJECT
public:
	/**
	  * Domyślny konstruktor.
	  */
        RenderArea(QWidget *parent = 0);
	/**
	  * Podpowiedź dotycząca rozmiaru widgetu.
	  * @return Zwraca obiekt QSize zawierający
	  * wskazówki dot. szerokości i wysokości
	  * widgetu.
	  */
        QSize sizeHint() const;
public slots:
	/**
	  * Czyść polygon.
	  */
        void clearPoly();
	/**
	  * Przesuwa polygon o wektor.
	  * Przesunięcie zapamiętane jest w zmiennych
	  * newX i newY.
	  */
        void movePoly();
	/**
	  * Ustawia polygon na oryginalnym miejscu.
	  */
        void unMovePoly();
	/**
	  * Ustaw wartość przesunięcia polygonu w poziomie (w newX).
	  */
        void setNewX(QString);
	/**
	  * Ustaw wartość przesunięcia polygonu w pionie (w newY).
	  */
        void setNewY(QString);
protected:
	/**
	  * Naciśnięcie myszy.
	  * Wciśnięcie lewego przycisku myszy powoduje dodanie
	  * kolejnego wierzchołka do polygonu.
	  */
        void mousePressEvent(QMouseEvent *);
	/**
	  * Rysowanie obiektów.
	  * Rysuje siatkę i polygon.
	  * @param event Informacje o kliknięciu.
	  */
        void paintEvent(QPaintEvent *event);
private:
	/**
	  * Dodawanie punktu do polygonu.
	  * @param pos Współrzędne nowego punktu.
	  */
        void addPoint(const QPoint &pos);
	/**
	  * Obiekt QImage.
	  * Przydaje się do wyznaczania wymiarów dla widgetu.
	  */
        QImage image;
	/**
	  * Współczynnik wielkości.
	  * Określa rozmiar pola rysunkowego.
	  */
        int zoom;
	/**
	  * Rysowany polygon.
	  */
        Polygon poly;
	/**
	  * Przesunięcie polygonu (sumaryczne).
	  */
        Wektor transl;
	/**
	  * Nowe przesunięcie o wektor w poziomie
	  */
        double newX;
	/**
	  * Nowe przesunięcie o wektor w pionie.
	  */
        double newY;
};

#endif // DRAW_H
