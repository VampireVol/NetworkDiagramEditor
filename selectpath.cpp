<<<<<<< HEAD
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
=======
#include "selectpath.h"
#include "ui_selectpath.h"
#include "QPushButton"

SelectPath::SelectPath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectPath)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    model = new QFileSystemModel;
    model->setFilter(QDir::Dirs);
    model->setRootPath("");
    ui->listView->setModel(model);
}

SelectPath::~SelectPath()
{
    delete ui;
}

void SelectPath::on_listView_doubleClicked(const QModelIndex &index)
{
    QListView *listView = ui->listView;
    QFileInfo fileInfo = model->fileInfo(index);
    if(fileInfo.fileName() == "..")
    {
        QDir dir = fileInfo.dir();
        dir.cdUp();
        listView->setRootIndex(model->index(dir.absolutePath()));
    }
    else if(fileInfo.fileName() == ".")
    {
        listView->setRootIndex(model->index(""));
    }
    else if(fileInfo.isDir())
    {
        listView->setRootIndex(index);
    }


}

void SelectPath::on_buttonBox_accepted()
{

}

void SelectPath::on_buttonBox_rejected()
{

}

void SelectPath::on_listView_clicked(const QModelIndex &index)
{

}
>>>>>>> Network/master
