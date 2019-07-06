#ifndef FILEORGANIZER_H
#define FILEORGANIZER_H

#include "equipment.h"

class FileOrganizer
{
public:
    FileOrganizer(const QString &projectName);
    bool createProject();
    int openProject();
    bool addEquipments();
    bool deleteEquipments();
    void createEquipment(Equipment *equipment);
    QVector <Equipment*> getEquipmentsInProject();
    QVector <Equipment*> getEquipmentsInLibrary();

private:
    int openLibrary();

private:
    const QString mainPath;
    QString projectName;
    QString projectPath;
    QVector <Equipment*> equipmentsInProject;
    QVector <Equipment*> equipmentsInLibrary;
};

#endif // FILEORGANIZER_H
