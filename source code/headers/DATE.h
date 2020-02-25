#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

using namespace std;

/**
    * @class Date
    * @brief  Represents a date in day/month/year
    *
    *
    * @author Gareth Griffiths
    * @version 01
    * @date 26/03/2019
    *
    * @todo nill.
    *
    * @bug nill.
    */

class Date
{
    public:
        Date();

            /**
            * @brief  Constructs a date object
            *
            *@param int day.
            *@param int month.
            *@param int year.
            *@return void
            */
        Date(int day, int month, int year);

            /**
            * @brief  Returns the entire date as string i.e. with forward slash seperator
            *
            * @return string
            */
        string GetEntireDate();

            /**
            * @brief Compares input with months of the year and
            * returns the worded version of the month. e.g. 1 will
            * return Janurary.
            *
            * @param month - the inputed number version of month
            * @return months - the worded month
            */
        string GetMonthText(int month);

        int GetDay() const;
        void SetDay(int iDay);

        int GetMonth() const;
        void SetMonth(int iMonth);

        int GetYear() const;
        void SetYear(int iYear);

    private:
            ///Day of the date object
        int day;
            ///Month of the date object
        int month;
            ///Year of the date object
        int year;
};

#endif
