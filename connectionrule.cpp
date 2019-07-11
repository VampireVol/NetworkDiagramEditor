#include "connectionrule.h"
#include <QDebug>
ConnectionRule::ConnectionRule()
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            if(i == j)
            {
                rules[i][j] = true;
            }
            else
            {
                rules[i][j] = false;
            }
        }
    }
}

void ConnectionRule::SetRule(Qt::GlobalColor color1, Qt::GlobalColor color2, bool rule)
{
    int col = GetIndex(color1);
    int row = GetIndex(color2);
    qDebug() << "345" << color1 << color2;
    if (col != -1 && row != -1)
    {
        rules[row][col] = rule;
        rules[col][row] = rule;
        qDebug() << "567" << rule;
    }
}

bool ConnectionRule::GetRule(Qt::GlobalColor color1, Qt::GlobalColor color2)
{
    int col = GetIndex(color1);
    int row = GetIndex(color2);
    //qDebug() << col << row;
    return rules[row][col];
}

int ConnectionRule::GetIndex(Qt::GlobalColor color)
{
    int ind;
    switch (color)
    {
    case Qt::red:
    {
        ind = 0;
        break;
    }
    case Qt::blue:
    {
        ind = 1;
        break;
    }
    case Qt::green:
    {
        ind = 2;
        break;
    }
    case Qt::cyan:
    {
        ind = 3;
        break;
    }
    case Qt::yellow:
    {
        ind = 4;
        break;
    }
    default:
        ind = -1;
        break;
    }
    return ind;
}
