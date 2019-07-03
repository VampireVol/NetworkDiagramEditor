#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipmentcreator.h"

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

void MainWindow::on_OpenEquipmentCreator_triggered()
{
    EquipmentCreator window;
    window.setModal(true);
    window.exec();
}
