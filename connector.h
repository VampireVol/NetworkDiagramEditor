#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

///Класс описания коннектора
class Connector : public QObject, public QGraphicsItem
{
public:
    Connector(Qt::GlobalColor color); /// установка стандртного цвета и флага
    ~Connector(); /// деструктор класса

    int connectorId; /// личное ID коннектора
    int equipmentId; /// ID оборудование
    enum {
        Type = UserType + 10
    };/// Инициализация типа объекта, для распознавания объектов на сцене
    int type() const override; /// возвращение типа объекта
    bool IsNull(); /// проверка на NULL указатель, проверка на сущестовавание связи

public:
    Qt::GlobalColor GetColor(); /// возвращение цвета коннектора
    void SetLink(Connector *connector); ///установление связи между коннекторами
    Connector* GetLink(); /// возвращение указателя на коннектор, связанный с выбранным коннектором

private:
    Qt::GlobalColor color; //цвет коннектора
    Connector *link; //указатель на связанный коннектор
    /* Данные методы виртуальные, поэтому их необходимо реализовать
     * в случае наследования от QGraphicsItem
     * */
    QRectF boundingRect() const; //рабочая область
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //рисование коннектора
};

/// Класс USB
class ConnectorRed : public Connector
{
public:
    ConnectorRed();
};

/// Класс HDMI
class ConnectorBlue : public Connector
{
public:
    ConnectorBlue();
};

/// Класс VGA
class ConnectorGreen : public Connector
{
public:
    ConnectorGreen();
};

/// Класс ethernet
class ConnectorCyan : public Connector
{
public:
    ConnectorCyan();
};

/// Класс Mini jack 3.5 mm
class ConnectorYellow : public Connector
{
public:
    ConnectorYellow();
};

#endif // CONNECTOR_H
