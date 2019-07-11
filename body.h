#ifndef BODY_H
#define BODY_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>


/// Тело оборудования

class Body  : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Body(int size); /// Установление стандартного размера оборудования, установление флага "Выделение объекта"
    ~Body(); /// деструктор класса

public:
    void setId(int id); /// Установление ID equipment (оборудования)
    enum {
        Type = UserType + 11
    }; /// Инициализация типа объекта, для распознавания объектов на сцене
    int type() const override; /// возвращение типа объекта

private:
    int size; // кол-во пар слотов в высоту
    int height; // высота в пикселях
    int id; // id оборудования
    QPointF m_shiftMouseCoords; // координаты точки нажатия по body
    QRectF boundingRect() const; // рабочая область (в виде прямоугольника)
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // рисование тела оборудования
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);// действия при перемещении тела
    void mousePressEvent(QGraphicsSceneMouseEvent *event);// действия при нажатии на тела
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event); // действия при отпускании кнопки мыши
    QPointF m_previousPosition; // координаты предшевствующего положения мыши

signals:
    void equipmentIsSelected(int equipmentId); // отправление сигнала, когда предмет выбран
    void signalMove(QGraphicsItem *signalOwner, qreal dx, qreal dy); //отправления сигнала, когда предмет движется
};

#endif // BODY_H
