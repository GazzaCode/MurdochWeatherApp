#ifndef DateMap_H
#define DateMap_H

#include <map>
#include "../headers/Container.h"
#include "../headers/VECTOR.h"

    /**
    * @class DateMap
    * @brief  DateMap will store a map<Date, Vector<Container>> and a Date. This is so each map
    * has a date identifier which will be used by the BST to insert data correctly (with the use of
    * operators).
    *
    * @author Gareth Griffiths
    * @version 03
    * @date 19/05/2019
    *
    * @todo nill.
    *
    * @bug No known bugs
    */

class DateMap
{
    public:
        DateMap();
        ~DateMap();

            /**
            * @brief  Copy constructor to duplicate a DateMap
            * @param const DateMap &other - the other DateMap to copy.
            */
        DateMap(const DateMap &other);

            /**
            * @brief  Set the map of the DateMap.
            * @param map<Date, Vector<Container>> &iVecMap - the map to set this map as
            */
        void setMap(map<Date, Vector<Container>> &iVecMap);

            /**
            * @brief  Set the date of the DateMap.
            * @param Date &iDate - the date to set this date as
            */
        void setDate(const Date &iDate);

            /**
            * @brief  Get this date object of this DateMap
            * @return map<Date, Vector<Container>> - The map of this object
            */
        map<Date,Vector<Container>> getMap() const;

            /**
            * @brief  Get this date object of this DateMap
            * @return Date - the Date of this object
            */
        Date getDate() const;

            /**
            * @brief  Overloaded assignment operator to be able to assign one DateMap to another
            * @param const DateMap &other - the other DateMap to assign this DateMap to.
            */
        const &operator =(const DateMap &other);
    private:
            ///encapsulated map that stores a Vector of containers with a date identifier.
        map<Date, Vector<Container>> vecMap;
            ///encapsulated date to identify the starting month of the map.
        Date date;
};


#endif
