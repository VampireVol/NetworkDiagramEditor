#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipmentcreator.h"
#include "addequipment.h"
#include "changeequipment.h"
#include "selectpath.h"
#include "createproject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    //numberOfEquipments = 0;
    //equipments = new Equipment[numberOfEquipments];
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

void MainWindow::on_change_equipment_triggered()
{
    ChangeEquipment window;
    window.setModal(true);
    window.exec();
}
