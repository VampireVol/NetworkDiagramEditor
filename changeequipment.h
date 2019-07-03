#ifndef CHANGEEQUIPMENT_H
#define CHANGEEQUIPMENT_H

#include <QDialog>

namespace Ui {
class ChangeEquipment;
}

class ChangeEquipment : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeEquipment(QWidget *parent = nullptr);
    ~ChangeEquipment();

private slots:
    void on_back_clicked();

    void on_select_clicked();

private:
    Ui::ChangeEquipment *ui;
};

#endif // CHANGEEQUIPMENT_H
