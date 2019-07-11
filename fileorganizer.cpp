#include "fileorganizer.h"
#include "QFile"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include "QMessageBox"
#include <Qt>

FileOrganizer::FileOrganizer(QString projectName, QString projectPath, QString mainPath, QString libraryPath)
    :mainPath(mainPath), projectName(projectName), projectPath(projectPath), libraryPath(libraryPath)
{
}

int FileOrganizer::openProject()
{
    this->setPath(mainPath);
    if(!this->exists("library"))
        this->mkdir("library");

    this->setPath(projectPath);
    projectName = this->dirName();
    if(!(this->exists("equipments") && this->exists("scheme.xml")))
        return 1;
    if(!openEquipments())
        return 2;
    if(!openLibrary())
        return 3;
    if(!openScheme())
        return 4;

    return 0;
}

QVector <Equipment*> FileOrganizer::getEquipmentsInProject()
{
    return equipmentsInProject;
}

QVector <Equipment*> FileOrganizer::getEquipmentsInLibrary()
{
    return equipmentsInLibrary;
}

QVector <Equipment*> FileOrganizer::getEquipmentsInScheme()
{
    return equipmentsInScheme;
}

int FileOrganizer::createProject()
{
    this->setPath(mainPath);
    if(!this->exists("library"))
        this->mkdir("library");

    this->setPath(projectPath);
    if(this->exists(projectName))
        return 1;

    this->mkdir(projectName);
    projectPath = projectPath + "/" + projectName;
    this->setPath(projectPath);
    this->mkdir("equipments");

    QFile file(projectPath + "/scheme.xml");
    if (!file.open(QIODevice::WriteOnly))
        return 3;

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("scheme");
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();

    equipmentsInProject.clear();
    equipmentsInLibrary.clear();
    equipmentsInScheme.clear();

    if(!openLibrary())
        return 2;

    return 0;
}

bool FileOrganizer::removeDir(const QString & dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    return result;
}

int FileOrganizer::editProjectPath(QVector<Equipment*> equipmentsInScheme, QString newProjectPath)
{
    if(newProjectPath == projectPath)
        return 1;
    this->setPath(projectPath);
    this->setPath(newProjectPath);
    if(this->exists(projectName))
        return 2;

    saveScheme(equipmentsInScheme);

    this->mkdir(projectName);
    newProjectPath = newProjectPath + "/" + projectName;
    this->setPath(newProjectPath);
    this->mkdir("equipments");

    if(!QFile::copy(projectPath + "/scheme.xml", newProjectPath + "/scheme.xml"))
        return 2;
    this->setPath(projectPath + "/equipments");
    QStringList entryList = this->entryList();
    for(int i = 2; i < entryList.size(); i++)
    {
        if(!QFile::copy(projectPath + "/equipments/" + entryList[i], newProjectPath + "/equipments/" + entryList[i]))
            return 3;
    }

    this->cdUp();
    this->removeRecursively();
    //this->cdUp();
    //if(!this->rmdir(projectName))
    //    return false;
    projectPath = newProjectPath;
    return 0;
}

