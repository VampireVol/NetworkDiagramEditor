#include "addrule.h"
#include "ui_addrule.h"
#include "QDebug"

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
    ui->listWidget->addItem(new QListWidgetItem(QIcon(":/img/red_out.png"), "USB"));
    ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/img/red_out.png"), "USB"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon(":/img/blue_out.png"), "HDMI"));
    ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/img/blue_out.png"), "HDMI"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon(":/img/green_out.png"), "VGA"));
    ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/img/green_out.png"), "VGA"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon(":/img/cyan_out.png"), "Internet"));
    ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/img/cyan_out.png"), "Internet"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon(":/img/yellow_out.png"), "Mini jack 3.5 mm"));
    ui->listWidget_2->addItem(new QListWidgetItem(QIcon(":/img/yellow_out.png"), "Mini jack 3.5 mm"));
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
    if(color1 == "USB")
    {
        color_1 = Qt::red;
    }
    else if (color1 == "HDMI")
    {
        color_1 = Qt::blue;
    }
    else if (color1 == "VGA")
    {
        color_1 = Qt::green;
    }
    else if (color1 == "Internet")
    {
        color_1 = Qt::cyan;
    }
    else if (color1 == "Mini jack 3.5 mm")
    {
        color_1 = Qt::yellow;
    }

    if(color2 == "USB")
    {
        color_2 = Qt::red;
    }
    else if (color2 == "HDMI")
    {
        color_2 = Qt::blue;
    }
    else if (color2 == "VGA")
    {
        color_2 = Qt::green;
    }
    else if (color2 == "Internet")
    {
        color_2 = Qt::cyan;
    }
    else if (color2 == "Mini jack 3.5 mm")
    {
        color_2 = Qt::yellow;
    }

}

Qt::GlobalColor AddRule::getColor_1()
{
    return color_1;
}

Qt::GlobalColor AddRule::getColor_2()
{
    return color_2;
}

bool AddRule::getRule()
{
    return rule;
}

bool AddRule::isReject()
{
    return reject;
}

void AddRule::on_reject_clicked()
{
    reject = true;
    AddRule::close();
}

void AddRule::on_allow_clicked()
{
    rule = true;
    addRule();
    AddRule::close();
}

void AddRule::on_ban_clicked()
{
    rule = false;
    addRule();
    AddRule::close();
}
