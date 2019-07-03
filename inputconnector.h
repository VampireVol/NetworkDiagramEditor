#ifndef INPUTCONNECTOR_H
#define INPUTCONNECTOR_H

#include <QPainter>

class OutputConnector;

class InputConnector
{
public:
    InputConnector(Qt::GlobalColor color);
    ~InputConnector();
private:
    Qt::GlobalColor color;
    OutputConnector *link;
};

class InputConnectorRed : public InputConnector
{
public:
    InputConnectorRed();
};

class InputConnectorBlue : public InputConnector
{
public:
    InputConnectorBlue();
};

class InputConnectorGreen : public InputConnector
{
public:
    InputConnectorGreen();
};

class InputConnectorCyan : public InputConnector
{
public:
    InputConnectorCyan();
};

class InputConnectorYellow : public InputConnector
{
public:
    InputConnectorYellow();
};

#endif // INPUTCONNECTOR_H
