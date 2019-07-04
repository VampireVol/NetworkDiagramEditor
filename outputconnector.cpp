#include "outputconnector.h"

OutputConnector::OutputConnector(Qt::GlobalColor color)
    : color(color), link(nullptr)
{

}

OutputConnector::~OutputConnector()
{

}


OutputConnectorRed::OutputConnectorRed()
    : OutputConnector (Qt::red)
{

}

OutputConnectorBlue::OutputConnectorBlue()
    : OutputConnector (Qt::blue)
{

}

OutputConnectorGreen::OutputConnectorGreen()
    : OutputConnector (Qt::green)
{

}

OutputConnectorCyan::OutputConnectorCyan()
    : OutputConnector (Qt::cyan)
{

}

OutputConnectorYellow::OutputConnectorYellow()
    : OutputConnector (Qt::yellow)
{

}
