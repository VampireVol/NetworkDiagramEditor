#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipmentcreator.h"
#include "addequipment.h"
#include "selectpath.h"
#include "createproject.h"
#include <QGraphicsScene>
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

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
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
    EquipmentCreator window;
    window.setModal(true);
    window.exec();
    equipments.push_back(window.CreateEquipment());
    ui->listWidget->addItem(equipments.last());
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
    int row = ui->listWidget->currentRow();
    Equipment *copy = CreateCopy(equipments[row]);
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
    //тут можно поставить выдачу Id
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
    return copy;
}
