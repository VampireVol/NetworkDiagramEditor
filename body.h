#ifndef BODY_H
#define BODY_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class Body  : public QObject, public QGraphicsItem
{
public:
    Body(int maxInputOrOutput);
    ~Body();
private:
    int maxInputOrOutput;
    int height;
    QPointF m_shiftMouseCoords;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BODY_H
