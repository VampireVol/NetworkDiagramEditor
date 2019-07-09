#ifndef EQUIPMENT_H
#define EQUIPMENT_H

<<<<<<< HEAD
#include <QVector>
#include <QString>
#include <equipmentrender.h>
=======
#include<QVector>
#include<QString>
#include<equipmentrender.h>
>>>>>>> Network/master
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
<<<<<<< HEAD
    void SetId(int &nextEquipmentId, int &nextConnectorId);
    EquipmentRender *render;
=======
    EquipmentRender *render;

public:
    void SetId(int &nextEquipmentId);

public:
    static Equipment* CreateCopy(Equipment *equipment);
    static bool Contains(QVector <Equipment*> equipments, Equipment *equipment);
>>>>>>> Network/master
};

#endif // EQUIPMENT_H
