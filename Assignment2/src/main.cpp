#include <iostream>
#include <limits>
#include <tgmath.h>

#include "../headers/DataHandler.h"

//Used for input validation of the menu option
//Makes sure the number entered falls within a range
bool inRange(int low, int high, int x);

//The following methods are used for converting and formating
//data from the Vector after it has been read in from file.
float calcTotal(const Vector<float> &log);
float calcAverage(const Vector<float> &log);
float mps_to_kmph(float mps); // function to convert speed in m/sec to km/hr/
float WM_to_KwM(float WM);
float truncOneDecimal(float num);

//These routines handle user input and input validation for different dates
Date inputMonthYear();      //Just input the month and year
Date inputDayMonthYear();   //Input day month and year
Date inputYear();           //Just input the year

//The routines below are used for each requirement of the program.
void optionOne(const DataHandler &dh);
void optionTwo(const DataHandler &dh);
void optionThree(const DataHandler &dh);
void optionFour(const DataHandler &dh);
void optionFive(const DataHandler &dh);



int main()
{
    DataHandler dhandler;   //Create a datahandler, this will store and process the data.

    dhandler.getMultipleDataFiles("data/met_index.txt");    //tell the datahandler to get the data from the met_index

    const DataHandler dh(dhandler);     //Create a const version of the datahandler so data cannot be modified

    int running = true;
    while(running)
    {
        int choice;
        cout << '\n' << "1. Average wind speed and ambient temperature for A specific month of year" << '\n'
             << "2. Average wind speed and ambient temperature for EACH month of year" << '\n'
             << "3. Total solar radiation(Kwh/m^2) for each month of a specific year" << '\n'
             << "4. Print Average wind speed (km/h), average ambient air temperature and" << '\n'
             << "total solar radiation in (kWh/m^2) for each month of a specified year" << '\n'
             << "5. Highest solar radiation in (kWh/m^2) for a given day" << '\n'
             << "6. Exit" << '\n';

        cin >> choice;
        //Input validation
        while(cin.fail() || inRange(0, 6, choice) == false)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Invalid input"<<endl;
            cin>>choice;

            if(!cin.fail() && inRange(0, 6, choice) == true)
                break;
        }

        switch(choice)
        {
            case 1:
                optionOne(dh);
                break;
            case 2:
                optionTwo(dh);
                break;
            case 3:
                optionThree(dh);
                break;
            case 4:
                optionFour(dh);
                break;
            case 5:
                optionFive(dh);
                break;
            case 6:
                running = false;
                break;
        }
    }

    return 0;
}

bool inRange(int low, int high, int x)
{
    return ((x-high)*(x-low) <= 0);
}

void optionOne(const DataHandler &dh)
{
    Date date = inputMonthYear();//day is 1 this means it will recieve data from the start of the month
                              //if day was 3 it would get data starting at the 3rd of the month

    Vector<float> monthOfWindSpeed; //Create a new vector of floats to store windspeed data into
    Vector<float> monthOfAmbientTemp;
    float temp; //The calculated temp will be stored here
    float speed;

    if(dh.getWS_M_Y(date, monthOfWindSpeed)) //Send above data to the get windspeed method
    {
        if(dh.getAT_M_Y(date, monthOfAmbientTemp))
        {
            temp = calcAverage(monthOfAmbientTemp);
        }

        speed = calcAverage(monthOfWindSpeed); //This will return the average windpeed
        speed = mps_to_kmph(speed); //This will return the average in kmph

        cout << '\n' << date.GetMonthText(date.GetMonth()) << " " << date.GetYear() << ": " << speed << " km/h,"
             << " " << temp << "degrees C" << '\n';
    }
    else
         cout << '\n' << date.GetMonthText(date.GetMonth()) << " " << date.GetYear() << ": " << "No data" << '\n';

}

void optionTwo(const DataHandler &dh)
{
    Date date = inputYear(); //day is 1 this means it will recieve data from the start of the month
                          //if day was 3 it would get data starting at the 3rd of the month
    Vector<float> monthOfWindSpeed; //Create a new vector of floats to store windspeed data into
    Vector<float> monthOfAmbientTemp;
    float temp; //The calculated temp will be stored here
    float speed;

    cout << '\n' << date.GetYear() << '\n';
    for(unsigned i = 1; i <= 12; i++) //for everymonth, get month of data and output the averages.
    {
        date.SetMonth(i);
        if(dh.getWS_M_Y(date, monthOfWindSpeed)) //Send above data to the get windspeed method
        {
            if(dh.getAT_M_Y(date, monthOfAmbientTemp))
            {
                speed = calcAverage(monthOfWindSpeed); //This will return the average windpeed
                speed = mps_to_kmph(speed); //This will return the average in kmph
                temp = calcAverage(monthOfAmbientTemp);

                cout << date.GetMonthText(date.GetMonth()) << ": " << speed << " km/h, "
                     << temp << " degrees C" << '\n';   //this is the correct average windspeed and ambient temp!!!
            }
            else
                cout << date.GetMonthText(date.GetMonth()) << ": "<< "No data" << '\n';
        }
        else
             cout << date.GetMonthText(date.GetMonth()) << ": "<< "No data" << '\n';

        monthOfWindSpeed.clear();
        monthOfAmbientTemp.clear();
    }
}

