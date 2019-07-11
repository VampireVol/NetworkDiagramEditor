#ifndef VEPOLYLINE_H
#define VEPOLYLINE_H

#include <QObject>
#include <QGraphicsPathItem>
#include <body.h>

class DotSignal;

/// Класс, описывающий ломанную линию
class VEPolyline : public QObject, public QGraphicsPathItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

public:
    explicit VEPolyline(Body *first = 0, Body *end = 0, QObject *parent = 0); /// Инициализация ломанной линии
    ~VEPolyline(); /// Деструктор класса

    enum {
        Type = UserType + 12
    };///Инициализация типа объекта, для распознавания объектов на сцене
    int type() const override;/// возвращение типа объекта
    Body *first; /// указатель на первое тело оборудования
    Body *end; /// указатель на второе тело оборудования
    int polylineId; /// ID ломанной линии
    QPointF previousPosition() const; /// функция, возвращающая предыдущую позицию ломанной линии
    void setPreviousPosition(const QPointF previousPosition); /// Функция, устанавливающая позицию
    void setPath(const QPainterPath &path); /// Установка пути ломанной
    void SetId(int &nextPolylineId); /// Установка ID ломанной
    void SetDescription(QString text); /// Добавление описания для ломанной
    QString GetDescription(); /// Отправление описания ломанной
signals:
    void previousPositionChanged(); ///сигнал о том, что предыдущая позиция была изменена
    void clicked(VEPolyline *rect); ///сигнал о том, что по ломанной линии кликнули
    void signalMove(QGraphicsItem *item, qreal dx, qreal dy); /// сигнал о том, как изменилась позиция веришна ломанной линии
    void polylineIsSelected(int polylineId); /// сигнал о том, что ломанная выбрана
protected:
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override; /// действия при нажатии на ломанную
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override; /// создание новой вершины ломанной
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override; /// удаление отображаемых вершин при отведении курсора мыши за граници ломанной
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override; /// действия, когда курсором водят по этой области
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override; /// создание отображаемых вершин при наведении курсора мыши

public slots:

private slots:
    void slotMove(QGraphicsItem *signalOwner, qreal dx, qreal dy); // слот, чтобы ломанная следовала за оборудованием
    void checkForDeletePoints(); // проверка на необходимость удаления вершины

private:
    QPointF m_previousPosition;
    bool m_leftMouseButtonPressed;
    QList<DotSignal *> listDotes;
    int m_pointForCheck = -1;
    QString description;
    void updateDots(); // вспомогательная функция для проверки удаления отображаемых вершин
};

#endif // VEPOLYLINE_H
