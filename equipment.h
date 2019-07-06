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

    void SetId(int &nextEquipmentId, int &nextConnectorId);
    EquipmentRender *render;
};

#endif // EQUIPMENT_H
