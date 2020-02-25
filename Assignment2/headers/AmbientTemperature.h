#ifndef AmbientTemperature_H
#define AmbientTemperature_H

#include "Temperature.h"

    /**
    * @class AmbientTemperature
    * @brief  Class that extends Temperature to store ambient temperature
    * data.
    *
    * @author Gareth Griffiths
    * @version 01
    * @date 15/04/2019
    *
    * @todo nill.
    *
    * @bug nill.
    */
class AmbientTemperature : public Temperature
{
    public:
        AmbientTemperature();

        //No getter and setters and no pure virtual method
        //were defined in Temperature
};

#endif
