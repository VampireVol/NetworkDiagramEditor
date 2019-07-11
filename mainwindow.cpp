#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipmentcreator.h"
#include "addequipment.h"
#include "projectname.h"
#include "selectpath.h"
#include "projectname.h"
#include "addrule.h"
#include "adddescription.h"
#include <QGraphicsScene>
#include "QMessageBox"
#include "connector.h"
#include "vepolyline.h"
#include "dotsignal.h"
#include "body.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //scene->hasFocus()
    ui->open_equipment_creator->setEnabled(false);
    //ui->add_delete_equipment->setEnabled(false);
    ui->pushAddEquipment->setEnabled(false);
    ui->pushDeleteObj->setEnabled(false);
    ui->add_connection->setEnabled(false);
    ui->pushAddConn->setEnabled(false);
    ui->pushAddDescription->setEnabled(false);
    ui->save->setEnabled(false);
    ui->save_as->setEnabled(false);
    scene = new QGraphicsScene();
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(enable_pushDeleteObj()));
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(ennable_pushAddConn()));
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(enable_pushAddDescription()));
    ui->graphicsView->setScene(scene);
    mainPath = FileOrganizer::currentPath();//"V:/study/QtProjects/build-DiagramNetworkEditor-Desktop_Qt_5_13_0_MSVC2017_64bit-Release";
    connectionRule = new ConnectionRule;
    nextPolylineId = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_create_triggered()
{
    ui->statusBar->showMessage("Создать проект");
    ProjectName windowProjectName;
    windowProjectName.setModal(true);
    windowProjectName.exec();
    if(!windowProjectName.projectName().isEmpty())
    {
        SelectPath windowSelectPath;
        windowSelectPath.setModal(true);
        windowSelectPath.exec();
        if(!windowSelectPath.getProjectPath().isEmpty())
        {
            //.///////////////////////////////////////////////////////////////////////
            fileOrganizer = new FileOrganizer(windowProjectName.projectName(), windowSelectPath.getProjectPath(), mainPath, mainPath + "/library");
            switch(fileOrganizer->createProject())
            {
            case 0:
            {
                QMessageBox::information(this, "Успех", "Проект успешно создан:)");
                ui->save->setEnabled(true);
                ui->save_as->setEnabled(true);
                ui->open_equipment_creator->setEnabled(true);
                ui->add_connection->setEnabled(true);
                ui->pushAddEquipment->setEnabled(false);
                ui->pushDeleteObj->setEnabled(false);
                ui->pushAddConn->setEnabled(false);
                ui->pushAddDescription->setEnabled(false);
                connectionRule = new ConnectionRule;
                equipmentsInProject.clear();
                equipmentsInLibrary.clear();
                equipmentsOnScene.clear();
                nextEquipmentId = 1;
                foreach(Equipment *equipmet, fileOrganizer->getEquipmentsInLibrary())
                    equipmentsInLibrary.push_back(Equipment::CreateCopy(equipmet));
                ui->listWidget->clear();
                ui->descriprion->clear();
                scene->clear();
                break;
            }
            case 1:
            {
                QMessageBox::warning(this, "Упс:(", "Проект с таким именем уже существует");
                break;
            }
            case 2:
            {
                QMessageBox::warning(this, "Упс:(", "Библиотека не загружена");
                break;
            }
            case 3:
            {
                QMessageBox::warning(this, "Упс:(", "Проект не удалось создать");
                break;
            }
            }
        }
    }
}

