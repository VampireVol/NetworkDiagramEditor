#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include<QVector>
#include<QString>
#include<body.h>

//class Output;
//class Input;

class Equipment
{
public:
    Equipment();
    ~Equipment();
    //QVector <Output>outputs;
    //QVector <Input>inputs;
    QString name;

private:
    Body *body;
};

#endif // EQUIPMENT_H
