#ifndef WindSpeed_H
#define WindSpeed_H

    /**
    * @class WindSpeed
    * @brief  Class to contain windspeed data and manipulate when needed.
    *
    * @author Gareth Griffiths
    * @version 01
    * @date 16/04/2019
    *
    * @todo nill.
    *
    * @bug nill.
    */
class WindSpeed
{
    public:
        WindSpeed();

        float getSpeed() const;
        void setSpeed(float spd);
    private:
        float speed;
};

#endif
