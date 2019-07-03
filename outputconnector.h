#ifndef OUTPUTCONNECTOR_H
#define OUTPUTCONNECTOR_H

#include <QPainter>

class InputConnctor;
class OutputConnector
{
public:
    OutputConnector(Qt::GlobalColor color);
    ~OutputConnector();
private:
    Qt::GlobalColor color;
    InputConnctor *link;
};

class OutputConnectorRed : public OutputConnector
{
public:
    OutputConnectorRed();
};

class OutputConnectorBlue : public OutputConnector
{
public:
    OutputConnectorBlue();
};

class OutputConnectorGreen : public OutputConnector
{
public:
    OutputConnectorGreen();
};

class OutputConnectorCyan : public OutputConnector
{
public:
    OutputConnectorCyan();
};

class OutputConnectorYellow : public OutputConnector
{
public:
    OutputConnectorYellow();
};

#endif // OUTPUTCONNECTOR_H
