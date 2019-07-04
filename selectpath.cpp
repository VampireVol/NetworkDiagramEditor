#include "selectpath.h"
#include "ui_selectpath.h"
#include "QPushButton"
#include <QRegExpValidator>

SelectPath::SelectPath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectPath)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    QRegExp exp("[a-zA-Z]{1,9}[1-9]{0,2}");
    ui->path->setValidator(new QRegExpValidator(exp, this));
}

SelectPath::~SelectPath()
{
    delete ui;
}


void SelectPath::on_buttonBox_accepted()
{
    //Возвращаем путь
    emit filePath(ui->path->text());
    SelectPath::close();
}

void SelectPath::on_buttonBox_rejected()
{
    SelectPath::close();
}

void SelectPath::on_path_textChanged()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ui->path->hasAcceptableInput());
}
