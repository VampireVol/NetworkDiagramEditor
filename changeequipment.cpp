#include "changeequipment.h"
#include "ui_changeequipment.h"

ChangeEquipment::ChangeEquipment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeEquipment)
{
    ui->setupUi(this);
}

ChangeEquipment::~ChangeEquipment()
{
    delete ui;
}

void ChangeEquipment::on_back_clicked()
{
    ChangeEquipment::close();
}

void ChangeEquipment::on_select_clicked()
{
}
