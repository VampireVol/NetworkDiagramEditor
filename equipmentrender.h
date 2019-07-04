#ifndef EQUIPMENTRENDER_H
#define EQUIPMENTRENDER_H

#include<QVector>
#include<body.h>
#include<outputconnector.h>
#include<inputconnector.h>

class EquipmentRender
{
public:
    EquipmentRender(QVector <OutputConnector*> outputs, QVector <InputConnector*> input);

    Body *body;
    QVector <OutputConnector*> outputs;
    QVector <InputConnector*> inputs;
};

#endif // EQUIPMENTRENDER_H
