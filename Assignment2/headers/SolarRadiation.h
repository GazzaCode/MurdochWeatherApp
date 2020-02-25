#ifndef SolarRadiation_H
#define SolarRadiation_H

    /**
    * @class SolarRadiation
    * @brief  Class to contain solar radiation data and manipulate when needed.
    *
    * @author Gareth Griffiths
    * @version 01
    * @date 15/04/2019
    *
    * @todo nill.
    *
    * @bug nill.
    */
class SolarRadiation
{
    public:
        SolarRadiation();

        float getRadiation() const;
        void setRadiation(float rad);
    private:
        float radiation;
};

#endif
