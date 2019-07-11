#include "equipmentcreator.h"
#include "ui_equipmentcreator.h"
#include <QMessageBox>
#include <QRegExpValidator>

EquipmentCreator::EquipmentCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EquipmentCreator)
{
    ui->setupUi(this);
    QListWidgetItem *itemRed = new QListWidgetItem(QIcon(":/img/red_out.png"), "USB");
    ui->listWidgetConnectors->addItem(itemRed);
    QListWidgetItem *itemBlue = new QListWidgetItem(QIcon(":/img/blue_out.png"), "HDMI");
    ui->listWidgetConnectors->addItem(itemBlue);
    QListWidgetItem *itemGreen = new QListWidgetItem(QIcon(":/img/green_out.png"), "VGA");
    ui->listWidgetConnectors->addItem(itemGreen);
    QListWidgetItem *itemCyan = new QListWidgetItem(QIcon(":/img/cyan_out.png"), "Internet");
    ui->listWidgetConnectors->addItem(itemCyan);
    QListWidgetItem *itemYellow = new QListWidgetItem(QIcon(":/img/yellow_out.png"), "Mini jack 3.5 mm");
    ui->listWidgetConnectors->addItem(itemYellow);

    QRegExp exp("[a-zA-Z]{1,9}[1-9]{0,2}");
    ui->lineEditName->setValidator(new QRegExpValidator(exp, this));

    listWidgetEquipment_isEmpty = true;
    equipmentName_isGood = false;
    ui->pushButtonAdd->setEnabled(false);
    ui->pushButtonDel->setEnabled(false);
    ui->pushButtonCreate->setEnabled(false);
}

EquipmentCreator::~EquipmentCreator()
{
    delete ui;
}

Equipment* EquipmentCreator::CreateEquipment()
{
    return equipment;
}

void EquipmentCreator::on_pushButtonCreate_clicked()
{
//записываем XML файл
    QVector <Connector*> connectors;
    QString str;

    while (QListWidgetItem *item = ui->listWidgetEquipment->takeItem(0))
    {
        str = item->text();
        if(str == "USB")
        {
            connectors.push_back(new ConnectorRed());
        }
        else if (str == "HDMI")
        {
            connectors.push_back(new ConnectorBlue());
        }
        else if (str == "VGA")
        {
            connectors.push_back(new ConnectorGreen());
        }
        else if (str == "Internet")
        {
            connectors.push_back(new ConnectorCyan());
        }
        else if (str == "Mini jack 3.5 mm")
        {
            connectors.push_back(new ConnectorYellow());
        }
    }
    QString name = ui->lineEditName->text();
    equipment = new Equipment(connectors);
    equipment->name = name;

    EquipmentCreator::close();
}

void EquipmentCreator::on_pushButtonAdd_clicked()
{
    QListWidgetItem *item = new QListWidgetItem();
    *item = *ui->listWidgetConnectors->currentItem();
    ui->listWidgetEquipment->addItem(item);
    listWidgetEquipment_isEmpty = false;
    enable_pushButtonCreate();
}

void EquipmentCreator::on_pushButtonDel_clicked()
{
    QListWidgetItem *item = ui->listWidgetEquipment->takeItem(ui->listWidgetEquipment->currentRow());
    delete item;
    if(ui->listWidgetEquipment->count() == 0)
    {
        ui->pushButtonDel->setEnabled(false);
        listWidgetEquipment_isEmpty = true;
        enable_pushButtonCreate();
    }
}

void EquipmentCreator::on_listWidgetConnectors_itemClicked()
{
    ui->pushButtonAdd->setEnabled(true);
}

void EquipmentCreator::on_listWidgetEquipment_itemClicked()
{
    ui->pushButtonDel->setEnabled(true);
}

void EquipmentCreator::on_listWidgetConnectors_itemDoubleClicked()
{
    EquipmentCreator::on_pushButtonAdd_clicked();
}

void EquipmentCreator::on_listWidgetEquipment_itemDoubleClicked()
{
    EquipmentCreator::on_pushButtonDel_clicked();
}

void EquipmentCreator::on_pushButtonExit_clicked()
{
    EquipmentCreator::close();
}

void EquipmentCreator::on_lineEditName_textChanged()
{
    equipmentName_isGood = ui->lineEditName->hasAcceptableInput();
    enable_pushButtonCreate();
}

void EquipmentCreator::enable_pushButtonCreate()
{
    if(!listWidgetEquipment_isEmpty && equipmentName_isGood)
        ui->pushButtonCreate->setEnabled(true);
    else {
        ui->pushButtonCreate->setEnabled(false);
    }
}
