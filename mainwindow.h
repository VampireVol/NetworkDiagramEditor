#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "equipment.h"
#include "fileorganizer.h"
#include "connectionrule.h"
#include "vepolyline.h"

namespace Ui {
class MainWindow;
}

/// Основное окно проекта
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr); /// инициализация объектов в MainWindow
    ~MainWindow(); // Деструктор класса, удаление ui

private slots:
    void on_open_equipment_creator_triggered();

    void on_create_triggered();

    void on_open_triggered();

    void on_save_triggered();

    void on_close_triggered();

    void on_add_delete_equipment_triggered();

    void on_listWidget_itemClicked();

    void on_pushAddObj_clicked();

    void on_listWidget_itemDoubleClicked();

    void on_pushDeleteObj_clicked();

    void on_save_as_triggered();

    void on_add_connection_triggered();

    void showDescription(int equipmentId);

    void showDescriptionPolyline(int polylineId);

    void on_pushAddDescription_clicked();

    void on_pushAddConn_clicked();

    void enable_pushDeleteObj();

    void ennable_pushAddConn();

    void enable_pushAddDescription();

private:
    QString getConnectorType(int color);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QVector <Equipment*> equipmentsInProject;
    QVector <Equipment*> equipmentsInLibrary;
    QVector <Equipment*> equipmentsOnScene;
    int nextEquipmentId;
    int nextPolylineId;
    FileOrganizer *fileOrganizer;
    QString mainPath;
    ConnectionRule *connectionRule;
    QVector <VEPolyline*> connections;
};

#endif // MAINWINDOW_H
