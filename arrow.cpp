/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "arrow.h"
#include "diagramitem.h"

#include <QPainter>
#include <QPen>
#include <QtMath>

//! [0]
Arrow::Arrow(MyItem *startItem, MyItem *endItem, QGraphicsItem *parent)
    : QGraphicsLineItem(parent), myStartItem(startItem), myEndItem(endItem)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}
//! [0]

//! [1]
QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}
//! [1]

//! [2]
QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}


//! [2]

//! [3]
void Arrow::updatePosition()
{
    QLineF line(myStartItem->pos(), myEndItem->pos());
    setLine(line);
}

QPointF Arrow::startPoint() const
{
    return point_start;
}

void Arrow::setStartPoint(const QPointF &value)
{
    point_start=value;
}

QPointF Arrow::endPoint() const
{
    return point_end;
}

void Arrow::setEndPoint(const QPointF &value)
{
    point_end=value;
}
//! [3]

//! [4]
void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                  QWidget *)
{
    if (myStartItem->collidesWithItem(myEndItem))
        return;

    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(myColor);
//! [4] //! [5]
//!
//!
    if( point_start.isNull() )
        point_start = myStartItem->getLinePoint();
    if( point_end.isNull() )
        point_end = myEndItem->getLinePoint();

    QLineF centerLine(myStartItem->pos(), myEndItem->pos());

    QPointF p1 = myStartItem->pos();
    QPointF p2 = myEndItem->pos();

    QTransform transform;
    transform.rotate( myStartItem->rotation() );
    p1 += transform.map(point_start);

    QTransform transform2;
    transform2.rotate( myEndItem->rotation() );
    p2 += transform2.map(point_end);


    QPointF pCorner = QPointF(p2.x(),p1.y());
    QLineF line1 = QLineF(p1,pCorner);
    QLineF line2 = QLineF(pCorner,p2);

//    setLine(line1);
    setLine(line2);
    //! [5] //! [6]

    double angle = std::atan2(-line().dy(), line().dx());

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                    cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                    cos(angle + M_PI - M_PI / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;
//! [6] //! [7]
    painter->drawLine(line1);
    painter->drawLine(line2);
//    painter->drawPolygon(arrowHead);
    if (isSelected()) {
        painter->setPen(QPen(myColor, 2, Qt::DashLine));
//        QLineF myLine = line();
        line1.translate(0, 4.0);
        painter->drawLine(line1);
        line1.translate(0,-8.0);
        painter->drawLine(line1);

        painter->setPen(QPen(myColor, 2, Qt::DashLine));
        line2.translate(4.0,0);
        painter->drawLine(line2);
        line2.translate(-8.0,0);
        painter->drawLine(line2);
    }
}
//! [7]
