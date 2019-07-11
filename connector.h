#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class Connector : public QObject, public QGraphicsItem
{
public:
    Connector(Qt::GlobalColor color);
    ~Connector();
    Qt::GlobalColor GetColor();
    int connectorId;
    int equipmentId;
    enum {
        Type = UserType + 10
    };
    int type() const override;
    bool IsNull();
    void SetLink(Connector *forLink);
private:
    Qt::GlobalColor color;
    Connector *link;
    /* Данные методы виртуальные, поэтому их необходимо реализовать
     * в случае наследования от QGraphicsItem
     * */
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class ConnectorRed : public Connector
{
public:
    ConnectorRed();
};

class ConnectorBlue : public Connector
{
public:
    ConnectorBlue();
};

class ConnectorGreen : public Connector
{
public:
    ConnectorGreen();
};

class ConnectorCyan : public Connector
{
public:
    ConnectorCyan();
};

class ConnectorYellow : public Connector
{
public:
    ConnectorYellow();
};

#endif // CONNECTOR_H
