#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipmentcreator.h"
#include "addequipment.h"
#include "projectname.h"
#include "selectpath.h"
#include <QGraphicsScene>
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushAddObj->setEnabled(false);
    ui->pushDeleteObj->setEnabled(false);
    ui->pushDeleteConn->setEnabled(false);
    ui->open_equipment_creator->setEnabled(false);
    ui->add_delete_equipment->setEnabled(false);
    ui->save->setEnabled(false);
    ui->save_as->setEnabled(false);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    mainPath = FileOrganizer::currentPath();//"V:/study/QtProjects/build-DiagramNetworkEditor-Desktop_Qt_5_13_0_MSVC2017_64bit-Release";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_create_triggered()
{
    ui->statusBar->showMessage("Создать проект");
    ui->pushAddObj->setEnabled(false);
    ProjectName window;
    window.setModal(true);
    window.exec();
    QString projectName = window.projectName();
    if(!projectName.isEmpty())
    {
        //.///////////////////////////////////////////////////////////////////////
        fileOrganizer = new FileOrganizer(projectName, mainPath);
        if(fileOrganizer->createProject())
        {
            QMessageBox::information(this, "Успех", "Проект успешно создан:)");
            ui->save->setEnabled(true);
            ui->save_as->setEnabled(true);
            ui->open_equipment_creator->setEnabled(true);
            ui->add_delete_equipment->setEnabled(true);
            equipmentsInProject.clear();
            equipmentsInLibrary.clear();
            equipmentsOnScene.clear();
            nextEquipmentId = 1;
            foreach(Equipment *equipmet, fileOrganizer->getEquipmentsInLibrary())
                equipmentsInLibrary.push_back(Equipment::CreateCopy(equipmet));
            ui->listWidget->clear();
            scene->clear();
        }
        else
        {
            QMessageBox::warning(this, "Упс:(", "Проект не удалось создать");
        }
    }
}

void MainWindow::on_open_triggered()
{
    ui->statusBar->showMessage("Открыть проект");
    ui->pushAddObj->setEnabled(false);
    ProjectName window;
    window.setModal(true);
    window.exec();
    QString projectName = window.projectName();
    if(!projectName.isEmpty())
    {
        //.////////////////////////////////////////////////////////////////////////
        fileOrganizer = new FileOrganizer(projectName, mainPath);
        switch(fileOrganizer->openProject())
        {
        case 0:
        {
            QMessageBox::information(this, "Ура:)", "Проект успешно открыт");
            ui->save->setEnabled(true);
            ui->save_as->setEnabled(true);
            ui->open_equipment_creator->setEnabled(true);
            ui->add_delete_equipment->setEnabled(true);
            ui->listWidget->clear();
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
                equipmentsOnScene.push_back(Equipment::CreateCopy(equipmet));

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
                    QGraphicsProxyWidget* proxyWidget = new QGraphicsProxyWidget(equipment->render->body);
                    //тут можно поиграться с отображением
                    proxyWidget->setWidget(equipment->labelId);
                    equipmentsOnScene.push_back(equipment);
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
    if(fileOrganizer->saveScheme(equipmentsOnScene))
        QMessageBox::information(this, "Сохранение", "Схема сохранена");
    else
        QMessageBox::warning(this, "Сохранение", "Схему не удалось сохранить");
    ui->statusBar->showMessage("Сохранить");
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
        equipmentsInLibrary.push_back(Equipment::CreateCopy(window.CreateEquipment()));
        equipmentsInProject.last()->setText(equipmentsInProject.last()->name);
        ui->listWidget->addItem(equipmentsInProject.last());
        fileOrganizer->addEquipment(equipmentsInProject.last());
    }
}

void MainWindow::on_add_delete_equipment_triggered()
{
    AddEquipment window;
    window.loadEquipments(equipmentsInLibrary, equipmentsInProject);
    window.setModal(true);
    window.exec();
    if(!window.reject_isClicked())
    {
        QVector <Equipment*> copyEquipments;
        foreach(Equipment *equipment, equipmentsInProject)
            copyEquipments.push_back(Equipment::CreateCopy(equipment));

        equipmentsInProject.clear();
        ui->listWidget->clear();
        foreach(Equipment *equipment, window.getEquipmentsInProject())
        {
                equipmentsInProject.push_back(Equipment::CreateCopy(equipment));
                equipmentsInProject.last()->setText(equipmentsInProject.last()->name);
                ui->listWidget->addItem(equipmentsInProject.last());
                fileOrganizer->addEquipment(equipmentsInProject.last());
        }
        foreach(Equipment *equipment, copyEquipments)
        {
            if(!Equipment::Contains(equipmentsInProject, equipment))
                fileOrganizer->deleteEquipment(equipment->name);
        }
    }
}

void MainWindow::on_listWidget_itemClicked()
{
    ui->pushAddObj->setEnabled(true);
}

void MainWindow::on_pushAddObj_clicked()
{
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
    scene->addItem(copy->render->body);
}

void MainWindow::on_listWidget_itemDoubleClicked()
{
    MainWindow::on_pushAddObj_clicked();
}


void MainWindow::on_pushDeleteObj_clicked()
{
    //Удаление выделенного объекта и связи с другими объектами
}

void MainWindow::on_pushDeleteConn_clicked()
{
    //удаление выделенной связи
}

void MainWindow::on_delete_equipment_triggered()
{

}

void MainWindow::on_save_as_triggered()
{

}
