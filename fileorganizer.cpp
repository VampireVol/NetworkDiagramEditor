#include "fileorganizer.h"
#include "QFile"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include "QMessageBox"
#include <Qt>

FileOrganizer::FileOrganizer(QString &projectName, QString mainPath)
    :mainPath(mainPath), projectName(projectName)
{
    projectPath = mainPath + "/projects/" + projectName;
}

int FileOrganizer::openProject()
{
    this->setPath(mainPath);
    if(!this->exists("projects"))
        this->mkdir("projects");
    if(!this->exists("library"))
        this->mkdir("library");

    this->setPath(projectPath);
    if(!this->exists())
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

bool FileOrganizer::createProject()
{
    this->setPath(mainPath);
    if(!this->exists("projects"))
        this->mkdir("projects");
    if(!this->exists("library"))
        this->mkdir("library");

    this->setPath(mainPath + "/projects");
    this->mkdir(projectName);
    this->cd(projectPath);
    this->mkdir("equipments");

    QFile file(projectPath + "/scheme.xml");
    if (!file.open(QIODevice::WriteOnly))
        return 1;

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

    if(openLibrary())
        return true;
    else
        return false;
}

void FileOrganizer::addEquipment(Equipment *equipment)
{
    FileOrganizer::setCurrent(projectPath + "/equipments");
    QFile file(equipment->text() + ".xml");
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("equipment");
    //xmlWriter.writeAttribute("id", QString::number(equipment->equipmentId));
    xmlWriter.writeStartElement("name");
    xmlWriter.writeCharacters(equipment->name);
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("inputs");
    foreach(InputConnector* connector, equipment->render->inputs)
    {
        xmlWriter.writeStartElement("connector");
        xmlWriter.writeAttribute("color", QString::number(connector->GetColor()));
        //xmlWriter.writeAttribute("id", QString::number(equipment->render->inputs[i]->connectorId));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("outputs");
    foreach(InputConnector* connector, equipment->render->inputs)
    {
        xmlWriter.writeStartElement("connector");
        xmlWriter.writeAttribute("color", QString::number(connector->GetColor()));
        //xmlWriter.writeAttribute("id", QString::number(equipment->render->outputs[i]->connectorId));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
    QFile::copy(file.fileName(), mainPath + "/library/" + file.fileName());
    equipmentsInProject.push_back(Equipment::CreateCopy(equipment));
    equipmentsInLibrary.push_back(Equipment::CreateCopy(equipment));
}

bool FileOrganizer::saveScheme(QVector<Equipment *> equipmentsInScheme)
{
    this->equipmentsInScheme.clear();
    foreach(Equipment* equipment, equipmentsInScheme)
        this->equipmentsInScheme.push_back(Equipment::CreateCopy(equipment));

    FileOrganizer::setCurrent(projectPath);
    QFile file("scheme.xml");
    if (!file.open(QIODevice::WriteOnly))
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
        xmlWriter.writeStartElement("inputs");
        foreach(InputConnector* connector, equipment->render->inputs)
        {
            xmlWriter.writeStartElement("connector");
            xmlWriter.writeAttribute("id", QString::number(connector->connectorId));
            xmlWriter.writeAttribute("color", QString::number(connector->GetColor()));
            xmlWriter.writeStartElement("link");
            //Информация о связи
            xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("outputs");
        foreach(OutputConnector* connector, equipment->render->outputs)
        {
            xmlWriter.writeStartElement("connector");
            xmlWriter.writeAttribute("id", QString::number(connector->connectorId));
            xmlWriter.writeAttribute("color", QString::number(connector->GetColor()));
            xmlWriter.writeStartElement("link");
            //Информация о связи
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

void FileOrganizer::deleteEquipment(QString name)
{
    this->setPath(projectPath + "/equipments");
    this->remove(name + ".xml");
    for(int i = 0; i < equipmentsInProject.size(); i++)
    {
        if(equipmentsInProject[i]->name == name)
            equipmentsInProject.remove(i);
    }
}

bool FileOrganizer::openEquipments()
{
    FileOrganizer::setCurrent(projectPath + "/equipments");
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
             //int equipmentId;
             QVector <OutputConnector*> outputs;
             QVector <InputConnector*> inputs;

             QXmlStreamReader xmlReader;
             xmlReader.setDevice(&file);
             //while(xmlReader.name() != "equipment")
             //    xmlReader.readNext();
             //equipmentId = xmlReader.attributes().begin()->value().toInt();

             while(xmlReader.name() != "name")
                 xmlReader.readNext();
             equipmentName = xmlReader.readElementText();

             while(xmlReader.name() != "inputs")
                 xmlReader.readNext();
             QVector <int> colors_in;
             //QVector <int> identificators_in;
             while(!(xmlReader.name() == "inputs" && xmlReader.isEndElement()))
             {
                 if(xmlReader.name() == "connector")
                 {
                     foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                     {
                         //if(attr.name().toString() == "color")
                             colors_in.push_back(attr.value().toInt());
                        // else if(attr.name().toString() == "id")
                        //     identificators_in.push_back(attr.value().toInt());
                     }
                 }
                 xmlReader.readNext();
             }
             while(xmlReader.name() != "outputs")
                 xmlReader.readNext();
             QVector <int> colors_out;
             //QVector <int> identificators_out;
             while(!xmlReader.atEnd())
             {
                     if(xmlReader.name() == "connector")
                     {
                         foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                         {
                             //if(attr.name().toString() == "color")
                                 colors_out.push_back(attr.value().toInt());
                             //else if(attr.name().toString() == "id")
                             //    identificators_out.push_back(attr.value().toInt());
                         }
                     }
                 xmlReader.readNext();
             }

             inputs = setInputs(colors_in);
             outputs = setOutputs(colors_out);

             /*for(int i = 0; i < identificators_in.size(); i++)
             {
                 inputs[i]->connectorId = identificators_in[i];
                 inputs[i]->equipmentId = equipmentId;
             }
             for(int i = 0; i < identificators_out.size(); i++)
             {
                 outputs[i]->connectorId = identificators_out[i];
                 outputs[i]->equipmentId = equipmentId;
             }*/

             Equipment* equipment = new Equipment(outputs, inputs);
             equipment->name = equipmentName;
             //equipment->equipmentId = equipmentId;
             equipmentsInProject.push_back(equipment);
        }
        file.close();
    }

    return true;
}

bool FileOrganizer::openScheme()
{
    FileOrganizer::setCurrent(projectPath);

    QFile file("scheme.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    else {
        equipmentsInScheme.clear();
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        QVector <OutputConnector*> outputs;
        QVector <InputConnector*> inputs;
        QVector <int> colors_in;
        QVector <int> identificators_in;
        QVector <int> colors_out;
        QVector <int> identificators_out;
        int equipmentId;
        while(!xmlReader.atEnd())
        {
            if(xmlReader.name() == "equipment" && xmlReader.isStartElement())
            {
                outputs.clear();
                inputs.clear();
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    equipmentId = attr.value().toInt();
                }
                colors_in.clear();
                identificators_in.clear();
                while(xmlReader.name() != "inputs")
                    xmlReader.readNext();
                if(xmlReader.name() == "inputs")
                {
                    while(!(xmlReader.name() == "inputs" && xmlReader.isEndElement()))
                    {
                        if(xmlReader.name() == "connector")
                        {
                            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                            {
                                if(attr.name().toString() == "id")
                                    identificators_in.push_back(attr.value().toInt());
                                else if(attr.name().toString() == "color")
                                    colors_in.push_back(attr.value().toInt());
                            }
                            //xmlReader.readNext();
                            /*if(xmlReader.name() == "link")
                            {
                                if(xmlReader.isStartElement())
                                {
                                    //считываем связь
                                    xmlReader.readNext();
                                }
                                else {
                                    xmlReader.readNext();
                                }
                            }*/
                        }
                        xmlReader.readNext();
                    }
                }
                colors_out.clear();
                identificators_out.clear();
                while(xmlReader.name() != "outputs")
                    xmlReader.readNext();
                if(xmlReader.name() == "outputs")
                {
                    while(!(xmlReader.name() == "outputs" && xmlReader.isEndElement()))
                    {
                        if(xmlReader.name() == "connector")
                        {
                            foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                            {
                                if(attr.name().toString() == "id")
                                    identificators_out.push_back(attr.value().toInt());
                                else if(attr.name().toString() == "color")
                                    colors_out.push_back(attr.value().toInt());
                            }
                            /*xmlReader.readNext();
                            if(xmlReader.name() == "link")
                            {
                                if(xmlReader.isStartElement())
                                {
                                    //считываем связь
                                    xmlReader.readNext();
                                }
                                else {
                                    xmlReader.readNext();
                                }
                            }*/
                        }
                        xmlReader.readNext();
                    }
                }
                inputs = setInputs(colors_in);
                outputs = setOutputs(colors_out);
                Equipment* equipment = new Equipment(outputs, inputs);
                equipment->equipmentId = equipmentId;
                for(int i = 0; i < identificators_in.size(); i++)
                {
                    equipment->render->inputs[i]->connectorId = identificators_in[i];
                    equipment->render->inputs[i]->equipmentId = equipmentId;
                }
                for(int i = 0; i < identificators_out.size(); i++)
                {
                    equipment->render->outputs[i]->connectorId = identificators_out[i];
                    equipment->render->outputs[i]->equipmentId = equipmentId;
                }
                equipmentsInScheme.push_back(equipment);
            }
            xmlReader.readNext();
        }
        file.close();
    }

    return true;
}

bool FileOrganizer::openLibrary()
{
    FileOrganizer::setCurrent(mainPath + "/library");
    this->setPath(mainPath + "/library");

    QString filePath;
    QStringList entryList = this->entryList();
    equipmentsInLibrary.clear();
    for(int i = 2; i < entryList.size(); i++)
    {
        filePath = entryList[i];
        QFile file(filePath);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            return false;
        else{
             QString equipmentName;
             //int equipmentId;
             QVector <OutputConnector*> outputs;
             QVector <InputConnector*> inputs;

             QXmlStreamReader xmlReader;
             xmlReader.setDevice(&file);
             //while(xmlReader.name() != "equipment")
             //    xmlReader.readNext();
             //equipmentId = xmlReader.attributes().begin()->value().toInt();

             while(xmlReader.name() != "name")
                 xmlReader.readNext();
             equipmentName = xmlReader.readElementText();

             while(xmlReader.name() != "inputs")
                 xmlReader.readNext();
             QVector <int> colors_in;//Qt::GlobalColor
             //QVector <int> identificators_in;
             while(!(xmlReader.name() == "inputs" && xmlReader.isEndElement()))
             {
                 if(xmlReader.name() == "connector")
                 {
                     foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                     {
                         //if(attr.name().toString() == "color")
                             colors_in.push_back(attr.value().toInt());
                         //else if(attr.name().toString() == "id")
                         //    identificators_in.push_back(attr.value().toInt());
                     }
                 }
                 xmlReader.readNext();
             }
             while(xmlReader.name() != "outputs")
                 xmlReader.readNext();
             QVector <int> colors_out;//Qt::GlobalColor
             //QVector <int> identificators_out;
             while(!xmlReader.atEnd())
             {
                 if(xmlReader.name() == "connector")
                 {
                         foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                         {
                             //if(attr.name().toString() == "color")
                                 colors_out.push_back(attr.value().toInt());
                             //else if(attr.name().toString() == "id")
                             //    identificators_out.push_back(attr.value().toInt());
                         }
                 }
                 xmlReader.readNext();
             }

             inputs = setInputs(colors_in);
             outputs = setOutputs(colors_out);

             /*for(int i = 0; i < identificators_in.size(); i++)
             {
                 inputs[i]->connectorId = identificators_in[i];
                 inputs[i]->equipmentId = equipmentId;
             }
             for(int i = 0; i < identificators_out.size(); i++)
             {
                 outputs[i]->connectorId = identificators_out[i];
                 outputs[i]->equipmentId = equipmentId;
             }*/

             Equipment* equipment = new Equipment(outputs, inputs);
             equipment->name = equipmentName;
             //equipment->equipmentId = equipmentId;
             equipmentsInLibrary.push_back(equipment);
        }
        file.close();
    }

    return true;
}

QVector <InputConnector*> FileOrganizer::setInputs(QVector<int> colors_in)
{
    QVector <InputConnector*> inputs;

    foreach(int color, colors_in)
    {
        switch(color)
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

    return inputs;
}

QVector <OutputConnector*> FileOrganizer::setOutputs(QVector<int> colors_out)
{
    QVector <OutputConnector*> outputs;

    foreach(int color, colors_out)
    {
        switch(color)
        {
        case Qt::red:
        {
            outputs.push_back(new OutputConnectorRed());
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

    return outputs;
}
