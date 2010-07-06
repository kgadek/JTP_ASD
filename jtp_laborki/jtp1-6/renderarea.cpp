#include "renderarea.h"
#include "polygon.h"
#include <qt4/QtGui/QtGui>
#include <qt4/QtCore/Qt>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {
       image = QImage(16,16,QImage::Format_ARGB32);
       zoom = 40;
       newX = newY = 0;
}

void RenderArea::paintEvent(QPaintEvent *) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QLinearGradient grad;
        grad.setColorAt(0.0,QColor(255,0,0,255));
        grad.setColorAt(1.0,QColor(255,127,0,255));
        painter.setBrush(grad);

        for(int j=0; j<=image.width(); ++j)
                painter.drawLine(zoom*j,0,zoom*j,zoom*image.width());
        for(int i=0; i<=image.width(); ++i)
                painter.drawLine(0,zoom*i,zoom*image.width(),zoom*i);

        poly.show_reset();
        Punkt a;
        if(!poly.show_end()) {
                QPainterPath path;
                a = poly.show_next();
                path.moveTo(a.getIX()+transl.getIX(),a.getIY()+transl.getIY());
                while(!poly.show_end()) {
                        a = poly.show_next();
                        path.lineTo(a.getIX()+transl.getIX(),a.getIY()+transl.getIY());
                }
                path.closeSubpath();
                painter.drawPath(path);
        }
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
        if(event->buttons() & Qt::LeftButton)
                addPoint(event->pos());
}

QSize RenderArea::sizeHint() const {
        QSize size = zoom * image.size();
        if(zoom >= 3)
            size += QSize(1,1);
        return size;
}

void RenderArea::addPoint(const QPoint &pos) {
        poly.add(Punkt((double)(pos.x()-transl.getIX()),(double)(pos.y()-transl.getIY()),0.0));
        update();
}

void RenderArea::clearPoly() {
        poly.clear();
        update();
}

void RenderArea::movePoly() {
        transl += Wektor(newX,newY,0);
        update();
}

void RenderArea::unMovePoly() {
        transl = Wektor();
        update();
}

void RenderArea::setNewX(QString x) {
        newX = x.toInt();
}

void RenderArea::setNewY(QString y) {
        newY = y.toInt();
}
