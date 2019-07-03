#include "createproject.h"
#include "ui_createproject.h"
#include "QPushButton"

CreateProject::CreateProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateProject)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(okClicked()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), SLOT(close()));
}

CreateProject::~CreateProject()
{
    delete ui;
}
