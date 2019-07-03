#include "inputconnector.h"

InputConnector::InputConnector(Qt::GlobalColor color)
    : color(color) , link(nullptr)
{

}

InputConnector::~InputConnector()
{

}


InputConnectorRed::InputConnectorRed()
    : InputConnector (Qt::red)
{

}

InputConnectorBlue::InputConnectorBlue()
    : InputConnector (Qt::blue)
{

}

InputConnectorGreen::InputConnectorGreen()
    : InputConnector (Qt::green)
{

}

InputConnectorCyan::InputConnectorCyan()
    : InputConnector (Qt::cyan)
{

}

InputConnectorYellow::InputConnectorYellow()
    : InputConnector (Qt::yellow)
{

}
