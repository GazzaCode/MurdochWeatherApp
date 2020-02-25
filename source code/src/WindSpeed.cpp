#include "../headers/WindSpeed.h"

WindSpeed::WindSpeed()
{
    speed = 0;
}

float WindSpeed::getSpeed() const
{
    return speed;
}

void WindSpeed::setSpeed(float spd)
{
    speed = spd;
}
