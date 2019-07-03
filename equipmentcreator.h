#ifndef EQUIPMENTCREATOR_H
#define EQUIPMENTCREATOR_H

#include <QDialog>

namespace Ui {
class EquipmentCreator;
}

class EquipmentCreator : public QDialog
{
    Q_OBJECT

public:
    explicit EquipmentCreator(QWidget *parent = nullptr);
    ~EquipmentCreator();

private slots:
    void on_pushButtonCreate_clicked();

    void on_pushButtonAddIn_clicked();

private:
    Ui::EquipmentCreator *ui;
};

#endif // EQUIPMENTCREATOR_H
