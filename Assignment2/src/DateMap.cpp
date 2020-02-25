#include "../headers/DateMap.h"

DateMap::DateMap()
{
    vecMap =  map<Date, Vector<Container>>();
}

DateMap::~DateMap()
{

}

DateMap::DateMap(const DateMap &other)
{
    vecMap = other.getMap();
    date = other.getDate();
}

void DateMap::setMap(map<Date, Vector<Container>> &iVecMap)
{
    vecMap = iVecMap;
}

map<Date,Vector<Container>> DateMap::getMap() const
{
    return vecMap;
}

void DateMap::setDate(const Date &iDate)
{
    date.SetDay(iDate.GetDay());
    date.SetMonth(iDate.GetMonth());
    date.SetYear(iDate.GetYear());
}

Date DateMap::getDate() const
{
    return date;
}

const &DateMap::operator =(const DateMap &other)
{
    vecMap = other.getMap();
    date = other.getDate();

}
