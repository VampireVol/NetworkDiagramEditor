#ifndef FILEORGANIZER_H
#define FILEORGANIZER_H

#include "equipment.h"
#include "QDir"
#include "QFile"

class FileOrganizer : public QDir
{
public:
    FileOrganizer(const QString &projectName);
    int createProject();
    int openProject();
    //bool addEquipments();
    void deleteEquipment(QString name);
    void addEquipment(Equipment *equipment);
    QVector <Equipment*> getEquipmentsInProject();
    QVector <Equipment*> getEquipmentsInLibrary();

private:
    int openLibrary();

private:
    QString mainPath;
    QString projectName;
    QString projectPath;
    QVector <Equipment*> equipmentsInProject;
    QVector <Equipment*> equipmentsInLibrary;
};

#endif // FILEORGANIZER_H
