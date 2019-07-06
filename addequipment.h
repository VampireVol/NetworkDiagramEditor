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

    void loadEquipmentsFromLibrary(QVector <Equipment*> equipmentsInLibrary);
    QVector<Equipment*> getAddedEquipments();

private slots:
    void on_pushAdd_clicked();

    void on_pushExit_clicked();

    void on_pushDelete_clicked();

    void on_ListWidgetsAvailable_itemClicked();

    void on_ListWidgetsAvailable_itemDoubleClicked();

    void on_ListWidgetsAdded_itemClicked();

    void on_ListWidgetsAdded_itemDoubleClicked();

    void on_pushOk_clicked();

private:
    Ui::AddEquipment *ui;
    QVector<Equipment*> equipmentsAdded;
    QVector<Equipment*> equipmentsInLibrary;
};

#endif // ADDEQUIPMENT_H
