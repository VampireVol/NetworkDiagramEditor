#ifndef PROJECTNAME_H
#define PROJECTNAME_H

#include <QDialog>
#include "connectionrule.h"

namespace Ui {
class ProjectName;
}

/// Класс, отвечающий за ввод названия проекта
class ProjectName : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectName(QWidget *parent = nullptr); /// Инициализация диалогового окна
    ~ProjectName(); /// Деструктор класса
public:
    QString projectName(); /// возврат названия проекта

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_projectName_textChanged();

private:
    Ui::ProjectName *ui;
    bool projectName_isSelected;
    ConnectionRule connectionRule;
};

#endif // PROJECTNAME_H