void optionThree(const DataHandler &dh)
{
    Date date = inputYear(); //day is 1 this means it will recieve data from the start of the month
                          //if day was 3 it would get data starting at the 3rd of the month

    Vector<float> monthOfRadiation;

    cout << '\n' << date.GetYear() << '\n';
    for(unsigned i = 1; i <= 12; i++)
    {
        date.SetMonth(i);
        if(dh.getSR_M_Y(date, monthOfRadiation) == true)
        {
            float rad = calcTotal(monthOfRadiation); //total radiation values
            rad = WM_to_KwM(rad); //Convert totaled value to Kwh/m^2
            rad = truncOneDecimal(rad); //format to one decimal place

            cout << date.GetMonthText(date.GetMonth()) << ": " << rad << " kWh/m^2" << '\n';
        }
        else
            cout << date.GetMonthText(date.GetMonth()) << ": no data" << '\n';

        monthOfRadiation.clear();
    }
}

void optionFour(const DataHandler &dh)
{
    ofstream ofile( "WindTempSolar.csv");

    Date date = inputYear(); //day is 1 this means it will recieve data from the start of the month
                          //if day was 3 it would get data starting at the 3rd of the month
    Vector<float> monthOfWindSpeed; //Create a new vector of floats to store windspeed data into
    Vector<float> monthOfAmbientTemp;
    Vector<float> monthOfRadiation;
    float temp; //The calculated temp will be stored here
    float speed;
    float rad;

    cout << '\n' << date.GetYear() << '\n';
    ofile << date.GetYear() << '\n';
    for(unsigned i = 1; i <= 12; i++) //for everymonth, get month of data and output the averages.
    {
        date.SetMonth(i);
        if(dh.getWS_M_Y(date, monthOfWindSpeed)) //Send above data to the get windspeed method
        {
            if(dh.getAT_M_Y(date, monthOfAmbientTemp))
            {
                if(dh.getSR_M_Y(date, monthOfRadiation) == true)
                {
                    rad = calcTotal(monthOfRadiation); //total radiation values
                    rad = WM_to_KwM(rad); //Convert totaled value to Kwh/m^2
                    rad = truncOneDecimal(rad); //format to one decimal place

                    speed = calcAverage(monthOfWindSpeed); //This will return the average windpeed
                    speed = mps_to_kmph(speed); //This will return the average in kmph
                    temp = calcAverage(monthOfAmbientTemp);

                    ofile << date.GetMonthText(date.GetMonth()) << ',' << speed << ',' << temp
                    << ',' << rad << '\n';

                    cout << date.GetMonthText(date.GetMonth()) << ',' << speed << ',' << temp
                    << ',' << rad << '\n';
                }
            }
        }

        monthOfWindSpeed.clear();
        monthOfAmbientTemp.clear();
        monthOfRadiation.clear();
    }
}

void optionFive(const DataHandler &dh)
{
    Date date = inputDayMonthYear();

    map<Time, float> dayOfData;         //The day of data will be stored in this
    dh.getSR_D_M_Y(date, dayOfData);    //Every data value that contains date will be stored into dayOfData with its date.

    //Simple algorithm to find the highest value
    float currentMax = 0;
    Time time;
    for(auto it = dayOfData.cbegin(); it != dayOfData.cend(); ++it ) {
        if (it->second > currentMax)
        {
            time = it->first;
            currentMax = it->second;
        }
    }

    cout << '\n' << "Date: " << date << '\n';
    cout << "High solar radiation for the day: " << currentMax << "W/m2" << '\n';

    cout << '\n' << "Time:" << '\n';
    //Output date where the value = the currentMax value.
    for(auto it = dayOfData.cbegin(); it != dayOfData.cend(); ++it )
    {
        if (it->second == currentMax)
        {
            cout << it->first << '\n';
        }
    }
}

Date inputDayMonthYear()
{
    int year, month, day = 0;

    cout << "Enter day : " << '\n';
    cin >> day;

    while(!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input, enter a number" << endl;
        cin >> day;
    }

    cout << "Enter month : " << '\n';
    cin >> month;

    while(!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input, enter a number" << endl;
        cin >> month;
    }

    cout << "Enter year : " << '\n';
    cin >> year;

    while(!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input, enter a number" << endl;
        cin >> year;
    }

    Date date(day, month, year);

    return date;
}

Date inputYear()
{
    int year, month = 0;
    int day = 1;
    cout << "Enter year : " << '\n';
    cin >> year;

    while(!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input, enter a number" << endl;
        cin >> year;
    }

    Date date(day,month,year);

    return date;
}

Date inputMonthYear()
{
    int year;
    int month;
    int day = 1;
    cout << "Enter year : " << '\n';
    cin >> year;

    while(!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input, enter a number" << endl;
        cin >> year;
    }

    cout << "Enter month : " << '\n';
    cin >> month;

    while(!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input, enter a number" << endl;
        cin >> month;
    }

    Date date(day,month,year);

    return date;
}

//The following methods are used for converting and formating
//data from the Vector after it has been read in from file.
float calcTotal(const Vector<float> &log)
{
    float total = 0;
    for(int i = 0; i < log.getCurrentSize(); i++)
    {
        total += log[i];
    }

    return total;
}

float calcAverage(const Vector<float> &log)
{
    float avg = calcTotal(log) / log.getCurrentSize();

    avg = truncOneDecimal(avg);
    return avg;
}

float truncOneDecimal(float num)
{
    return round(num * 10)/10;
}

// function to convert speed
// in m/sec to km/hr
float mps_to_kmph(float mps)
{
    return (3.6 * mps);
}

//function to convert W/m^2 to Kwh/M^2
//assumes the data has been totaled before use, or can be used for
// single piece of W/m^2 data.
float WM_to_KwM(float WM)
{
    return (WM * (1.0/6.0)) / 1000;
}


