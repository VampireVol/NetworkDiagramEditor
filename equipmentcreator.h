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
<<<<<<< HEAD
public:
    Equipment *equipment = nullptr;
=======

>>>>>>> Network/master
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

    void on_lineEditName_textChanged();

    void enable_pushButtonCreate();

private:
    Ui::EquipmentCreator *ui;
    bool listWidgetEquipment_isEmpty;
    bool equipmentName_isGood;
    Equipment *equipment = nullptr;
};

#endif // EQUIPMENTCREATOR_H