void FileOrganizer::addEquipment(Equipment *equipment, QString path)
{
    FileOrganizer::setCurrent(path);
    QFile file(equipment->name + ".xml");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("equipment");
    xmlWriter.writeStartElement("name");
    xmlWriter.writeCharacters(equipment->name);
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("connectors");
    foreach(Connector* connector, equipment->render->connectors)
    {
        xmlWriter.writeStartElement("connector");
        xmlWriter.writeAttribute("color", QString::number(connector->GetColor()));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
}

void FileOrganizer::addEquipmentToProject(Equipment *equipment)
{
    addEquipment(equipment, projectPath + "/equipments");
    equipmentsInProject.push_back(Equipment::CreateCopy(equipment));
}

void FileOrganizer::addEquipmentToLibrary(Equipment *equipment)
{
    addEquipment(equipment, libraryPath);
    equipmentsInLibrary.push_back(Equipment::CreateCopy(equipment));
}

bool FileOrganizer::saveScheme(QVector<Equipment *> equipmentsInScheme)
{
    this->equipmentsInScheme.clear();
    foreach(Equipment* equipment, equipmentsInScheme)
        this->equipmentsInScheme.push_back(Equipment::CreateCopy(equipment));

    FileOrganizer::setCurrent(projectPath);
    QFile file("scheme.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("scheme");
    foreach(Equipment* equipment, this->equipmentsInScheme)
    {
        xmlWriter.writeStartElement("equipment");
        xmlWriter.writeAttribute("id", QString::number(equipment->equipmentId));
        //xmlWriter.writeStartElement("name");
        //xmlWriter.writeCharacters(equipment->name);
        //xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("connectors");
        foreach(Connector* connector, equipment->render->connectors)
        {
            xmlWriter.writeStartElement("connector");
            xmlWriter.writeAttribute("id", QString::number(connector->connectorId));
            xmlWriter.writeAttribute("color", QString::number(connector->GetColor()));
            xmlWriter.writeStartElement("link");
            /*if(!connector->IsNull())
            {
                xmlWriter.writeAttribute("eq_id", QString::number(connector->GetLink()->equipmentId));
                xmlWriter.writeAttribute("conn_id", QString::number(connector->GetLink()->connectorId));
            }
            else {
                xmlWriter.writeAttribute("eq_id", QString::number(0));
                xmlWriter.writeAttribute("conn_id", QString::number(0));
            }*/
            xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();

    return true;
}

void FileOrganizer::deleteEquipmentFromProject(QString name)
{
    this->setPath(projectPath + "/equipments");
    this->remove(name + ".xml");
    for(int i = 0; i < equipmentsInProject.size(); i++)
    {
        if(equipmentsInProject[i]->name == name)
            equipmentsInProject.remove(i);
    }
}

void FileOrganizer::deleteEquipmentFromLibrary(QString name)
{
    this->setPath(libraryPath);
    this->remove(name + ".xml");
    for(int i = 0; i < equipmentsInLibrary.size(); i++)
    {
        if(equipmentsInLibrary[i]->name == name)
            equipmentsInLibrary.remove(i);
    }
}

bool FileOrganizer::openEquipments()
{
    FileOrganizer::setCurrent(projectPath + "/equipments");
    this->setPath(projectPath);
    if(!this->exists("equipments"))
        return false;
    this->setPath(projectPath + "/equipments");
    QString filePath;
    QStringList entryList = this->entryList();
    equipmentsInProject.clear();
    for(int i = 2; i < entryList.size(); i++)
    {
        filePath = entryList[i];
        QFile file(filePath);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            return false;
        else{
             QString equipmentName;
             QVector <Connector*> connectors;

             QXmlStreamReader xmlReader;
             xmlReader.setDevice(&file);
             xmlReader.readNext();
             xmlReader.readNext();
             if(xmlReader.name() != "equipment")
                 continue;

             while(xmlReader.name() != "name")
                 xmlReader.readNext();
             equipmentName = xmlReader.readElementText();
             while(xmlReader.name() != "connectors")
                 xmlReader.readNext();
             QVector <int> colors;
             while(!(xmlReader.name() == "connectors" && xmlReader.isEndElement()))
             {
                 if(xmlReader.name() == "connector")
                 {
                     foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                     {
                         colors.push_back(attr.value().toInt());
                     }
                 }
                 xmlReader.readNext();
             }

             connectors = setConnectors(colors);

             Equipment* equipment = new Equipment(connectors);
             equipment->name = equipmentName;
             equipmentsInProject.push_back(equipment);
        }
        file.close();
    }

    return true;
}

bool FileOrganizer::openScheme()
{
    FileOrganizer::setCurrent(projectPath);
    this->setPath(projectPath);
    if(!this->exists("scheme.xml"))
        return false;

    QFile file("scheme.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    else {
        equipmentsInScheme.clear();
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        xmlReader.readNext();
        if(xmlReader.name() != "scheme")
            return false;
        QVector <Connector*> connectors;
        QVector <int> colors;
        QVector <int> identificators;
        QVector <int> linkConnIdentificators;
        QVector <int> linkEqIdentificators;
        QVector <QVector <int>> allLinkConnId;
        QVector <QVector <int>> allLinkEqId;
        int equipmentId;
        while(!xmlReader.atEnd())
        {
            if(xmlReader.name() == "equipment" && xmlReader.isStartElement())
            {
                connectors.clear();
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    equipmentId = attr.value().toInt();
                }
                colors.clear();
                identificators.clear();
                while(xmlReader.name() != "connectors")
                    xmlReader.readNext();
                if(xmlReader.name() == "connectors")
                {
                    while(!(xmlReader.name() == "connectors" && xmlReader.isEndElement()))
                    {
                        if(xmlReader.name() == "connector")
                        {
                            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                            {
                                if(attr.name().toString() == "id")
                                    identificators.push_back(attr.value().toInt());
                                else if(attr.name().toString() == "color")
                                    colors.push_back(attr.value().toInt());
                            }
                            /*while(xmlReader.name() != "link")
                                xmlReader.readNext();
                            if(xmlReader.name() == "link")
                            {
                                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                                {
                                    if(attr.name().toString() == "conn_id")
                                        linkConnIdentificators.push_back(attr.value().toInt());
                                    else if(attr.name().toString() == "eq_id")
                                        linkEqIdentificators.push_back(attr.value().toInt());
                                }
                            }*/
                        }
                        xmlReader.readNext();
                    }
                }

                connectors = setConnectors(colors);
                Equipment* equipment = new Equipment(connectors);
                equipment->equipmentId = equipmentId;
                for(int i = 0; i < identificators.size(); i++)
                {
                    equipment->render->connectors[i]->connectorId = identificators[i];
                    equipment->render->connectors[i]->equipmentId = equipmentId;
                }
                equipmentsInScheme.push_back(equipment);
                allLinkEqId.push_back(linkEqIdentificators);
                allLinkConnId.push_back(linkConnIdentificators);
            }
            xmlReader.readNext();
        }

        for(int i = 0; i < equipmentsInScheme.size(); i++)
        {
            for(int j = 0; j < allLinkEqId[i].size(); j++)
            {
                if(allLinkEqId[i][j] != 0)
                {
                    int connId = allLinkConnId[i][j];
                    int eqId = allLinkEqId[i][j];
                    equipmentsInScheme[i]->render->connectors[j]->SetLink(equipmentsInScheme[eqId]->render->connectors[connId]);
                }
            }
        }

        file.close();
    }

    return true;
}

bool FileOrganizer::openLibrary()
{
    FileOrganizer::setCurrent(libraryPath);
    this->setPath(mainPath);
    if(!this->exists("library"))
        return false;
    this->setPath(libraryPath);

    QString filePath;
    QStringList entryList = this->entryList();
    equipmentsInLibrary.clear();
    for(int i = 2; i < entryList.size(); i++)
    {
        filePath = entryList[i];
        QFile file(filePath);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            continue;
        else{
            QString equipmentName;
            QVector <Connector*> connectors;

            QXmlStreamReader xmlReader;
            xmlReader.setDevice(&file);
            xmlReader.readNext();
            xmlReader.readNext();
            if(xmlReader.name() != "equipment")
                return false;

            while(xmlReader.name() != "name")
                xmlReader.readNext();
            equipmentName = xmlReader.readElementText();
            while(xmlReader.name() != "connectors")
                xmlReader.readNext();
            QVector <int> colors;
            while(!(xmlReader.name() == "connectors" && xmlReader.isEndElement()))
            {
                if(xmlReader.name() == "connector")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        colors.push_back(attr.value().toInt());
                    }
                }
                xmlReader.readNext();
            }

            connectors = setConnectors(colors);

            Equipment* equipment = new Equipment(connectors);
            equipment->name = equipmentName;
            equipmentsInLibrary.push_back(equipment);
        }
        file.close();
    }

    return true;
}

QVector <Connector*> FileOrganizer::setConnectors(QVector<int> colors)
{
    QVector <Connector*> connectors;

    foreach(int color, colors)
    {
        switch(color)
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
        {
            break;
        }
        }
    }

    return connectors;
}
