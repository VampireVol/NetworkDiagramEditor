#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include<QVector>
#include<QString>
#include<equipmentrender.h>
#include <QListWidgetItem>

class Equipment : public QListWidgetItem
{
public:
    //Equipment();
    Equipment(QVector <OutputConnector*> outputs, QVector <InputConnector*> inputs);
    ~Equipment();
    QString name;
    int equipmentId;

    EquipmentRender *render;
};

#endif // EQUIPMENT_H
