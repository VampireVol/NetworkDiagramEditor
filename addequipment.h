#ifndef ADDEQUIPMENT_H
#define ADDEQUIPMENT_H

#include <QDialog>
#include "equipment.h"

/// интерфейс для добавления оборудования


namespace Ui {
class AddEquipment;
}


/// класс интерфейс для добавления оборудования
class AddEquipment : public QDialog
{
    Q_OBJECT ///для сигналов и слотов

public:
    explicit AddEquipment(QWidget *parent = nullptr); /// конструктор создания окна, установка стандартные состояния кнопок
    ~AddEquipment(); /// деструктор, удаление ui (using interface)

    void loadEquipments(QVector <Equipment*> equipmentsInLibrary, QVector<Equipment*> equipmentsInProject); /// загрузка из библиотеки и из проекта списков оборудования
    QVector<Equipment*> getEquipmentsInProject(); /// отправляет список оборудования в проекте
    QVector<Equipment*> getEquipmentsInLibrary(); /// отправляет список оборудования из библиотеки
    bool reject_isClicked(); /// проверка на нажатие кнопки "Отмена"

private slots: 
    void on_pushAdd_clicked(); // добавление из одного виджета в другой

    void on_pushReject_clicked(); // действия при нажатии кнопки "Отмена"

    void on_pushDelete_clicked(); // действия при нажатии кнопки "Удалить", удаление объекта из виджета

    void on_ListWidgetsLibrary_itemClicked(); //действия при нажатии на объект из виджета_1

    void on_ListWidgetsLibrary_itemDoubleClicked(); // добавление из одного виджета в другой

    void on_ListWidgetsProject_itemClicked(); // действия при нажатии на объект из виджета_2

    void on_ListWidgetsProject_itemDoubleClicked(); // добавление из одного виджета в другой

    void on_pushOk_clicked(); // действия при нажатии кнопки "Ок"

private:
    Ui::AddEquipment *ui;
    QVector<Equipment*> equipmentsInProject;
    QVector<Equipment*> equipmentsInLibrary;
    bool reject;
    bool library_hasFocus;
    bool project_hasFocus;
};

#endif // ADDEQUIPMENT_H
