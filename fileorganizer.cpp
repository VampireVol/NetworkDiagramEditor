#include "fileorganizer.h"
#include "QFile"
#include "QDir"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include "QMessageBox"
#include <Qt>

FileOrganizer::FileOrganizer(const QString &projectName)
    :mainPath("V:/study/QtProjects/DiagramNetworkEditor"), projectName(projectName)
{
    projectPath = mainPath + "/projects" + "/" + projectName;
}

int FileOrganizer::openProject()
{
    QDir dir(projectPath);
    if(!dir.exists())
        return 1;

    dir.cd("equipments");
    QString filePath;
    QStringList entryList = dir.entryList();
    QDir::setCurrent(projectPath + "/equipments");
    for(int i = 2; i < entryList.size(); i++)
    {
        filePath = entryList[i];
        QFile file(filePath);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            return 2;
        else{
             QString equipmentName;
             int equipmentId;
             QVector <OutputConnector*> outputs;
             QVector <InputConnector*> inputs;

             QXmlStreamReader xmlReader;
             xmlReader.setDevice(&file);
             while(xmlReader.name() != "equipment")
                 xmlReader.readNext();
             equipmentId = xmlReader.attributes().begin()->value().toInt();

             while(xmlReader.name() != "name")
                 xmlReader.readNext();
             equipmentName = xmlReader.readElementText();

             while(xmlReader.name() != "inputs")
                 xmlReader.readNext();
             QVector <int> colors_in;//Qt::GlobalColor
             QVector <int> identificators_in;
             while(xmlReader.name() != "outputs")
             {
                 if(xmlReader.name() == "connector")
                 {
                     foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                     {
                         if(attr.name().toString() == "color")
                             colors_in.push_back(attr.value().toInt());
                         else if(attr.name().toString() == "id")
                             identificators_in.push_back(attr.value().toInt());
                     }
                 }
                 xmlReader.readNext();
             }

             QVector <int> colors_out;//Qt::GlobalColor
             QVector <int> identificators_out;
             while(xmlReader.atEnd())
             {
                 if(xmlReader.name() == "connector")
                 {
                     if(xmlReader.name() == "connector")
                     {
                         foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                         {
                             if(attr.name().toString() == "color")
                                 colors_out.push_back(attr.value().toInt());
                             else if(attr.name().toString() == "id")
                                 identificators_out.push_back(attr.value().toInt());
                         }
                     }
                 }
                 xmlReader.readNext();
             }

             for(int i = 0; i < colors_in.size(); i++)
             {
                 switch(colors_in[i])
                 {
                 case Qt::red:
                     {
                         inputs.push_back(new InputConnectorRed());
                         break;
                     }
                 case Qt::blue:
                 {
                     inputs.push_back(new InputConnectorBlue());
                     break;
                 }
                 case Qt::green:
                 {
                     inputs.push_back(new InputConnectorGreen());
                     break;
                 }
                 case Qt::cyan:
                 {
                     inputs.push_back(new InputConnectorCyan());
                     break;
                 }
                 case Qt::yellow:
                 {
                     inputs.push_back(new InputConnectorYellow());
                     break;
                 }
                 default:
                 {
                     break;
                 }
                 }
             }
             for(int i = 0; i < colors_out.size(); i++)
             {
                 switch(colors_out[i])
                 {
                 case Qt::red:
                     {
                         inputs.push_back(new InputConnectorRed());
                         break;
                     }
                 case Qt::blue:
                 {
                     outputs.push_back(new OutputConnectorBlue());
                     break;
                 }
                 case Qt::green:
                 {
                     outputs.push_back(new OutputConnectorGreen());
                     break;
                 }
                 case Qt::cyan:
                 {
                     outputs.push_back(new OutputConnectorCyan());
                     break;
                 }
                 case Qt::yellow:
                 {
                     outputs.push_back(new OutputConnectorYellow());
                     break;
                 }
                 default:
                 {
                     break;
                 }
                 }
             }

             for(int i = 0; i < identificators_in.size(); i++)
             {
                 inputs[i]->connectorId = identificators_in[i];
                 inputs[i]->equipmentId = equipmentId;
             }
             for(int i = 0; i < identificators_out.size(); i++)
             {
                 outputs[i]->connectorId = identificators_out[i];
                 outputs[i]->equipmentId = equipmentId;
             }

             Equipment* equipment = new Equipment(outputs, inputs);
             equipment->name = equipmentName;
             equipment->equipmentId = equipmentId;
             equipment->setText(equipmentName);
             equipmentsInProject.push_back(equipment);
        }
        file.close();
    }

    int check = openLibrary();
    return check;
}

QVector <Equipment*> FileOrganizer::getEquipmentsInProject()
{
    return equipmentsInProject;
}

QVector <Equipment*> FileOrganizer::getEquipmentsInLibrary()
{
    return equipmentsInLibrary;
}

bool FileOrganizer::createProject()
{
    QDir dir(mainPath + "/projects");
    if(!dir.exists())
        return false;

    dir.mkdir(projectName);
    dir.cd(projectPath);
    dir.mkdir("equipments");

    QFile file(projectPath + "/connections.xml");
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("connections");
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();

    return true;
}

