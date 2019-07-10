#include "adddescription.h"
#include "ui_adddescription.h"

AddDescription::AddDescription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDescription)
{
    ui->setupUi(this);
    ui->ok->setEnabled(false);
}

AddDescription::~AddDescription()
{
    delete ui;
}

void AddDescription::on_plainTextEdit_textChanged()
{
}

void AddDescription::on_ok_clicked()
{
    AddDescription::close();
}

void AddDescription::on_reject_clicked()
{
    AddDescription::close();
}
