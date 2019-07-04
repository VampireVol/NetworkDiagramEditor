#include "body.h"

Body::Body()
{

}

Body::~Body()
{

}

QRectF Body::boundingRect() const
{
    return QRectF (0,0,80,180);
}

void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(Qt::white);
    painter->drawRect(0,0,80,180);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Body::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */

    this->setPos(mapToScene(event->pos() + m_shiftMouseCoords));
}

void Body::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    m_shiftMouseCoords = this->pos() - mapToScene(event->pos());
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Body::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
