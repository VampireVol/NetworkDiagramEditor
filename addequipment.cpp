#include "addequipment.h"
#include "ui_addequipment.h"

AddEquipment::AddEquipment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEquipment)
{
    ui->setupUi(this);
    ui->pushAdd->setEnabled(false);
    ui->pushDelete->setEnabled(false);
    ui->pushOk->setEnabled(false);
}

AddEquipment::~AddEquipment()
{
    delete ui;
}

void AddEquipment::loadEquipmentsFromLibrary(QVector<Equipment*> equipmentsInLibrary)
{
    this->equipmentsInLibrary = equipmentsInLibrary;
    foreach(Equipment* equipment, equipmentsInLibrary)
        ui->ListWidgetsAvailable->addItem(equipment);
}

QVector<Equipment*> AddEquipment::getAddedEquipments()
{
    return equipmentsAdded;
}

void AddEquipment::on_pushAdd_clicked()
{
    ui->pushOk->setEnabled(true);
    ui->pushDelete->setEnabled(true);
    QListWidgetItem *item = new QListWidgetItem();
    int row = ui->ListWidgetsAvailable->currentRow();
    *item = *ui->ListWidgetsAvailable->currentItem();
    ui->ListWidgetsAdded->addItem(item);
    equipmentsAdded.push_back(equipmentsInLibrary[row]);
}

void AddEquipment::on_pushExit_clicked()
{
    AddEquipment::close();
}

void AddEquipment::on_pushDelete_clicked()
{
    QListWidgetItem *item = ui->ListWidgetsAdded->takeItem(ui->ListWidgetsAdded->currentRow());
        delete item;
    if(ui->ListWidgetsAdded->count() == 0)
    {
        ui->pushOk->setEnabled(false);
        ui->pushDelete->setEnabled(false);
    }
}

void AddEquipment::on_ListWidgetsAvailable_itemClicked()
{
    ui->pushAdd->setEnabled(true);
}

void AddEquipment::on_ListWidgetsAvailable_itemDoubleClicked()
{
    AddEquipment::on_pushAdd_clicked();
}

void AddEquipment::on_ListWidgetsAdded_itemClicked()
{
    ui->pushDelete->setEnabled(true);
}

void AddEquipment::on_ListWidgetsAdded_itemDoubleClicked()
{
    AddEquipment::on_pushDelete_clicked();
}

void AddEquipment::on_pushOk_clicked()
{
    AddEquipment::close();
}
