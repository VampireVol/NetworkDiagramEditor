#ifndef FILEORGANIZER_H
#define FILEORGANIZER_H

#include "equipment.h"
#include "QDir"
#include "QFile"

class FileOrganizer : public QDir
{
public:
    FileOrganizer(QString projectName, QString projectPath, QString mainPath, QString libraryPath);
    int createProject();
    int openProject();
    //bool addEquipments();
    void deleteEquipmentFromProject(QString name);
    void deleteEquipmentFromLibrary(QString name);
    void addEquipmentToProject(Equipment *equipment);
    void addEquipmentToLibrary(Equipment *equipment);
    bool saveScheme(QVector<Equipment*> equipmentsInScheme);
    int editProjectPath(QVector<Equipment*> equipmentsInScheme, QString newProjectPath);
    QVector <Equipment*> getEquipmentsInProject();
    QVector <Equipment*> getEquipmentsInLibrary();
    QVector <Equipment*> getEquipmentsInScheme();

private:
    void addEquipment(Equipment *equipment, QString path);
    bool openEquipments();
    bool openScheme();
    bool openLibrary();
    bool removeDir(const QString & dirName);
    QVector <Connector*> setConnectors(QVector <int> colors);

private:
    QString mainPath;
    QString projectName;
    QString projectPath;
    QString libraryPath;
    QVector <Equipment*> equipmentsInProject;
    QVector <Equipment*> equipmentsInLibrary;
    QVector <Equipment*> equipmentsInScheme;
};

#endif // FILEORGANIZER_H
