#include "equipment.h"

Equipment::Equipment()
{
    body = new Body();
}

Equipment::~Equipment()
{
    delete body;
}
