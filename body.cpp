#include "body.h"

Body::Body(int size)
    : size(size), height((2 * size + 1) * 20)
{
    setFlag(ItemIsSelectable);
}

Body::~Body()
{

}

int Body::type() const
{
    return Type;
}

void Body::setId(int id)
{
    this->id = id;
}

QRectF Body::boundingRect() const
{
    return QRectF (0,0,80,height);
}

void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(isSelected() ? 4 : 2);
    painter->setPen(pen);
    painter->setBrush(Qt::white);
    painter->drawRect(0,0,80,height);
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
    auto dx = event->pos().x() - m_previousPosition.x();
    auto dy = event->pos().y() - m_previousPosition.y();
    emit signalMove(this, dx, dy);
}

void Body::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    emit equipmentIsSelected(id);
    m_shiftMouseCoords = this->pos() - mapToScene(event->pos());
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    m_previousPosition = event->pos();
    Q_UNUSED(event);
    QGraphicsItem::mousePressEvent(event);
}

void Body::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
