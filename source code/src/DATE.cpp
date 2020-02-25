#include "../headers/DATE.h"

Date::Date()
{
    day = 0;
    month = 0;
    year = 0;
}

Date::Date(int iDay, int iMonth, int iYear)
{
    day = iDay;
    month = iMonth;
    year = iYear;
}

string Date::GetEntireDate()
{
    string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    return date;
}

string Date::GetMonthText(int month)
{
    const char * months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    if(month < 0 || month > 12)
    {
        return "Invalid date convertion";
    }
    else
        return months[month - 1];
}

int Date::GetDay() const
{
    return day;
}

void Date::SetDay(int iDay)
{
    day = iDay;
}

int Date::GetMonth() const
{
    return month;
}

void Date::SetMonth(int iMonth)
{
    month = iMonth;
}

int Date::GetYear() const
{
    return year;
}

void Date::SetYear(int iYear)
{
    year = iYear;
}


