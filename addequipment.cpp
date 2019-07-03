#include "addequipment.h"
#include "ui_addequipment.h"

AddEquipment::AddEquipment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEquipment)
{
    ui->setupUi(this);
    ui->pushAdd->setEnabled(false);
    ui->pushDelete->setEnabled(false);
}

AddEquipment::~AddEquipment()
{
    delete ui;
}

void AddEquipment::on_pushAdd_clicked()
{
    QListWidgetItem *item = new QListWidgetItem();
    *item = *ui->ListWidgetsAvailable->currentItem();
    ui->ListWidgetsAdded->addItem(item);
}

void AddEquipment::on_pushExit_clicked()
{
    AddEquipment::close();
}

void AddEquipment::on_pushDelete_clicked()
{
    QListWidgetItem *item = ui->ListWidgetsAdded->takeItem(ui->ListWidgetsAdded->currentRow());
        delete item;
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
