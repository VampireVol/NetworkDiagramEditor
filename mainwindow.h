#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "equipment.h"
#include "fileorganizer.h"
#include "projectname.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_equipment_creator_triggered();

    void on_create_triggered();

    void on_open_triggered();

    void on_save_triggered();

    void on_close_triggered();

    void on_add_equipment_triggered();

    void on_listWidget_itemClicked();

    void on_pushAddObj_clicked();

    void on_listWidget_itemDoubleClicked();

    void on_pushDeleteObj_clicked();

    void on_pushDeleteConn_clicked();

    void on_delete_equipment_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QVector <Equipment*> equipmentsInProject;
    QVector <Equipment*> equipmentsInLibrary;
    QVector <Equipment*> equipmentsOnScene;
    int nextEquipmentId;
    int nextConnectorId;
    Equipment* CreateCopy(Equipment *equipment);
    FileOrganizer *fileOrganizer;
};

#endif // MAINWINDOW_H
