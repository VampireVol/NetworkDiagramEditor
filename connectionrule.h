#ifndef CONNECTIONRULE_H
#define CONNECTIONRULE_H

#include <Qt>

class ConnectionRule
{
public:
    ConnectionRule();

public:
    void SetRule(Qt::GlobalColor color1, Qt::GlobalColor color2, bool rule);
    bool GetRule(Qt::GlobalColor color1, Qt::GlobalColor color2);

private:
    int GetIndex(Qt::GlobalColor color);
    static const int size = 5;
    bool rules[size][size];
};

#endif // CONNECTIONRULE_H
