#ifndef Tempreture_H
#define Tempreture_H

    /**
    * @class Temperature
    * @brief  Abstract base class to represent temperature data.
    * This has been designed to support different type of temperatures e.g.
    * ambient tempereature, soil temperature
    *
    * @author Gareth Griffiths
    * @version 01
    * @date 15/04/2019
    *
    * @todo nill.
    *
    * @bug nill.
    */
class Temperature
{
    public:
        //These are not pure virtual as no modification is needed for child classes
        virtual float getTemp() const {return temp;};
        virtual void setTemp(float tmp) {temp = tmp;};

    protected:
        float temp;
};

#endif
