#include "addequipment.h"
#include "ui_addequipment.h"
#include "QMessageBox"

AddEquipment::AddEquipment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEquipment)
{
    ui->setupUi(this);
    ui->pushAdd->setEnabled(false);
    ui->pushDelete->setEnabled(false);
    reject = false;
    library_hasFocus = false;
    project_hasFocus = false;
}

AddEquipment::~AddEquipment()
{
    delete ui;
}

void AddEquipment::loadEquipments(QVector<Equipment*> equipmentsInLibrary, QVector<Equipment*> equipmentsInProject)
{
    foreach(Equipment* equipmentLib, equipmentsInLibrary)
    {
        this->equipmentsInLibrary.push_back(Equipment::CreateCopy(equipmentLib));
        this->equipmentsInLibrary.last()->setText(this->equipmentsInLibrary.last()->name);
        ui->ListWidgetsLibrary->addItem(this->equipmentsInLibrary.last());
    }
    foreach(Equipment* equipmentProj, equipmentsInProject)
    {
        this->equipmentsInProject.push_back(Equipment::CreateCopy(equipmentProj));
        this->equipmentsInProject.last()->setText(this->equipmentsInProject.last()->name);
        ui->ListWidgetsProject->addItem(this->equipmentsInProject.last());
    }
}

QVector<Equipment*> AddEquipment::getEquipmentsInProject()
{
    return equipmentsInProject;
}

QVector<Equipment*> AddEquipment::getEquipmentsInLibrary()
{
    return equipmentsInLibrary;
}

void AddEquipment::on_pushAdd_clicked()
{
    if(library_hasFocus)
    {
        int row = ui->ListWidgetsLibrary->currentRow();
        if(!Equipment::Contains(equipmentsInProject, equipmentsInLibrary[row]))
        {
            QListWidgetItem *item = new QListWidgetItem();
            *item = *ui->ListWidgetsLibrary->currentItem();
            ui->ListWidgetsProject->addItem(item);
            equipmentsInProject.push_back(equipmentsInLibrary[row]);
            ui->pushDelete->setEnabled(true);
        }
        else {
            QMessageBox::information(this, "Внимание!", "Оборудование уже в проекте");
        }
    }
    else if(project_hasFocus)
    {
        int row = ui->ListWidgetsProject->currentRow();
        if(!Equipment::Contains(equipmentsInLibrary, equipmentsInProject[row]))
        {
            QListWidgetItem *item = new QListWidgetItem();
            *item = *ui->ListWidgetsProject->currentItem();
            ui->ListWidgetsLibrary->addItem(item);
            equipmentsInLibrary.push_back(equipmentsInProject[row]);
            ui->pushDelete->setEnabled(true);
        }
        else {
            QMessageBox::information(this, "Внимание!", "Оборудование уже в библиотеке");
        }
    }
}

void AddEquipment::on_pushReject_clicked()
{
    reject = true;
    AddEquipment::close();
}

bool AddEquipment::reject_isClicked()
{
    return reject;
}

void AddEquipment::on_pushDelete_clicked()
{
    if(project_hasFocus)
    {
        int row = ui->ListWidgetsProject->currentRow();
        QListWidgetItem *item = ui->ListWidgetsProject->takeItem(ui->ListWidgetsProject->currentRow());
        delete item;
        equipmentsInProject.remove(row);
        if(ui->ListWidgetsProject->count() == 0)
        {
            ui->pushDelete->setEnabled(false);
            ui->pushAdd->setEnabled(false);
            project_hasFocus = false;
        }
    }
    else if(library_hasFocus)
    {
        int row = ui->ListWidgetsLibrary->currentRow();
        QListWidgetItem *item = ui->ListWidgetsLibrary->takeItem(ui->ListWidgetsLibrary->currentRow());
        delete item;
        equipmentsInLibrary.remove(row);
        if(ui->ListWidgetsLibrary->count() == 0)
        {
            ui->pushDelete->setEnabled(false);
            ui->pushAdd->setEnabled(false);
            project_hasFocus = false;
        }
    }
}

void AddEquipment::on_ListWidgetsLibrary_itemClicked()
{
    library_hasFocus = true;
    project_hasFocus = false;
    ui->pushAdd->setEnabled(true);
    ui->pushDelete->setEnabled(true);
}

void AddEquipment::on_ListWidgetsLibrary_itemDoubleClicked()
{
    AddEquipment::on_pushAdd_clicked();
}

void AddEquipment::on_ListWidgetsProject_itemClicked()
{
    library_hasFocus = false;
    project_hasFocus = true;
    ui->pushAdd->setEnabled(true);
    ui->pushDelete->setEnabled(true);
}

void AddEquipment::on_ListWidgetsProject_itemDoubleClicked()
{
    AddEquipment::on_pushAdd_clicked();
}

void AddEquipment::on_pushOk_clicked()
{
    AddEquipment::close();
}
