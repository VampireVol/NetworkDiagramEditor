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

private slots:
    void on_pushButtonCreate_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonDel_clicked();

    void on_listWidgetConnectors_itemClicked();

    void on_listWidgetEquipment_itemClicked();

    void on_listWidgetConnectors_itemDoubleClicked();

    void on_listWidgetEquipment_itemDoubleClicked();

    void on_pushButtonExit_clicked();

    void on_lineEditName_textChanged();

    void enable_pushButtonCreate();

private:
    Ui::EquipmentCreator *ui;
    bool listWidgetEquipment_isEmpty;
    bool equipmentName_isGood;
    Equipment *equipment = nullptr;
};

#endif // EQUIPMENTCREATOR_H
