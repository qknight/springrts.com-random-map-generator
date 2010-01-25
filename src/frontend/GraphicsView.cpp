/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "GraphicsView.h"
#include <QMouseEvent>
#include <QDebug>

GraphicsView::GraphicsView(QWidget * parent) : QGraphicsView(parent) {
//     setDragMode(QGraphicsView::ScrollHandDrag);
    onmove=false;
}

GraphicsView::~GraphicsView()
{
}
void GraphicsView::mousePressEvent ( QMouseEvent * event ) {
    if (event->button() == Qt::MidButton) {
        x=event->x();
        y=event->y();
        onmove=true;
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseReleaseEvent ( QMouseEvent * event ) {
    onmove=false;
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::mouseMoveEvent ( QMouseEvent * event ) {
    if (onmove == true) {
        int xdiff = x - event->x();
        int ydiff = y - event->y();

        // x and y store the old values so we can compute the difference
        x = event->x();
        y = event->y();

        QRectF v = sceneRect();
        v.moveTo(v.x()+xdiff, v.y()+ydiff);
        setSceneRect(v);
// 	centerOn(v.x()+xdiff,v.y()+ydiff);
// 	qDebug() << "you are looking at x/y = " << v.x() << " " << v.y();
    }
    QGraphicsView::mouseMoveEvent(event);

}

void GraphicsView::resizeEvent(QResizeEvent* event) {
  QRectF v = sceneRect();
  qDebug() << v;
  setSceneRect(v.x(),v.y(),v.width(),v.height());
}



