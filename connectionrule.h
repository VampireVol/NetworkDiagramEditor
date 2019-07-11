#ifndef CONNECTIONRULE_H
#define CONNECTIONRULE_H

#include <Qt>

///Класс, содержащий правила соединений

class ConnectionRule
{
public:
    ConnectionRule(); /// конструктор класса, установка начальных правил (одинаковые виды коннекторов - true, разные - false)

public:
    void SetRule(Qt::GlobalColor color1, Qt::GlobalColor color2, bool rule); /// Установка пользовательский правил, 2 вида коннектора
    bool GetRule(Qt::GlobalColor color1, Qt::GlobalColor color2); /// Получение правила в зависимости от вида коннектора

private:
    int GetIndex(Qt::GlobalColor color); // перевод из цвета в индекс строки/столбца, вспомогательная функция
    static const int size = 5; // установление константного размера количества типов коннекторов
    bool rules[size][size]; // матрица смежности
};

#endif // CONNECTIONRULE_H

