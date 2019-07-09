#ifndef EQUIPMENTRENDER_H
#define EQUIPMENTRENDER_H

#include<QVector>
#include<body.h>
#include<outputconnector.h>
#include<inputconnector.h>

class EquipmentRender
{
public:
<<<<<<< HEAD
    EquipmentRender(QVector <OutputConnector*> outputs, QVector <InputConnector*> input);
=======
    EquipmentRender(QVector <OutputConnector*> outputs, QVector <InputConnector*> inputs);
>>>>>>> Network/master

    Body *body;
    QVector <OutputConnector*> outputs;
    QVector <InputConnector*> inputs;
};

#endif // EQUIPMENTRENDER_H
