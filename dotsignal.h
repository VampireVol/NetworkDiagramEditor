#ifndef DOTSIGNAL_H
#define DOTSIGNAL_H

#include <QObject>
#include <QGraphicsRectItem>

/// Класс, описывающий вершины ломанной
class DotSignal : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged) ///Макрос Q_PROPERTY необходим для того, чтобы  иметь возможность создавать класс со свойствами, поддерживаемыми метаобъектной подсистемой Qt.

public:
    explicit DotSignal(QGraphicsItem *parentItem = 0, QObject *parent = 0); /// создание вершины ломанной
    explicit DotSignal(QPointF pos, QGraphicsItem *parentItem = 0, QObject *parent = 0); /// создание вершины ломанной с определенной позицией
    ~DotSignal(); /// деструктор класса
    enum Flags {
        Movable = 0x01
    }; /// стандартный флаг возможности двигать

    QPointF previousPosition() const; /// возвращение предыдущей позиции
    void setPreviousPosition(const QPointF previousPosition); /// установка предыдущей позиции

    void setDotFlags(unsigned int flags); /// установка флагов

signals:
    void previousPositionChanged(); /// сигнал, вызываемый при изменении позиции
    void signalMouseRelease(); /// сигнал, вызываемый при отпускании кнопки мыши
    void signalMove(QGraphicsItem *signalOwner, qreal dx, qreal dy); /// отправления сигнала, когда предмет движется

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override; /// действия при движении мыши
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override; /// действия при нажатии кнопки мыши
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override; /// действия при отпускании кнопки мыши
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event); /// дейсвтия при наведении курсора мыши на объект
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event); ///действия при выходе курсора из рабочей области объекта

public slots:
private:
    unsigned int m_flags; // флаги вершины
    QPointF m_previousPosition; // координаты предыдущей позиции
};

#endif // DOTSIGNAL_H
