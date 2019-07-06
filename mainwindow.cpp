#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipmentcreator.h"
#include "addequipment.h"
#include "projectname.h"
#include "fileorganizer.h"
#include <QGraphicsScene>
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushAddObj->setEnabled(false);
    ui->pushDeleteObj->setEnabled(false);
    ui->pushDeleteConn->setEnabled(false);
    ui->open_equipment_creator->setEnabled(false);
    ui->add_equipment->setEnabled(false);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    nextEquipmentId = 1;
    nextConnectorId = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_create_triggered()
{
    ui->statusBar->showMessage("Создать проект");
    ProjectName window;
    window.setModal(true);
    window.exec();
    QString projectName = window.projectName();
    if(!projectName.isEmpty())
    {
        ui->open_equipment_creator->setEnabled(true);
        ui->add_equipment->setEnabled(true);
        //Перед этим надо бы удалить старый объект
        fileOrganizer = new FileOrganizer(projectName);
        if(fileOrganizer->createProject())
        {
            QMessageBox::information(this, "Успех", "Проект успешно создан:)");
            ui->listWidget->clear();
        }
        else {
            QMessageBox::warning(this, "Ошибка", "Проект не создан:(");
        }
    }
}

void MainWindow::on_open_triggered()
{
    ui->statusBar->showMessage("Открыть проект");
    ProjectName window;
    window.setModal(true);
    window.exec();
    QString projectName = window.projectName();
    if(!projectName.isEmpty())
    {
        ui->open_equipment_creator->setEnabled(true);
        ui->add_equipment->setEnabled(true);
        //Перед этим надо бы удалить старый объект
        fileOrganizer = new FileOrganizer(projectName);
        int check = fileOrganizer->openProject();
        switch(check)
        {
        case 0:
        {
            QMessageBox::information(this, "Ура:)", "Проект успешно открыт");
            ui->listWidget->clear();
            equipmentsInProject = fileOrganizer->getEquipmentsInProject();
            equipmentsInLibrary = fileOrganizer->getEquipmentsInLibrary();
            for(int i = 0; i < equipmentsInProject.size(); i++)
                ui->listWidget->addItem(equipmentsInProject[i]);
            break;
        }
        case 1:
        {
            QMessageBox::warning(this, "Упс:(", "Проект не найден");
            break;
        }
        case 2:
        {
            QMessageBox::warning(this, "Упс:(", "Ошибка при открытии файла xml");
            break;
        }
        case 3:
        {
            QMessageBox::warning(this, "Упс:(", "Библиотека не найдена:(");
            break;
        }
        default:
        {
            QMessageBox::warning(this, "Упс:(", "Неизвестная ошибка:(");
            break;
        }
        }
    }
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
    if(window.CreateEquipment() != nullptr)
    {
        equipmentsInProject.push_back(window.CreateEquipment());
        equipmentsInProject.last()->SetId(nextEquipmentId, nextConnectorId);
        ui->listWidget->addItem(equipmentsInProject.last());
        fileOrganizer->createEquipment(equipmentsInProject.last());
    }
}

void MainWindow::on_add_equipment_triggered()
{
    AddEquipment window;
    window.loadEquipmentsFromLibrary(equipmentsInLibrary);
    window.setModal(true);
    window.exec();
    if(!window.getAddedEquipments().isEmpty())
    {
        foreach(Equipment *equipment, window.getAddedEquipments())
        {
            equipmentsInProject.push_back(equipment);
            QString name = equipmentsInProject.last()->name;
            equipmentsInProject.last()->setText(name);
            ui->listWidget->addItem(equipmentsInProject.last());
        }
    }
}

void MainWindow::on_listWidget_itemClicked()
{
    ui->pushAddObj->setEnabled(true);
}

void MainWindow::on_pushAddObj_clicked()
{
    //Добавление объекта на схему
    int row = ui->listWidget->currentRow();
    Equipment *copy = CreateCopy(equipmentsInProject[row]);
    equipmentsOnScene.push_back(copy);
    scene->addItem(copy->render->body);
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

Equipment* MainWindow::CreateCopy(Equipment *equipment)
{
    QVector <OutputConnector*> outputs;
    QVector <InputConnector*> inputs;
    QString name = equipment->text();
    int outputSize = equipment->render->outputs.size();
    int inputSize = equipment->render->inputs.size();
    for(int i = 0; i < outputSize; ++i)
    {
        Qt::GlobalColor color = equipment->render->outputs[i]->GetColor();
        switch (color)
        {
        case Qt::red:
        {
            outputs.push_back(new OutputConnectorRed());
            break;
        }
        case Qt::blue:
        {
            outputs.push_back(new OutputConnectorBlue());
            break;
        }
        case Qt::green:
        {
            outputs.push_back(new OutputConnectorGreen());
            break;
        }
        case Qt::cyan:
        {
            outputs.push_back(new OutputConnectorCyan());
            break;
        }
        case Qt::yellow:
        {
            outputs.push_back(new OutputConnectorYellow());
            break;
        }
        default:
            //сюда надо воткнуть месседжбокс который говорит, что что-то пошло не так
            break;
        }
    }
    for(int i = 0; i < inputSize; ++i)
    {
        Qt::GlobalColor color = equipment->render->inputs[i]->GetColor();
        switch (color)
        {
        case Qt::red:
        {
            inputs.push_back(new InputConnectorRed());
            break;
        }
        case Qt::blue:
        {
            inputs.push_back(new InputConnectorBlue());
            break;
        }
        case Qt::green:
        {
            inputs.push_back(new InputConnectorGreen());
            break;
        }
        case Qt::cyan:
        {
            inputs.push_back(new InputConnectorCyan());
            break;
        }
        case Qt::yellow:
        {
            inputs.push_back(new InputConnectorYellow());
            break;
        }
        default:
            //сюда надо воткнуть месседжбокс который говорит, что что-то пошло не так
            break;
        }
    }
    Equipment *copy = new Equipment(outputs, inputs);
    copy->setText(name);
    QString text = QString("id: %1").arg(equipment->equipmentId);
    copy->labelId = new QLabel(text);
    QGraphicsProxyWidget* proxyWidget = new QGraphicsProxyWidget(copy->render->body);
    //тут можно поиграться с отображением
    proxyWidget->setWidget(copy->labelId);

    for(int i = 0; i < inputSize; ++i)
    {
        copy->render->inputs[i]->connectorId = equipment->render->inputs[i]->connectorId;
    }
    for(int i = 0; i < outputSize; ++i)
    {
        copy->render->outputs[i]->connectorId = equipment->render->outputs[i]->connectorId;
    }

    return copy;
}

void MainWindow::on_delete_equipment_triggered()
{

}
