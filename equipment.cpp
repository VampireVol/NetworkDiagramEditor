#include "equipment.h"

//Equipment::Equipment()
//{
//    render = new EquipmentRender();
//}
Equipment::Equipment(QVector <OutputConnector*> outputs, QVector <InputConnector*> inputs)
    : labelId(nullptr), equipmentId(0)
{
    render = new EquipmentRender(outputs, inputs);
}

Equipment::~Equipment()
{
    delete render;
}

void Equipment::SetId(int &nextEquipmentId, int &nextConnectorId)
{
    equipmentId = nextEquipmentId++;
    int outputSize = render->outputs.size();
    int inputSize = render->inputs.size();
    for(int i = 0; i < inputSize; ++i)
    {
        render->inputs[i]->equipmentId = equipmentId;
        render->inputs[i]->connectorId = nextConnectorId++;
    }
    for(int i = 0; i < outputSize; ++i)
    {
        render->outputs[i]->equipmentId = equipmentId;
        render->outputs[i]->connectorId = nextConnectorId++;
    }
}
