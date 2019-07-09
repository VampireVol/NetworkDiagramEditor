#ifndef FILEORGANIZER_H
#define FILEORGANIZER_H

#include "equipment.h"
#include "QDir"
#include "QFile"

class FileOrganizer : public QDir
{
public:
    FileOrganizer(QString &projectName, QString mainPath);
    bool createProject();
    int openProject();
    //bool addEquipments();
    void deleteEquipment(QString name);
    void addEquipment(Equipment *equipment);
    bool saveScheme(QVector<Equipment*> equipmentsInScheme);
    QVector <Equipment*> getEquipmentsInProject();
    QVector <Equipment*> getEquipmentsInLibrary();
    QVector <Equipment*> getEquipmentsInScheme();

private:
    bool openEquipments();
    bool openScheme();
    bool openLibrary();
    QVector <InputConnector*> setInputs(QVector <int> colors_in);
    QVector <OutputConnector*> setOutputs(QVector <int> colors_out);

private:
    QString mainPath;
    QString projectName;
    QString projectPath;
    QVector <Equipment*> equipmentsInProject;
    QVector <Equipment*> equipmentsInLibrary;
    QVector <Equipment*> equipmentsInScheme;
};

#endif // FILEORGANIZER_H
