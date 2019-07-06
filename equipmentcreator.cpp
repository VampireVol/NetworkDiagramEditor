#include "equipmentcreator.h"
#include "ui_equipmentcreator.h"
#include <QMessageBox>
#include <QRegExpValidator>

EquipmentCreator::EquipmentCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EquipmentCreator)
{
    ui->setupUi(this);
    QListWidgetItem *itemRedIn = new QListWidgetItem(QIcon(":/img/red_in.png"), "Красный вход");
    ui->listWidgetIn->addItem(itemRedIn);
    QListWidgetItem *itemBlueIn = new QListWidgetItem(QIcon(":/img/blue_in.png"), "Синий вход");
    ui->listWidgetIn->addItem(itemBlueIn);
    QListWidgetItem *itemGreenIn = new QListWidgetItem(QIcon(":/img/green_in.png"), "Зеленый вход");
    ui->listWidgetIn->addItem(itemGreenIn);
    QListWidgetItem *itemCyanIn = new QListWidgetItem(QIcon(":/img/cyan_in.png"), "Голубой вход");
    ui->listWidgetIn->addItem(itemCyanIn);
    QListWidgetItem *itemYellowIn = new QListWidgetItem(QIcon(":/img/yellow_in.png"), "Желтый вход");
    ui->listWidgetIn->addItem(itemYellowIn);

    QListWidgetItem *itemRedOut = new QListWidgetItem(QIcon(":/img/red_out.png"), "Красный выход");
    ui->listWidgetOut->addItem(itemRedOut);
    QListWidgetItem *itemBlueOut = new QListWidgetItem(QIcon(":/img/blue_out.png"), "Синий выход");
    ui->listWidgetOut->addItem(itemBlueOut);
    QListWidgetItem *itemGreenOut = new QListWidgetItem(QIcon(":/img/green_out.png"), "Зеленый выход");
    ui->listWidgetOut->addItem(itemGreenOut);
    QListWidgetItem *itemCyanOut = new QListWidgetItem(QIcon(":/img/cyan_out.png"), "Голубой выход");
    ui->listWidgetOut->addItem(itemCyanOut);
    QListWidgetItem *itemYellowOut = new QListWidgetItem(QIcon(":/img/yellow_out.png"), "Желтый выход");
    ui->listWidgetOut->addItem(itemYellowOut);

    QRegExp exp("[a-zA-Z]{1,9}[1-9]{0,2}");
    ui->lineEditName->setValidator(new QRegExpValidator(exp, this));

    listWidgetEquipment_isEmpty = true;
    equipmentName_isGood = false;
    ui->pushButtonAddIn->setEnabled(false);
    ui->pushButtonAddOut->setEnabled(false);
    ui->pushButtonDelInOut->setEnabled(false);
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
    QVector <OutputConnector*> outputs;
    QVector <InputConnector*> inputs;
    QString str;

    while (QListWidgetItem *item = ui->listWidgetEquipment->takeItem(0))
    {
        str = item->text();
        if(str == "Красный вход")
        {
            inputs.push_back(new InputConnectorRed());
        }
        else if (str == "Синий вход")
        {
            inputs.push_back(new InputConnectorBlue());
        }
        else if (str == "Зеленый вход")
        {
            inputs.push_back(new InputConnectorGreen());
        }
        else if (str == "Голубой вход")
        {
            inputs.push_back(new InputConnectorCyan());
        }
        else if (str == "Желтый вход")
        {
            inputs.push_back(new InputConnectorYellow());
        }
        else if (str == "Красный выход")
        {
            outputs.push_back(new OutputConnectorRed());
        }
        else if (str == "Синий выход")
        {
            outputs.push_back(new OutputConnectorBlue());
        }
        else if (str == "Зеленый выход")
        {
            outputs.push_back(new OutputConnectorGreen());
        }
        else if (str == "Голубой выход")
        {
            outputs.push_back(new OutputConnectorCyan());
        }
        else if (str == "Желтый выход")
        {
            outputs.push_back(new OutputConnectorYellow());
        }
    }
    QString name = ui->lineEditName->text();
    equipment = new Equipment(outputs, inputs);
    equipment->setText(name);
    equipment->name = name;

    EquipmentCreator::close();
}

void EquipmentCreator::on_pushButtonAddIn_clicked()
{
    QListWidgetItem *item = new QListWidgetItem();
    *item = *ui->listWidgetIn->currentItem();
    ui->listWidgetEquipment->addItem(item);
    listWidgetEquipment_isEmpty = false;
    enable_pushButtonCreate();
}

void EquipmentCreator::on_pushButtonAddOut_clicked()
{
    QListWidgetItem *item = new QListWidgetItem();
    *item = *ui->listWidgetOut->currentItem();
    ui->listWidgetEquipment->addItem(item);
    listWidgetEquipment_isEmpty = false;
    enable_pushButtonCreate();
}

void EquipmentCreator::on_pushButtonDelInOut_clicked()
{
    QListWidgetItem *item = ui->listWidgetEquipment->takeItem(ui->listWidgetEquipment->currentRow());
        delete item;
    if(ui->listWidgetEquipment->count() == 0)
    {
        ui->pushButtonDelInOut->setEnabled(false);
        listWidgetEquipment_isEmpty = true;
        enable_pushButtonCreate();
    }
}

void EquipmentCreator::on_listWidgetIn_itemClicked()
{
    ui->pushButtonAddIn->setEnabled(true);
}

void EquipmentCreator::on_listWidgetOut_itemClicked()
{
    ui->pushButtonAddOut->setEnabled(true);
}

void EquipmentCreator::on_listWidgetEquipment_itemClicked()
{
    ui->pushButtonDelInOut->setEnabled(true);
}

void EquipmentCreator::on_listWidgetIn_itemDoubleClicked()
{
    EquipmentCreator::on_pushButtonAddIn_clicked();
}

void EquipmentCreator::on_listWidgetOut_itemDoubleClicked()
{
    EquipmentCreator::on_pushButtonAddOut_clicked();
}

void EquipmentCreator::on_listWidgetEquipment_itemDoubleClicked()
{
    EquipmentCreator::on_pushButtonDelInOut_clicked();
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
