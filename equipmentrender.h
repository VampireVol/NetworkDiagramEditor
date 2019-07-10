#ifndef EQUIPMENTRENDER_H
#define EQUIPMENTRENDER_H

#include<QVector>
#include<body.h>
#include<connector.h>

class EquipmentRender
{
public:
    EquipmentRender(QVector <Connector*> connectors);

    Body *body;
    QVector <Connector*> connectors;
};

#endif // EQUIPMENTRENDER_H
