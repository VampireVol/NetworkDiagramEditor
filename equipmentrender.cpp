#include "equipmentrender.h"

EquipmentRender::EquipmentRender(QVector <OutputConnector*> outputs, QVector <InputConnector*> inputs)
    : outputs(outputs), inputs(inputs)
{
    body = new Body(outputs.size() > inputs.size() ? outputs.size() : inputs.size());
    for(int i = 0; i < outputs.size(); ++i)
    {
        outputs[i]->setParentItem(body);
        outputs[i]->setPos(60, 20 + i * 40);
    }
    for(int i = 0; i < inputs.size(); ++i)
    {
        inputs[i]->setParentItem(body);
        inputs[i]->setPos(0, 20 + i * 40);
    }
}
