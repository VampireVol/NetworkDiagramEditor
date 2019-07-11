#ifndef EQUIPMENTCREATOR_H
#define EQUIPMENTCREATOR_H

#include <QDialog>
#include <equipment.h>

namespace Ui {
class EquipmentCreator;
}

///Класс, описывающий создание оборудования
class EquipmentCreator : public QDialog
{
    Q_OBJECT

public:
    explicit EquipmentCreator(QWidget *parent = nullptr); /// конструктор окна, создание ui
    ~EquipmentCreator(); /// деструктор класса, удаление ui
    Equipment* CreateEquipment(); /// функция создания экземлпяра оборудования

private slots:
    void on_pushButtonCreate_clicked(); //нажатие на кнопку "создать"

    void on_pushButtonAdd_clicked(); // нажатие на кнопку "добавить"

    void on_pushButtonDel_clicked(); // нажатие на кнопку "удалить"

    void on_listWidgetConnectors_itemClicked(); // нажатие на объект из виджета

    void on_listWidgetEquipment_itemClicked(); // виджет с коннекторами на оборудовании

    void on_listWidgetConnectors_itemDoubleClicked(); // двойной клик по 1 виджету

    void on_listWidgetEquipment_itemDoubleClicked();// двойной клик по 2 виджету

    void on_pushButtonExit_clicked(); //  нажатие на кнопку "отмена"

    void on_lineEditName_textChanged(); // реакция на изменение текста

    void enable_pushButtonCreate(); // нажатие на кнопку "создать"

private:
    Ui::EquipmentCreator *ui;
    bool listWidgetEquipment_isEmpty;
    bool equipmentName_isGood;
    Equipment *equipment = nullptr;
};

#endif // EQUIPMENTCREATOR_H
