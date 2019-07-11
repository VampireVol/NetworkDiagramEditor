#ifndef EQUIPMENTRENDER_H
#define EQUIPMENTRENDER_H

#include<QVector>
#include<body.h>
#include<connector.h>

///Класс, содержащий тело и коннекторы оборудования
class EquipmentRender
{
public:
    EquipmentRender(QVector <Connector*> connectors); /// инициализация тела и коннекторов

    Body *body; ///тело объекта
    QVector <Connector*> connectors; ///коннекторы объекта
};

#endif // EQUIPMENTRENDER_H
