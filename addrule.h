#ifndef ADDRULE_H
#define ADDRULE_H

#include <QDialog>

namespace Ui {
class AddRule;
}


/// Класс для добавления правил соединения
class AddRule : public QDialog
{
    Q_OBJECT

public:
    explicit AddRule(QWidget *parent = nullptr); /// добавление видов коннекторов в List Widget's
    ~AddRule(); /// деструктор класса, удаление ui (using interface)

public:
    Qt::GlobalColor getColor_1(); /// возвращение выбранного вида коннекторов из List Widget
    Qt::GlobalColor getColor_2(); /// возвращение выбранного вида коннекторов из List Widget
    bool getRule(); /// возврат правила возможности соединения
    bool isReject(); /// проверка на нажатие кнопки "Отмена"
private slots:
    void on_listWidget_itemClicked(); // действия при нажатии на объект из виджета_1

    void on_listWidget_2_itemClicked(); //действия при нажатии на объект из виджета_2

    void addRule(); //добавление правила

    void on_reject_clicked(); // действия при нажатии кнопки "Отмена"

    void on_allow_clicked(); // установление разрешающего правила
    void on_ban_clicked(); // установление запрещающего правила

private:
    Ui::AddRule *ui;
    bool listWidget_1_clicked;
    bool listWidget_2_clicked;
    QString color1;
    QString color2;
    bool reject;
    Qt::GlobalColor color_1;
    Qt::GlobalColor color_2;
    bool rule;
};

#endif // ADDRULE_H
