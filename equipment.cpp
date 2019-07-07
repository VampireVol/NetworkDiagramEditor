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

void Equipment::SetId(int &nextEquipmentId)
{
    int nextConnectorId = 1;
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

Equipment* Equipment::CreateCopy(Equipment *equipment)
{
    QVector <OutputConnector*> outputs;
    QVector <InputConnector*> inputs;
    QString name = equipment->name;
    int outputSize = equipment->render->outputs.size();
    int inputSize = equipment->render->inputs.size();
    for(int i = 0; i < outputSize; ++i)
    {
        Qt::GlobalColor color = equipment->render->outputs[i]->GetColor();
        switch (color)
        {
        case Qt::red:
        {
            outputs.push_back(new OutputConnectorRed());
            break;
        }
        case Qt::blue:
        {
            outputs.push_back(new OutputConnectorBlue());
            break;
        }
        case Qt::green:
        {
            outputs.push_back(new OutputConnectorGreen());
            break;
        }
        case Qt::cyan:
        {
            outputs.push_back(new OutputConnectorCyan());
            break;
        }
        case Qt::yellow:
        {
            outputs.push_back(new OutputConnectorYellow());
            break;
        }
        default:
            //сюда надо воткнуть месседжбокс который говорит, что что-то пошло не так
            break;
        }
    }
    for(int i = 0; i < inputSize; ++i)
    {
        Qt::GlobalColor color = equipment->render->inputs[i]->GetColor();
        switch (color)
        {
        case Qt::red:
        {
            inputs.push_back(new InputConnectorRed());
            break;
        }
        case Qt::blue:
        {
            inputs.push_back(new InputConnectorBlue());
            break;
        }
        case Qt::green:
        {
            inputs.push_back(new InputConnectorGreen());
            break;
        }
        case Qt::cyan:
        {
            inputs.push_back(new InputConnectorCyan());
            break;
        }
        case Qt::yellow:
        {
            inputs.push_back(new InputConnectorYellow());
            break;
        }
        default:
            //сюда надо воткнуть месседжбокс который говорит, что что-то пошло не так
            break;
        }
    }
    Equipment *copy = new Equipment(outputs, inputs);
    copy->name = equipment->name;

    for(int i = 0; i < inputSize; ++i)
    {
        copy->render->inputs[i]->connectorId = equipment->render->inputs[i]->connectorId;
    }
    for(int i = 0; i < outputSize; ++i)
    {
        copy->render->outputs[i]->connectorId = equipment->render->outputs[i]->connectorId;
    }

    return copy;
}

bool Equipment::Contains(QVector<Equipment *> equipments, Equipment *equipment)
{
    foreach(Equipment *eq, equipments)
    {
        if(equipment->name == eq->name)
            return true;
    }

    return false;
}
