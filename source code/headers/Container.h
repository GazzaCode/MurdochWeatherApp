#ifndef Container_H
#define Container_H

#include "WindSpeed.h"
#include "SolarRadiation.h"
#include "AmbientTemperature.h"
#include "DATE.h"
#include "TIME.h"

    /**
    * @class Container
    * @brief  Class to contain objects that are going to be read
    * and edited by a client. This contains related objects together
    * which makes accessing data easier and safer.
    *
    * @author Gareth Griffiths
    * @version 01
    * @date 17/04/2019
    *
    * @todo nill.
    *
    * @bug nill.
    */
class Container
{
public:
    Container();

    //Basic setters and getters for all objects
    Date getDate() const;
    void setDate(Date date);

    Time getTime() const;
    void setTime(Time time);

    WindSpeed getWindSpeed() const;
    void setWindSpeed(float speed);

    AmbientTemperature getAmbientTemperature() const;
    void setAmbientTemperature(float temp); //This needs to use the objects
                                            //set method, so float is passed in, instead of an object.

    SolarRadiation getSolarRadiation() const;
    void setSolarRadiation(float solar);//This needs to use the objects
                                        //set method, so float is passed in, instead of an object.

private:
        ///Date of the sensor output is recorded in this object
    Date d;
        ///Time of the sensor output is recorded in this object
    Time t;
        ///wind speed data is stored in this object
    WindSpeed windSpeed;
        ///ambient temperature data is stored in this object
    AmbientTemperature amTemp;
        ///solar radiation data is stored in this object
    SolarRadiation solarRad;

};



#endif
