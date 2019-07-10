#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "equipment.h"
#include "fileorganizer.h"
#include "connectionrule.h"

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

    void on_add_delete_equipment_triggered();

    void on_listWidget_itemClicked();

    void on_pushAddObj_clicked();

    void on_listWidget_itemDoubleClicked();

    void on_pushDeleteObj_clicked();

    void on_pushDeleteConn_clicked();

    void on_delete_equipment_triggered();

    void on_save_as_triggered();

    void on_add_connection_triggered();

private slots:
    void showDescription(Equipment *equipment);

    void on_pushAddDescription_clicked();

    void on_pushAddConn_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QVector <Equipment*> equipmentsInProject;
    QVector <Equipment*> equipmentsInLibrary;
    QVector <Equipment*> equipmentsOnScene;
    int nextEquipmentId;
    FileOrganizer *fileOrganizer;
    QString mainPath;
    ConnectionRule *connectionRule;
};

#endif // MAINWINDOW_H
