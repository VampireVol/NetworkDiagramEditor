#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipmentcreator.h"
#include "addequipment.h"
#include "projectname.h"
#include "fileorganizer.h"
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

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
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
        ui->open_equipment_creator->setEnabled(true);
        ui->add_delete_equipment->setEnabled(true);
        //.///////////////////////////////////////////////////////////////////////
        fileOrganizer = new FileOrganizer(projectName);
        switch(fileOrganizer->createProject())
        {
        case 0:
        {
            QMessageBox::information(this, "Успех", "Проект успешно создан:)");
            equipmentsInProject.clear();
            equipmentsInLibrary.clear();
            equipmentsOnScene.clear();
            nextEquipmentId = 1;
            foreach(Equipment *equipmet, fileOrganizer->getEquipmentsInLibrary())
                equipmentsInLibrary.push_back(Equipment::CreateCopy(equipmet));
            ui->listWidget->clear();
            scene->clear();
            break;
        }
        case 1:
        {
            QMessageBox::warning(this, "Упс:(", "Проект не открыт");
            break;
        }
        case 2:
        {
            QMessageBox::warning(this, "Упс:(", "Библиотека не открыта");
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
        ui->open_equipment_creator->setEnabled(true);
        ui->add_delete_equipment->setEnabled(true);
        //.////////////////////////////////////////////////////////////////////////
        fileOrganizer = new FileOrganizer(projectName);
        switch(fileOrganizer->openProject())
        {
        case 0:
        {
            QMessageBox::information(this, "Ура:)", "Проект успешно открыт");
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

            if(!equipmentsInProject.isEmpty())
            {
                foreach(Equipment *equipment, equipmentsInProject)
                    ui->listWidget->addItem(equipment);
            }
            break;
        }
        case 1:
        {
            QMessageBox::warning(this, "Упс:(", "Проект не открыт");
            break;
        }
        case 2:
        {
            QMessageBox::warning(this, "Упс:(", "Библиотека не открыта");
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
        while(Equipment::Contains(equipmentsInProject, window.CreateEquipment()) || Equipment::Contains(equipmentsInLibrary, window.CreateEquipment()))
            window.CreateEquipment()->name += "1";
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
    QString name = equipmentsInProject[row]->text();
    copy->setText(name);
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
