#include "../headers/SolarRadiation.h"

SolarRadiation::SolarRadiation()
{
    radiation = 0;
}

float SolarRadiation::getRadiation() const
{
    return radiation;
}

void SolarRadiation::setRadiation(float rad)
{
    radiation = rad;
}
