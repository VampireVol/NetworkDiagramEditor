#ifndef CONNECTIONRULE_H
#define CONNECTIONRULE_H

#include <Qt>

class ConnectionRule
{
public:
    ConnectionRule();

public:
    void setRule(int color1, int color2, bool rule);
    bool getRule(int color1, int color2);

private:
    bool red_red;
    bool red_blue;
    bool red_cyan;
    bool red_green;
    bool red_yellow;
    bool blue_blue;
    bool blue_cyan;
    bool blue_green;
    bool blue_yellow;
    bool cyan_cyan;
    bool cyan_green;
    bool cyan_yellow;
    bool green_green;
    bool green_yellow;
    bool yellow_yellow;
};

#endif // CONNECTIONRULE_H
