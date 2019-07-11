#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include<QVector>
#include<QString>
#include<equipmentrender.h>
#include <QListWidgetItem>
#include <QLabel>
#include <QGraphicsProxyWidget>

/// Класс, описывающий оборудование
class Equipment : public QListWidgetItem
{
public:
    Equipment(QVector <Connector*> connectors); /// Инициализация стандартными значениями переменных и создание нового экземпляра EquipmentRender (содержится тело и коннекторы)
    ~Equipment(); /// деструктор класса, удаление экземпляра EquipmentRender

public:
    QLabel *labelId; ///вывод ID оборудования
    QString name; /// имя оборудования
    int equipmentId; /// ID оборудования
    EquipmentRender *render; /// Тело и коннекторы

public:
    void SetId(int &nextEquipmentId); /// Установка ID оборудования

public:
    static Equipment* CreateCopy(Equipment *equipment); /// Создание копии оборудования
    static bool Contains(QVector <Equipment*> equipments, Equipment *equipment); /// Проверка, есть ли оборудование в векторе
};

#endif // EQUIPMENT_H
