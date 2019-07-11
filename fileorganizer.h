#ifndef FILEORGANIZER_H
#define FILEORGANIZER_H

#include "equipment.h"
#include "QDir"
#include "QFile"

/// Класс, управляющий файловой системой (сохранением и открытием проекта)
class FileOrganizer : public QDir
{
public:
    FileOrganizer(QString projectName, QString projectPath, QString mainPath, QString libraryPath); ///инициализация имени проекта, пути проекта, пути библиотеки, главного пути, из которого запускается приложение
    int createProject(); /// создание проекта, создает основные директории
    int openProject(); /// открытие проекта, загружает библиотеку, оборудование и схему
    void deleteEquipmentFromProject(QString name); /// Удаление оборудования из проекта
    void deleteEquipmentFromLibrary(QString name); /// Удаление оборудования из библиотеки
    void addEquipmentToProject(Equipment *equipment); /// добавление оборудования в проект
    void addEquipmentToLibrary(Equipment *equipment); /// добавление оборудования в библиотеку
    bool saveScheme(QVector<Equipment*> equipmentsInScheme); ///сохранение схемы
    int editProjectPath(QVector<Equipment*> equipmentsInScheme, QString newProjectPath); /// изменение пути проекта (сохранение как)
    QVector <Equipment*> getEquipmentsInProject(); /// возвращает оборудование в проекте
    QVector <Equipment*> getEquipmentsInLibrary(); /// возвращает оборудование в библотеке
    QVector <Equipment*> getEquipmentsInScheme(); /// возвращает оборудование на схеме

private:
    void addEquipment(Equipment *equipment, QString path); // добавление оборудования в проект
    bool openEquipments(); // загрузка оборудование из проекта
    bool openScheme(); // загрузка схемы
    bool openLibrary(); // загрузка оборудования из библиотки
    bool removeDir(const QString & dirName);
    QVector <Connector*> setConnectors(QVector <int> colors); //установка типов коннекторов

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