void MainWindow::on_open_triggered()
{
    ui->statusBar->showMessage("Открыть проект");
    SelectPath windowSelectPath;
    windowSelectPath.setModal(true);
    windowSelectPath.exec();
    if(!windowSelectPath.getProjectPath().isEmpty())
    {
        //.////////////////////////////////////////////////////////////////////////
        fileOrganizer = new FileOrganizer(nullptr, windowSelectPath.getProjectPath(), mainPath, mainPath + "/library");
        switch(fileOrganizer->openProject())
        {
        case 0:
        {
            QMessageBox::information(this, "Ура:)", "Проект успешно открыт");
            ui->save->setEnabled(true);
            ui->save_as->setEnabled(true);
            ui->open_equipment_creator->setEnabled(true);
            ui->add_connection->setEnabled(true);
            ui->pushAddEquipment->setEnabled(false);
            ui->pushDeleteObj->setEnabled(false);
            ui->pushAddConn->setEnabled(false);
            ui->pushAddDescription->setEnabled(false);
            ui->listWidget->clear();
            ui->descriprion->clear();
            equipmentsInProject.clear();
            equipmentsInLibrary.clear();
            equipmentsOnScene.clear();
            scene->clear();
            nextEquipmentId = 1;
            foreach(Equipment *equipmet, fileOrganizer->getEquipmentsInProject())
            {
                equipmentsInProject.push_back(Equipment::CreateCopy(equipmet));
                equipmentsInProject.last()->setText(equipmentsInProject.last()->name);
            }
            foreach(Equipment *equipmet, fileOrganizer->getEquipmentsInLibrary())
                equipmentsInLibrary.push_back(Equipment::CreateCopy(equipmet));
            foreach(Equipment *equipmet, fileOrganizer->getEquipmentsInScheme())
            {
                equipmentsOnScene.push_back(Equipment::CreateCopy(equipmet));
            }

            if(!equipmentsInProject.isEmpty())
            {
                foreach(Equipment *equipment, equipmentsInProject)
                    ui->listWidget->addItem(equipment);
            }
            if(!equipmentsOnScene.isEmpty())
            {
                foreach(Equipment *equipment, equipmentsOnScene)
                {
                    //equipment->setText(equipment->name);
                    QString text = QString("id: %1").arg(equipment->equipmentId);
                    equipment->labelId = new QLabel(text);
                    equipment->render->body->setId(equipment->equipmentId);
                    QGraphicsProxyWidget* proxyWidget = new QGraphicsProxyWidget(equipment->render->body);
                    //тут можно поиграться с отображением
                    proxyWidget->setWidget(equipment->labelId);
                    connect(equipment->render->body, SIGNAL(equipmentIsSelected(int)), this, SLOT(showDescription(int)));
                    scene->addItem(equipment->render->body);
                }
                nextEquipmentId = equipmentsOnScene.last()->equipmentId + 1;
            }
            break;
        }
        case 1:
        {
            QMessageBox::warning(this, "Упс:(", "Проект не найден");
            break;
        }
        case 2:
        {
            QMessageBox::warning(this, "Упс:(", "Оборудование не удалось загрузить");
            break;
        }
        case 3:
        {
            QMessageBox::warning(this, "Упс:(", "Библиотеку не удалось загрузить");
            break;
        }
        case 4:
        {
            QMessageBox::warning(this, "Упс:(", "Схему не удалось загрузить");
            break;
        }
        default:
        {
            QMessageBox::warning(this, "Упс:(", "Неизвестная ошибка:(");
            break;
        }
        }
    }
}

void MainWindow::on_save_triggered()
{
    ui->statusBar->showMessage("Сохранить");
    if(fileOrganizer->saveScheme(equipmentsOnScene))
        QMessageBox::information(this, "Сохранение", "Проект успешно сохранен");
    else
        QMessageBox::warning(this, "Сохранение", "Проект не удалось сохранить");
}

void MainWindow::on_close_triggered()
{
    QApplication::quit();
}

void MainWindow::on_open_equipment_creator_triggered()
{
    EquipmentCreator window;
    window.setModal(true);
    window.exec();
    if(window.CreateEquipment() != nullptr)
    {
        int counter = 0;
        QString name = window.CreateEquipment()->name;
        while(Equipment::Contains(equipmentsInProject, window.CreateEquipment()) || Equipment::Contains(equipmentsInLibrary, window.CreateEquipment()))
            window.CreateEquipment()->name = name + QString::number(++counter);
        equipmentsInProject.push_back(Equipment::CreateCopy(window.CreateEquipment()));
        equipmentsInProject.last()->setText(equipmentsInProject.last()->name);
        ui->listWidget->addItem(equipmentsInProject.last());
        fileOrganizer->addEquipmentToProject(equipmentsInProject.last());
    }
}

