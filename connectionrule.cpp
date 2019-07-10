#include "connectionrule.h"

ConnectionRule::ConnectionRule()
    :red_red(true),
     red_blue(false),
     red_cyan(false),
     red_green(false),
     red_yellow(false),
     blue_blue(true),
     blue_cyan(false),
     blue_green(false),
     blue_yellow(false),
     cyan_cyan(true),
     cyan_green(false),
     cyan_yellow(false),
     green_green(true),
     green_yellow(false),
     yellow_yellow(true)
{

}

void ConnectionRule::setRule(int color1, int color2, bool rule)
{
    if(color1 == Qt::red && color2 == Qt::red)
        red_red = rule;
    else if(color1 == Qt::red && color2 == Qt::blue)
        red_blue = rule;
    else if(color1 == Qt::red && color2 == Qt::cyan)
        red_cyan = rule;
    else if(color1 == Qt::red && color2 == Qt::yellow)
        red_yellow = rule;
    else if(color1 == Qt::red && color2 == Qt::green)
        red_green = rule;
    else if(color1 == Qt::blue && color2 == Qt::blue)
        blue_blue = rule;
    else if(color1 == Qt::blue && color2 == Qt::cyan)
        blue_cyan = rule;
    else if(color1 == Qt::blue && color2 == Qt::green)
        blue_green = rule;
    else if(color1 == Qt::blue && color2 == Qt::yellow)
        blue_yellow = rule;
    else if(color1 == Qt::cyan && color2 == Qt::cyan)
        cyan_cyan = rule;
    else if(color1 == Qt::cyan && color2 == Qt::green)
        cyan_green = rule;
    else if(color1 == Qt::cyan && color2 == Qt::yellow)
        cyan_yellow = rule;
    else if(color1 == Qt::green && color2 == Qt::green)
        green_green = rule;
    else if(color1 == Qt::green && color2 == Qt::yellow)
        green_yellow = rule;
    else if(color1 == Qt::yellow && color2 == Qt::yellow)
        yellow_yellow = rule;
}

bool ConnectionRule::getRule(int color1, int color2)
{
    if(color1 == Qt::red && color2 == Qt::red)
        return red_red;
    else if(color1 == Qt::red && color2 == Qt::blue)
        return red_blue;
    else if(color1 == Qt::red && color2 == Qt::cyan)
        return red_cyan;
    else if(color1 == Qt::red && color2 == Qt::yellow)
        return red_yellow;
    else if(color1 == Qt::red && color2 == Qt::green)
        return red_green;
    else if(color1 == Qt::blue && color2 == Qt::blue)
        return blue_blue;
    else if(color1 == Qt::blue && color2 == Qt::cyan)
        return blue_cyan;
    else if(color1 == Qt::blue && color2 == Qt::green)
        return blue_green;
    else if(color1 == Qt::blue && color2 == Qt::yellow)
        return blue_yellow;
    else if(color1 == Qt::cyan && color2 == Qt::cyan)
        return cyan_cyan;
    else if(color1 == Qt::cyan && color2 == Qt::green)
        return cyan_green;
    else if(color1 == Qt::cyan && color2 == Qt::yellow)
        return cyan_yellow;
    else if(color1 == Qt::green && color2 == Qt::green)
        return green_green;
    else if(color1 == Qt::green && color2 == Qt::yellow)
        return green_yellow;
    else if(color1 == Qt::yellow && color2 == Qt::yellow)
        return yellow_yellow;

    return false;
}
