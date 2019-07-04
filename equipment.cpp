#include "equipment.h"

//Equipment::Equipment()
//{
//    render = new EquipmentRender();
//}
Equipment::Equipment(QVector <OutputConnector*> outputs, QVector <InputConnector*> inputs)
{
    render = new EquipmentRender(outputs, inputs);
}

Equipment::~Equipment()
{
    delete render;
}