void MainWindow::on_add_delete_equipment_triggered()
{
    ui->statusBar->showMessage("Открыть библиотеку");
    AddEquipment window;
    window.loadEquipments(equipmentsInLibrary, equipmentsInProject);
    window.setModal(true);
    window.exec();
    if(!window.reject_isClicked())
    {
        foreach(Equipment *equipment, window.getEquipmentsInProject())
        {
            if(!Equipment::Contains(equipmentsInProject, equipment))
            {
                equipmentsInProject.push_back(Equipment::CreateCopy(equipment));
                equipmentsInProject.last()->setText(equipmentsInProject.last()->name);
                ui->listWidget->addItem(equipmentsInProject.last());
                fileOrganizer->addEquipmentToProject(equipmentsInProject.last());
            }
        }

        foreach(Equipment *equipment, window.getEquipmentsInLibrary())
        {
            if(!Equipment::Contains(equipmentsInLibrary, equipment))
            {
                equipmentsInLibrary.push_back(Equipment::CreateCopy(equipment));
                fileOrganizer->addEquipmentToLibrary(equipmentsInLibrary.last());
            }
        }
        for(int i = 0; i < equipmentsInProject.size(); i++)
        {
            if(!Equipment::Contains(window.getEquipmentsInProject(), equipmentsInProject[i]))
            {
                equipmentsInProject.remove(i);
                fileOrganizer->deleteEquipmentFromProject(equipmentsInProject[i]->name);
                QListWidgetItem *item = ui->listWidget->takeItem(i);
                delete item;
            }
        }

        if(ui->listWidget->count() == 0)
            ui->pushAddEquipment->setEnabled(false);

        for(int i = 0; i < equipmentsInLibrary.size(); i++)
        {
            if(!Equipment::Contains(window.getEquipmentsInLibrary(), equipmentsInLibrary[i]))
            {
                equipmentsInLibrary.remove(i);
                fileOrganizer->deleteEquipmentFromLibrary(equipmentsInLibrary[i]->name);
            }
        }
    }
}

void MainWindow::on_listWidget_itemClicked()
{
    ui->pushAddEquipment->setEnabled(true);
}

void MainWindow::on_pushAddObj_clicked()
{
    ui->statusBar->showMessage("Объект добавлен на схему");
    //Добавление объекта на схему
    int row = ui->listWidget->currentRow();
    Equipment *copy = Equipment::CreateCopy(equipmentsInProject[row]);
    //copy->setText(copy->name);
    copy->SetId(nextEquipmentId);
    QString text = QString("id: %1").arg(copy->equipmentId);
    copy->labelId = new QLabel(text);
    QGraphicsProxyWidget* proxyWidget = new QGraphicsProxyWidget(copy->render->body);
    //тут можно поиграться с отображением
    proxyWidget->setWidget(copy->labelId);
    equipmentsOnScene.push_back(copy);
    connect(equipmentsOnScene.last()->render->body, SIGNAL(equipmentIsSelected(int)), this, SLOT(showDescription(int)));
    scene->addItem(equipmentsOnScene.last()->render->body);
}

void MainWindow::on_listWidget_itemDoubleClicked()
{
    MainWindow::on_pushAddObj_clicked();
}

void MainWindow::on_pushDeleteObj_clicked()
{
    /*if (scene->selectedItems().size() == 1 && scene->selectedItems().first()->type() == Connector::Type)
    {

    }*/
}

void MainWindow::on_save_as_triggered()
{
    ui->statusBar->showMessage("Сохранить как");
    SelectPath window;
    window.setModal(true);
    window.exec();
    if(!window.getProjectPath().isEmpty())
    {
        switch(fileOrganizer->editProjectPath(equipmentsOnScene, window.getProjectPath()))
        {
        case 0:
        {
            if(fileOrganizer->editProjectPath(equipmentsOnScene, window.getProjectPath()))
                QMessageBox::information(this, "Сохранение", "Проект успешно сохранен");
            break;
        }
        case 1:
        {
            QMessageBox::warning(this, "Сохранение", "Вы указали текущую директорию");
            break;
        }
        case 2:
        {
            QMessageBox::warning(this, "Сохранение", "Проект с таким именем уже существует");
            break;
        }
        case 3:
        {
            QMessageBox::warning(this, "Сохранение", "Проект не удалось сохранить");
            break;
        }
        }
    }
}