void FileOrganizer::createEquipment(Equipment *equipment)
{
    QDir::setCurrent(projectPath + "/equipments");
    QFile file;
    QString fileName = equipment->text() + ".xml";
    file.setFileName(fileName);
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();

    //Вопрос с аттрибутами
    xmlWriter.writeStartElement("equipment");
    xmlWriter.writeAttribute("id", QString::number(equipment->equipmentId));
    xmlWriter.writeStartElement("name");
    xmlWriter.writeCharacters(equipment->name);
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("inputs");
    for(int i = 0; i < equipment->render->inputs.size(); i++)
    {
        xmlWriter.writeStartElement("connector");
        xmlWriter.writeAttribute("color", QString::number(equipment->render->inputs[i]->GetColor()));
        xmlWriter.writeAttribute("id", QString::number(equipment->render->inputs[i]->connectorId));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("outputs");
    for(int i = 0; i < equipment->render->outputs.size(); i++)
    {
        xmlWriter.writeStartElement("connector");
        xmlWriter.writeAttribute("color", QString::number(equipment->render->outputs[i]->GetColor()));
        xmlWriter.writeAttribute("id", QString::number(equipment->render->outputs[i]->connectorId));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();

    file.close();   // Закрываем файл
    QFile::copy(fileName, mainPath + "/library/" + fileName);
    equipmentsInProject.push_back(equipment);
}

int FileOrganizer::openLibrary()
{
    QDir dir(mainPath + "/library");
    if(!dir.exists())
        return 3;

    QString filePath;
    QStringList entryList = dir.entryList();
    QDir::setCurrent(mainPath + "/library");
    for(int i = 2; i < entryList.size(); i++)
    {
        filePath = entryList[i];
        QFile file(filePath);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            return 3;
        else{
             QString equipmentName;
             int equipmentId;
             QVector <OutputConnector*> outputs;
             QVector <InputConnector*> inputs;

             QXmlStreamReader xmlReader;
             xmlReader.setDevice(&file);
             while(xmlReader.name() != "equipment")
                 xmlReader.readNext();
             equipmentId = xmlReader.attributes().begin()->value().toInt();

             while(xmlReader.name() != "name")
                 xmlReader.readNext();
             equipmentName = xmlReader.readElementText();

             while(xmlReader.name() != "inputs")
                 xmlReader.readNext();
             QVector <int> colors_in;//Qt::GlobalColor
             QVector <int> identificators_in;
             while(xmlReader.name() != "outputs")
             {
                 if(xmlReader.name() == "connector")
                 {
                     foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                     {
                         if(attr.name().toString() == "color")
                             colors_in.push_back(attr.value().toInt());
                         else if(attr.name().toString() == "id")
                             identificators_in.push_back(attr.value().toInt());
                     }
                 }
                 xmlReader.readNext();
             }

             QVector <int> colors_out;//Qt::GlobalColor
             QVector <int> identificators_out;
             while(xmlReader.atEnd())
             {
                 if(xmlReader.name() == "connector")
                 {
                     if(xmlReader.name() == "connector")
                     {
                         foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                         {
                             if(attr.name().toString() == "color")
                                 colors_out.push_back(attr.value().toInt());
                             else if(attr.name().toString() == "id")
                                 identificators_out.push_back(attr.value().toInt());
                         }
                     }
                 }
                 xmlReader.readNext();
             }

             for(int i = 0; i < colors_in.size(); i++)
             {
                 switch(colors_in[i])
                 {
                 case Qt::red:
                     {
                         inputs.push_back(new InputConnectorRed());
                         break;
                     }
                 case Qt::blue:
                 {
                     inputs.push_back(new InputConnectorBlue());
                     break;
                 }
                 case Qt::green:
                 {
                     inputs.push_back(new InputConnectorGreen());
                     break;
                 }
                 case Qt::cyan:
                 {
                     inputs.push_back(new InputConnectorCyan());
                     break;
                 }
                 case Qt::yellow:
                 {
                     inputs.push_back(new InputConnectorYellow());
                     break;
                 }
                 default:
                 {
                     break;
                 }
                 }
             }
             for(int i = 0; i < colors_out.size(); i++)
             {
                 switch(colors_out[i])
                 {
                 case Qt::red:
                     {
                         inputs.push_back(new InputConnectorRed());
                         break;
                     }
                 case Qt::blue:
                 {
                     outputs.push_back(new OutputConnectorBlue());
                     break;
                 }
                 case Qt::green:
                 {
                     outputs.push_back(new OutputConnectorGreen());
                     break;
                 }
                 case Qt::cyan:
                 {
                     outputs.push_back(new OutputConnectorCyan());
                     break;
                 }
                 case Qt::yellow:
                 {
                     outputs.push_back(new OutputConnectorYellow());
                     break;
                 }
                 default:
                 {
                     break;
                 }
                 }
             }

             for(int i = 0; i < identificators_in.size(); i++)
             {
                 inputs[i]->connectorId = identificators_in[i];
                 inputs[i]->equipmentId = equipmentId;
             }
             for(int i = 0; i < identificators_out.size(); i++)
             {
                 outputs[i]->connectorId = identificators_out[i];
                 outputs[i]->equipmentId = equipmentId;
             }

             Equipment* equipment = new Equipment(outputs, inputs);
             equipment->name = equipmentName;
             equipment->equipmentId = equipmentId;
             equipment->setText(equipmentName);
             equipmentsInLibrary.push_back(equipment);
        }
        file.close();
    }

    return 0;
}
