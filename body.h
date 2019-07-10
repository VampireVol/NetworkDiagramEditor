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
    Q_OBJECT
public:
    Body(int size);
    ~Body();

private:
    int size;
    int height;
    QPointF m_shiftMouseCoords;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void equipmentIsPressed();
    void signalMove(QGraphicsSceneMouseEvent *event, QPointF m_shiftMouseCoords);
};

#endif // BODY_H
