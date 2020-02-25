#include "../headers/TIME.h"


Time::Time()
{
    hours = 0;
    minutes = 0;
}

//Time::Time(Time &other)
//{
//    minutes = other.getMinutes();
//    hours = other.getHours();
//}

Time::Time(unsigned hrs, unsigned mins)
{
    hours = hrs;
    minutes = mins;
}

unsigned Time::getMinutes() const
{
    return minutes;
}

void Time::setMinutes(unsigned mins)
{
    minutes = mins;
}

unsigned Time::getHours() const
{
    return hours;
}

void Time::setHours(unsigned hrs)
{
    hours = hrs;
}
