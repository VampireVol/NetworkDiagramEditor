#include "connector.h"

Connector::Connector(Qt::GlobalColor color)
    : connectorId(0), equipmentId(0), color(color), link(nullptr)
{
    setFlag(ItemIsSelectable);
}

Connector::~Connector()
{

}

Qt::GlobalColor Connector::GetColor()
{
    return color;
}

void Connector::SetLink(Connector *connector)
{
    link = connector;
}

Connector* Connector::GetLink()
{
    return link;
}

QRectF Connector::boundingRect() const
{
    return QRectF (0,0,20,20);
}

void Connector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(isSelected() ? 4 : 0);
    painter->setPen(pen);
    painter->setBrush(color);
    painter->drawRect(0,0,20,20);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

int Connector::type() const
{
    return Type;
}

bool Connector::IsNull()
{
    return link == nullptr ? true : false;
}

ConnectorRed::ConnectorRed()
    : Connector (Qt::red)
{

}

ConnectorBlue::ConnectorBlue()
    : Connector (Qt::blue)
{

}

ConnectorGreen::ConnectorGreen()
    : Connector (Qt::green)
{

}

ConnectorCyan::ConnectorCyan()
    : Connector (Qt::cyan)
{

}

ConnectorYellow::ConnectorYellow()
    : Connector (Qt::yellow)
{

}
