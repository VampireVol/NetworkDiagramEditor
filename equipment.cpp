#include "equipment.h"

//Equipment::Equipment()
//{
//    render = new EquipmentRender();
//}
Equipment::Equipment(QVector <Connector*> connector)
    : labelId(nullptr), equipmentId(0)
{
    render = new EquipmentRender(connector);
}

Equipment::~Equipment()
{
    delete render;
}

void Equipment::SetId(int &nextEquipmentId)
{
    int nextConnectorId = 1;
    equipmentId = nextEquipmentId++;
    int connectorSize = render->connectors.size();
    for(int i = 0; i < connectorSize; ++i)
    {
        render->connectors[i]->equipmentId = equipmentId;
        render->connectors[i]->connectorId = nextConnectorId++;
    }
}

Equipment* Equipment::CreateCopy(Equipment *equipment)
{
    QVector <Connector*> connectors;
    QString name = equipment->name;
    int connectorSize = equipment->render->connectors.size();
    for(int i = 0; i < connectorSize; ++i)
    {
        Qt::GlobalColor color = equipment->render->connectors[i]->GetColor();
        switch (color)
        {
        case Qt::red:
        {
            connectors.push_back(new ConnectorRed());
            break;
        }
        case Qt::blue:
        {
            connectors.push_back(new ConnectorBlue());
            break;
        }
        case Qt::green:
        {
            connectors.push_back(new ConnectorGreen());
            break;
        }
        case Qt::cyan:
        {
            connectors.push_back(new ConnectorCyan());
            break;
        }
        case Qt::yellow:
        {
            connectors.push_back(new ConnectorYellow());
            break;
        }
        default:
            //сюда надо воткнуть месседжбокс который говорит, что что-то пошло не так
            break;
        }
    }
    Equipment *copy = new Equipment(connectors);
    copy->name = equipment->name;
    copy->equipmentId = equipment->equipmentId;

    for(int i = 0; i < connectorSize; ++i)
    {
        copy->render->connectors[i]->connectorId = equipment->render->connectors[i]->connectorId;
        copy->render->connectors[i]->equipmentId = copy->equipmentId;
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
