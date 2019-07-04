#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipmentcreator.h"
#include "addequipment.h"
#include "selectpath.h"
#include "createproject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushAddObj->setEnabled(false);
    ui->pushDeleteObj->setEnabled(false);
    ui->pushAddConn->setEnabled(false);
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
    //создаем файл xml
}

void MainWindow::on_open_triggered()
{
    ui->statusBar->showMessage("Открыть проект");
    SelectPath *window = new SelectPath(this);
    window->show();
    //Загружаем инфу из XML файлов
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
    EquipmentCreator window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_add_equipment_triggered()
{
    AddEquipment window;
    window.setModal(true);
    window.exec();
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

void MainWindow::on_pushAddConn_clicked()
{
    //Добавление связи
}

void MainWindow::on_pushDeleteObj_clicked()
{
    //Удаление выделенного объекта и связи с другими объектами
}

void MainWindow::on_pushDeleteConn_clicked()
{
    //удаление выделенной связи
}
