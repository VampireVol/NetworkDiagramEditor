#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipmentcreator.h"
#include "addequipment.h"
#include "selectpath.h"
#include "createproject.h"
#include "QFile"
#include "QDir"
#include "QTextStream"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushAddObj->setEnabled(false);
    ui->pushDeleteObj->setEnabled(false);
    ui->pushDeleteConn->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_create_triggered()
{
    ui->statusBar->showMessage("Создать новый проект");
    CreateProject *window = new CreateProject(this);
    window->show();
    connect(window, SIGNAL(projectName(QString)), this, SLOT(createProject(QString)));
    //создаем файл xml
}

void MainWindow::on_open_triggered()
{
    ui->statusBar->showMessage("Открыть проект");
    SelectPath *window = new SelectPath(this);
    window->show();
    connect(window, SIGNAL(filePath(QString)), this, SLOT(readFile(QString)));
}

void MainWindow::readFile(const QString &filePath)
{
    //Считываем инфу из файла существующего проекта
    QFile file(filePath);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Не корректный путь");
        return;
    }

    QTextStream stream(&file);
    QString buffer = stream.readAll();
    //ui->textEdit->setText(buffer);
    file.flush();
    file.close();
}

void MainWindow::createProject(const QString &projectName)
{
    //Создаем директорию нового проекта
    QDir dir("V:/study/My projects/practics/NetworkDiagramEditor-master/projects");
    if(!dir.exists())
    {
        QMessageBox::warning(this, "Error", "Не найдена директория");
        return;
    }
    dir.mkdir(projectName);

    //...
}

void MainWindow::on_save_triggered()
{
    ui->statusBar->showMessage("Сохранить");
}

void MainWindow::on_close_triggered()
{
    QApplication::quit();
}

void MainWindow::on_open_equipment_creator_triggered()
{
    EquipmentCreator *window = new EquipmentCreator(this);
    window->show();
}

void MainWindow::on_add_equipment_triggered()
{
    AddEquipment *window = new AddEquipment(this);
    window->show();
}

void MainWindow::on_listWidget_itemClicked()
{
    ui->pushAddObj->setEnabled(true);
}

void MainWindow::on_pushAddObj_clicked()
{
    //Добавление объекта на схему
}

void MainWindow::on_listWidget_itemDoubleClicked()
{
    MainWindow::on_pushAddObj_clicked();
}

void MainWindow::on_pushDeleteObj_clicked()
{
    //Удаление выделенного объекта и связи с другими объектами
}

void MainWindow::on_pushDeleteConn_clicked()
{
    //удаление выделенной связи
}