void MainWindow::on_pushAddConn_clicked()
{
        Connector *first = qgraphicsitem_cast<Connector*>(scene->selectedItems().first());
        Connector *end = qgraphicsitem_cast<Connector*>(scene->selectedItems().last());
        if (first->equipmentId != end->equipmentId)
        {
            if (first->IsNull() && end->IsNull())
            {
                qDebug() << first->GetColor() << " " << end->GetColor() << " " << connectionRule->GetRule(first->GetColor(), end->GetColor());
                if (connectionRule->GetRule(first->GetColor(), end->GetColor()))
                {
                    Equipment *firstEq = nullptr;
                    Equipment *endEq = nullptr;
                    first->SetLink(end);
                    end->SetLink(first);
                    foreach(Equipment *equipment, equipmentsOnScene)
                    {
                        if(equipment->equipmentId == first->equipmentId)
                        {
                            firstEq = equipment;
                        }
                        else if(equipment->equipmentId == end->equipmentId)
                        {
                            endEq = equipment;
                        }

                    }

                    VEPolyline *polyline = new VEPolyline(firstEq->render->body, endEq->render->body);
                    QPainterPath path;
                    QPointF fixPos;
                    fixPos.setX(10);
                    fixPos.setY(10);

                    path.moveTo(firstEq->render->body->pos() + first->pos() + fixPos);
                    path.lineTo(endEq->render->body->pos() + end->pos() + fixPos);
                    scene->addItem(polyline);
                    connections.push_back(polyline);
                    polyline->setPath(path);
                    QPen pen;
                    pen.setWidth(2);
                    polyline->setPen(pen);
                    polyline->setZValue(-1);
                    first->SetLink(end);
                    end->SetLink(first);
                    polyline->SetId(nextPolylineId);
                    connect(polyline, SIGNAL(polylineIsSelected(int)), this, SLOT(showDescriptionPolyline(int)));
                }
                else
                {
                    QMessageBox::warning(this, "Внимание", "Данное соединение запрещено");
                }
            }
            else
            {
                QMessageBox::warning(this, "Внимание", "Один из коннекторов уже соединен");
            }
        }
        else
        {
            QMessageBox::warning(this, "Внимание", "Данное соединение запрещено");
        }
}

void MainWindow::on_add_connection_triggered()
{
    ui->statusBar->showMessage("Добавить связь");
    AddRule window;
    window.setModal(true);
    window.exec();
    if(!window.isReject())
        connectionRule->SetRule(window.getColor_1(), window.getColor_2(), window.getRule());
}

void MainWindow::showDescription(int equipmentId)
{
    ui->descriprion->clear();
    QString text;
    foreach(Connector *connector, equipmentsOnScene[equipmentId - 1]->render->connectors)
    {
        text = text + "тип: " + getConnectorType(connector->GetColor()) + ", id: " + QString::number(connector->connectorId) + '\n';
    }
    text = "Название: " + equipmentsOnScene[equipmentId - 1]->name + '\n' +
            "id: " + QString::number(equipmentsOnScene[equipmentId - 1]->equipmentId) + '\n' +
            "Коннекторы:\n" + text;
    ui->descriprion->setText(text);
}

void MainWindow::showDescriptionPolyline(int polylineId)
{
    //int firstIdEquipment = connections[polylineId - 1]->first->id;
    //int secondIdEquipment = connections[polylineId - 1]->first->id;
    //Equipment *first, *second;
    ui->descriprion->clear();
    QString text = "Описание: " + connections[polylineId - 1]->GetDescription() + '\n' +
            "id: " + QString::number(connections[polylineId - 1]->polylineId) + '\n' +
            "Соединяет:\n" +
            "Оборудование #1: " + '\n' +
            "Оборудование #2: " + '\n';
    ui->descriprion->setText(text);
}

QString MainWindow::getConnectorType(int color)
{
    switch(color)
    {
    case Qt::red:
    {
        return "USB";
    }
    case Qt::blue:
    {
        return "HDMI";
    }
    case Qt::green:
    {
        return "VGA";
    }
    case Qt::cyan:
    {
        return "Enternet";
    }
    case Qt::yellow:
    {
        return "Mini jack 3.5 mm";
    }
    default:
    {
        return "Неизвестно";
    }
    }
}

void MainWindow::on_pushAddDescription_clicked()
{
    ui->pushDeleteObj->setEnabled(true);
    AddDescription window;
    window.setModal(true);
    window.exec();
}

void MainWindow::enable_pushDeleteObj()
{
    if((scene->selectedItems().size() == 1 && scene->selectedItems().first()->type() == Body::Type) ||
            (scene->selectedItems().size() == 1 && scene->selectedItems().first()->type() == VEPolyline::Type))
        ui->pushDeleteObj->setEnabled(true);
    else {
        ui->pushDeleteObj->setEnabled(false);
    }
}

void MainWindow::ennable_pushAddConn()
{
    if (scene->selectedItems().size() == 2 &&
            scene->selectedItems().first()->type() == Connector::Type &&
            scene->selectedItems().last()->type() == Connector::Type)
        ui->pushAddConn->setEnabled(true);
    else {
        ui->pushAddConn->setEnabled(false);
    }
}

void MainWindow::enable_pushAddDescription()
{
    if(scene->selectedItems().size() == 1 && scene->selectedItems().first()->type() == VEPolyline::Type)
        ui->pushAddDescription->setEnabled(true);
    else {
        ui->pushAddDescription->setEnabled(false);
    }
}
