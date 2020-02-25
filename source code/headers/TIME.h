#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>

using namespace std;

    /**
    * @class Time
    * @brief  Represents 24 hour time
    *
    *
    * @author Gareth Griffiths
    * @version 01
    * @date 09/04/2019
    *
    * @todo nill.
    *
    * @bug nill.
    */

class Time
{
    public:
        Time();

        //Time(Time &other);
            /**
            * @brief  Constructs a time object
            *
            *@param unsigned hours.
            *@param unsigned minutes.
            *@return void
            */
        Time(unsigned hrs, unsigned mins);


        unsigned getHours() const;
        void setHours(unsigned hours);

        unsigned getMinutes() const;
        void setMinutes(unsigned minutes);

    private:
            ///Hours in 24 hour time
        unsigned hours;
            ///Minutes of the hour
        unsigned minutes;
};

#endif
