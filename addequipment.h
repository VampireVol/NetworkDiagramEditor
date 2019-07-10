#ifndef ADDEQUIPMENT_H
#define ADDEQUIPMENT_H

#include <QDialog>
#include "equipment.h"

namespace Ui {
class AddEquipment;
}

class AddEquipment : public QDialog
{
    Q_OBJECT

public:
    explicit AddEquipment(QWidget *parent = nullptr);
    ~AddEquipment();

    void loadEquipments(QVector <Equipment*> equipmentsInLibrary, QVector<Equipment*> equipmentsInProject);
    QVector<Equipment*> getEquipmentsInProject();
    QVector<Equipment*> getEquipmentsInLibrary();
    bool reject_isClicked();

private slots: 
    void on_pushAdd_clicked();

    void on_pushReject_clicked();

    void on_pushDelete_clicked();

    void on_ListWidgetsLibrary_itemClicked();

    void on_ListWidgetsLibrary_itemDoubleClicked();

    void on_ListWidgetsProject_itemClicked();

    void on_ListWidgetsProject_itemDoubleClicked();

    void on_pushOk_clicked();

private:
    Ui::AddEquipment *ui;
    QVector<Equipment*> equipmentsInProject;
    QVector<Equipment*> equipmentsInLibrary;
    bool reject;
    bool library_hasFocus;
    bool project_hasFocus;
};

#endif // ADDEQUIPMENT_H
