#include "../headers/Container.h"


Container::Container(){}

/*Container::Container(Container &other)
{
    d.SetDay(other.getDate().GetDay());
    d.SetMonth(other.getDate().GetMonth());
    d.SetYear(other.getDate().GetYear());

    t.setMinutes(other.getTime().getMinutes());
    t.setHours(other.getTime().getHours());

    windSpeed.setSpeed(other.getWindSpeed().getSpeed());

    amTemp.setTemp(other.getAmbientTemperature().getTemp());

    solarRad.setRadiation(other.getSolarRadiation().getRadiation());
}*/

Date Container::getDate() const
{
    return d;
}

void Container::setDate(Date date)
{
    d = date;
}

Time Container::getTime() const
{
    return t;
}

void Container::setTime(Time time)
{
    t = time;
}

WindSpeed Container::getWindSpeed() const
{
    return windSpeed;
}

void Container::setWindSpeed(float speed)
{
    windSpeed.setSpeed(speed);
}

AmbientTemperature Container::getAmbientTemperature() const
{
    return amTemp;
}

void Container::setAmbientTemperature(float temp)
{
    amTemp.setTemp(temp);
}

SolarRadiation Container::getSolarRadiation() const
{
    return solarRad;
}

void Container::setSolarRadiation(float solar)
{
    solarRad.setRadiation(solar);
}

