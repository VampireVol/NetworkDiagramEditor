#include "equipmentcreator.h"
#include "ui_equipmentcreator.h"

EquipmentCreator::EquipmentCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EquipmentCreator)
{
    ui->setupUi(this);
    QListWidgetItem *itemRedIn = new QListWidgetItem(QIcon(":rec/img/RedIn.png"), "Красный вход");
    ui->listWidgetIn->addItem(itemRedIn);
    QListWidgetItem *itemBlueIn = new QListWidgetItem(QIcon(":rec/img/BlueIn.png"), "Синий вход");
    ui->listWidgetIn->addItem(itemBlueIn);
}

EquipmentCreator::~EquipmentCreator()
{
    delete ui;
}

void EquipmentCreator::on_pushButtonCreate_clicked()
{
//это конопка создать
}

void EquipmentCreator::on_pushButtonAddIn_clicked()
{
    QListWidgetItem *item = new QListWidgetItem();
    *item = *ui->listWidgetIn->currentItem();
    ui->listWidgetEquipment->addItem(item);
}
