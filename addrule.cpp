#include "addrule.h"
#include "ui_addrule.h"

AddRule::AddRule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRule)
{
    ui->setupUi(this);
    ui->allow->setEnabled(false);
    ui->ban->setEnabled(false);
    reject = false;
    listWidget_1_clicked = false;
    listWidget_2_clicked = false;
    //QListWidgetItem *itemRed = new QListWidgetItem(QIcon(":/img/red_out.png"), "Красный коннектор");
    ui->listWidget->addItem(new QListWidgetItem(QIcon(":/img/red_out.png"), "Красный коннектор"));
    ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/img/red_out.png"), "Красный коннектор"));
    //QListWidgetItem *itemBlue = new QListWidgetItem(QIcon(":/img/blue_out.png"), "Синий коннектор");
    ui->listWidget->addItem(new QListWidgetItem(QIcon(":/img/blue_out.png"), "Синий коннектор"));
    ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/img/blue_out.png"), "Синий коннектор"));
    //QListWidgetItem *itemGreen = new QListWidgetItem(QIcon(":/img/green_out.png"), "Зеленый коннектор");
    ui->listWidget->addItem(new QListWidgetItem(QIcon(":/img/green_out.png"), "Зеленый коннектор"));
    ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/img/green_out.png"), "Зеленый коннектор"));
    //QListWidgetItem *itemCyan = new QListWidgetItem(QIcon(":/img/cyan_out.png"), "Голубой коннектор");
    ui->listWidget->addItem(new QListWidgetItem(QIcon(":/img/cyan_out.png"), "Голубой коннектор"));
    ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/img/cyan_out.png"), "Голубой коннектор"));
    //QListWidgetItem *itemYellow = new QListWidgetItem(QIcon(":/img/yellow_out.png"), "Желтый коннектор");
    ui->listWidget->addItem(new QListWidgetItem(QIcon(":/img/yellow_out.png"), "Желтый коннектор"));
    ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/img/yellow_out.png"), "Желтый коннектор"));
}

AddRule::~AddRule()
{
    delete ui;
}

void AddRule::on_listWidget_itemClicked()
{
    listWidget_1_clicked = true;
    if(listWidget_2_clicked)
    {
        ui->allow->setEnabled(true);
        ui->ban->setEnabled(true);
    }
    color1 = ui->listWidget->currentItem()->text();
}

void AddRule::on_listWidget_2_itemClicked()
{
    listWidget_2_clicked = true;
    if(listWidget_1_clicked)
    {
        ui->allow->setEnabled(true);
        ui->ban->setEnabled(true);
    }
    color2 = ui->listWidget_2->currentItem()->text();
}

void AddRule::addRule()
{
    if(color1 == "Красный коннектор")
    {
        color_1 = Qt::red;
    }
    else if (color1 == "Синий коннектор")
    {
        color_1 = Qt::blue;
    }
    else if (color1 == "Зеленый коннектор")
    {
        color_1 = Qt::green;
    }
    else if (color1 == "Голубой коннектор")
    {
        color_1 = Qt::cyan;
    }
    else if (color1 == "Желтый коннектор")
    {
        color_1 = Qt::yellow;
    }

    if(color2 == "Красный коннектор")
    {
        color_2 = Qt::red;
    }
    else if (color2 == "Синий коннектор")
    {
        color_2 = Qt::blue;
    }
    else if (color2 == "Зеленый коннектор")
    {
        color_2 = Qt::green;
    }
    else if (color2 == "Голубой коннектор")
    {
        color_2 = Qt::cyan;
    }
    else if (color2 == "Желтый коннектор")
    {
        color_2 = Qt::yellow;
    }
}

int AddRule::getColor_1()
{
    if(!reject)
        return color_1;
    else
        return 0;
}

int AddRule::getColor_2()
{
    if(!reject)
        return color_2;
    else
        return 0;
}

bool AddRule::getRule()
{
    return rule;
}

void AddRule::on_reject_clicked()
{
    reject = true;
    AddRule::close();
}

void AddRule::on_allow_clicked()
{
    rule = true;
    AddRule::close();
}

void AddRule::on_ban_clicked()
{
    rule = false;
    AddRule::close();
}
