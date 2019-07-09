#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include<QVector>
#include<QString>
#include<equipmentrender.h>
#include <QListWidgetItem>
#include <QLabel>
#include <QGraphicsProxyWidget>

class Equipment : public QListWidgetItem
{
public:
    //Equipment();
    Equipment(QVector <OutputConnector*> outputs, QVector <InputConnector*> inputs);
    ~Equipment();
    QLabel *labelId;
    QString name;
    int equipmentId;
    EquipmentRender *render;

public:
    void SetId(int &nextEquipmentId);

public:
    static Equipment* CreateCopy(Equipment *equipment);
    static bool Contains(QVector <Equipment*> equipments, Equipment *equipment);
};

#endif // EQUIPMENT_H
