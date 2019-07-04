#ifndef EQUIPMENTCREATOR_H
#define EQUIPMENTCREATOR_H

#include <QDialog>
#include <equipment.h>

namespace Ui {
class EquipmentCreator;
}

class EquipmentCreator : public QDialog
{
    Q_OBJECT

public:
    explicit EquipmentCreator(QWidget *parent = nullptr);
    ~EquipmentCreator();
    Equipment* CreateEquipment();
public:
    Equipment *equipment = nullptr;
private slots:
    void on_pushButtonCreate_clicked();

    void on_pushButtonAddIn_clicked();

    void on_pushButtonAddOut_clicked();

    void on_pushButtonDelInOut_clicked();

    void on_listWidgetIn_itemClicked();

    void on_listWidgetOut_itemClicked();

    void on_listWidgetEquipment_itemClicked();

    void on_listWidgetIn_itemDoubleClicked();

    void on_listWidgetOut_itemDoubleClicked();

    void on_listWidgetEquipment_itemDoubleClicked();

    void on_pushButtonExit_clicked();

private:
    Ui::EquipmentCreator *ui;
};

#endif // EQUIPMENTCREATOR_H
