#include "../headers/DataHandler.h"

DataHandler::DataHandler()
{

}

DataHandler::~DataHandler()
{
}

DataHandler::DataHandler(const DataHandler &other)
{
   mapTree = other.getMapTree();
}

const BST<DateMap> DataHandler::getMapTree() const
{
    return mapTree;
}

//Used to read in multiple data files, coupled with getDataFromFile.
bool DataHandler::getMultipleDataFiles(string file)
{
    ifstream infile(file);

    if( !infile )
    {
        cout << "Could not find file" << '\n';
        return false;
    }

    string line;


    for(string line; getline(infile, line);)
    {
        if(line.length() != 0) //Check for blank line. ***MORE VALIDATION IS NEEDED HERE***
        {
            line = "data/" + line;
            getDataFromFile(line);
        }

    }

    infile.close();
    return true;
}

//Open CSV file and inserts data from file to a Vector.
//The vector passed in to this function is no const as it needs to be editted.
//Is int as checking if file exists requires an integer return value.
int DataHandler::getDataFromFile(string file)
{

    Vector<Container> tempVecLog; //Data for each day will be stored in this vector
    map<Date, Vector<Container>> mapT; //The vector will be stored in this map with a date to identify which day is being stored.
                                       //This map will be stored into the BST. Operators have been set for comparing the maps.

    //------Get file and check if it was found ------
    ifstream infile( file );

    if( !infile )
    {
        cout << "Could not find file" << '\n';
        return -1;
    }
    //-----------------------------------------------
    Date previousDate; //Used to determine if there is a new month of data or not.
    string line; //line of CSV from file
    int row_count = 0; //increments per row of data

    //loop through each entire line in file
    while(getline(infile, line))
    {
        stringstream  lineStream(line); //string stream treats a string as if it was an ifstream
        string        cell; //actual output

        int column_count = 0;
        row_count +=1;

        //new object to store in windlog each row.
        Date date;
        Time time;
        Container tempLog;

        //loop through the line until theres a comma
        while(getline(lineStream,cell,',') && row_count > 1)//ignore first row (data indentifier not actual data)
        {
            column_count+=1;

            if(cell != "N/A")
            {
                if ( column_count == 1)//If its the first column (date/time)
                {
                    stringstream cellSS(cell); //Used to store value of each CSV
                    string temp;

                    getline(cellSS, temp, '/');
                    date.SetDay(stoll(temp));

                    getline(cellSS, temp, '/');
                    date.SetMonth(stoll(temp));

                    getline(cellSS, temp, ' ');
                    date.SetYear(stoll(temp));

                    getline(cellSS, temp, ':');
                    time.setHours(stoll(temp));

                    getline(cellSS, temp, ',');
                    time.setMinutes(stoll(temp));

                    tempLog.setDate(date);
                    tempLog.setTime(time);
                }

                else if (column_count == 11 )//S column
                {
                    tempLog.setWindSpeed(stof(cell));
                }
                else if (column_count == 12)//SR column
                {
                    tempLog.setSolarRadiation(stof(cell));
                }
                else if(column_count == 18)//T column
                {
                    tempLog.setAmbientTemperature(stof(cell));
                }
            }
        }

        if(previousDate.GetDay() == 0) //Check if previous date has been set yet
            previousDate=tempLog.getDate();//if not set it (this will only happen for the first line of data of the file).

        if(tempLog.getDate().GetMonth() != previousDate.GetMonth())
        {
            Vector<Container> vecLog(tempVecLog); //Store every row of data into a new vector
            previousDate = tempLog.getDate();//set the previous date
            tempVecLog.clear();//Clear the tempVector for the next month of data

            Date temp = tempLog.getDate(); //Create a date set as the date of the current date (will be the 1st at 0:0 of every day)
            temp.SetMonth(vecLog[0].getDate().GetMonth());
            temp.SetYear(vecLog[0].getDate().GetYear());

            mapT.insert(std::make_pair(Date(temp), vecLog)); //insert the vector into a map, each maps unique key will be the starting date of the month

            DateMap dm; //Create a datemap object, this is used to assign a date to a map so the BST can deal with inserting, searching etc.
            dm.setMap(mapT); //Set the map and date of the DateMap
            dm.setDate(temp);

            mapTree.insert(dm); //Insert the map into the BST, each map has a unique Date (each month) so the data can be inserted properly with operator functions.

            mapT.clear();//clear the map for the next month of data
        }

        if(row_count > 1) //Check if row_count was above 1 so an empty tempLog is not entered
        {
            if(tempVecLog.push_back(tempLog))
            {
            }
            else
                cout << "Failed to add container to STL vector" << '\n';
        }

    }
   // mapTree.processNodeInOrder(f1t); //Will show starting date of each month of data being added.
                                     //Can optionally see every data value by uncommenting ostream & operator <<( ostream & os, const Vector<Container> & R ).

    //The following will add the last month of data into the BST.
    //This bug was found late into development so the fix is not very elegant. The last month was not being added due to the logic used earlier in the routine.
    //This fixes is but is not thoroughly tested.
    Date d;
    d.SetDay(1);
    d.SetMonth(tempVecLog[0].getDate().GetMonth());
    d.SetYear(tempVecLog[0].getDate().GetYear());

    DateMap dm;
    dm.setDate(d);

    if(mapTree.search(dm) == false)
    {
        mapT.insert(std::make_pair(Date(d), tempVecLog));
        dm.setMap(mapT);
        mapTree.insert(dm);
    }

    infile.close();

    return 1;
}

bool DataHandler::getWS_M_Y(const Date &date, Vector<float> &outputMonth) const
{
    bool success = false;
    //Create DateMap object to search the BST with.
    DateMap dateMap;    //Create a date map
    dateMap.setDate(date);     //Add the Date to the DateMap

    try
    {
        if(mapTree.search(dateMap))
        {
            DateMap dm = mapTree.get(dateMap);   //Search the map using the DateMap and return a DateMap to a new object
            if(dm.getMap().empty() == false)
            {
                map<Date, Vector<Container>> monthOfData = dm.getMap(); //Get the map from the DateMap and assign the outputMonth

                Vector<Container> vec = monthOfData[date]; //Get the vector from the map

                //loop through the windspeed vector and get the speed
                for(int i = 0; i < vec.getCurrentSize(); i++)
                {
                Container cont;
                float speed = vec[i].getWindSpeed().getSpeed(); //Get each speed value from the vector

                outputMonth.push_back(speed); //add the speed value to the float vector
                }

                success = true;
            }
            else
                success = false;
        }
        else
            success = false;


    }
    catch(const exception &ex)
    {
        success = false;
        cout << "Error finding : " << date << "     " << ex.what() << '\n';
    }

    return success;
}

bool DataHandler::getAT_M_Y(const Date &date, Vector<float> &outputMonth) const
{
    bool success = false;
    //Create DateMap object to search the BST with.
    DateMap dateMap;    //Create a date map
    dateMap.setDate(date);     //Add the Date to the DateMap

    try
    {
        if(mapTree.search(dateMap))
        {
            DateMap dm = mapTree.get(dateMap);   //Search the map using the DateMap and return a DateMap to a new object
            if(dm.getMap().empty() == false)
            {
                map<Date, Vector<Container>> monthOfData = dm.getMap(); //Get the map from the DateMap and assign the outputMonth

                Vector<Container> vec = monthOfData[date]; //Get the vector from the map

                //loop through the ambient temp vector and get the speed
                for(int i = 0; i < vec.getCurrentSize(); i++)
                {
                    Container cont;
                    float temp = vec[i].getAmbientTemperature().getTemp(); //Get each speed value from the vector

                    outputMonth.push_back(temp); //add the speed value to the float vector
                }

                success = true;
            }
            else
                success = false;
        }
        else
            success = false;

    }
    catch(const exception &ex)
    {
        success = false;
        cout << "Error finding : " << date << "     " << ex.what() << '\n';
    }

    return success;

}

bool DataHandler::getSR_M_Y(const Date &date, Vector<float> &outputMonth) const
{
    bool success = false;
    //Create DateMap object to search the BST with.
    DateMap dateMap;    //Create a date map
    dateMap.setDate(date);     //Add the Date to the DateMap

    try
    {
        if(mapTree.search(dateMap))
        {
            DateMap dm = mapTree.get(dateMap);   //Search the map using the DateMap and return a DateMap to a new object
            if(dm.getMap().empty() == false)
            {
                map<Date, Vector<Container>> monthOfData = dm.getMap(); //Get the map from the DateMap and assign the outputMonth

                Vector<Container> vec = monthOfData[date]; //Get the vector from the map

                //loop through the ambient temp vector and get the speed
                for(int i = 0; i < vec.getCurrentSize(); i++)
                {
                    Container cont;
                    float rad = vec[i].getSolarRadiation().getRadiation(); //Get each speed value from the vector

                    if(rad >= 100)
                    {
                        outputMonth.push_back(rad); //add the speed value to the float vector
                    }
                }

                success = true;
            }
            else
                success = false;
        }
        else
            success = false;

    }
    catch(const exception &ex)
    {
        success = false;
        cout << "Error finding : " << date << "     " << ex.what() << '\n';
    }

    return success;
}

bool DataHandler::getSR_D_M_Y(const Date &date, map<Time, float> &outputDay) const
{
    Vector<Container> output;

    bool success = false;
    //Create DateMap object to search the BST with.
    DateMap dateMap;    //Create a date map
    Date searchMonthDate(date);
    searchMonthDate.SetDay(1);
    dateMap.setDate(searchMonthDate);     //Add the Date to the DateMap

    try
    {
        if(mapTree.search(dateMap))
        {
            DateMap dm = mapTree.get(dateMap);   //Search the map using the DateMap and return a DateMap to a new object
            if(dm.getMap().empty() == false)
            {
                map<Date, Vector<Container>> monthOfData = dm.getMap(); //Get the map from the DateMap and assign the outputMonth

                Vector<Container> vec = monthOfData[date]; //Get the vector from the map

                //loop through the ambient temp vector and get the speed
                for(int i = 0; i < vec.getCurrentSize(); i++)
                {
                   // Container cont;
                    float rad = vec[i].getSolarRadiation().getRadiation(); //Get each speed value from the vector

                    if(rad >= 100)
                    {
                        Container cont(vec[i]);

                        if(cont.getDate() == date)
                        {
                            output.push_back(cont); //add the speed value to the float vector
                        }
                    }
                }

                for(int j = 0; j < output.getCurrentSize(); j++)
                {
                    outputDay.insert(std::make_pair(output[j].getTime(), output[j].getSolarRadiation().getRadiation()));

                }
            }
            else
                success = false;
        }
        else
            success = false;

    }
    catch(const exception &ex)
    {
        success = false;
        cout << "Error finding : " << date << "     " << ex.what() << '\n';
    }

    return success;
}

//Outputs the map data in DateMap objects. (BST is made up of DateMap objects)
void f1t(const DateMap &data)
{
    typedef map<Date, Vector<Container>>::const_iterator MapIterator;
    int counter = 0;
    map<Date, Vector<Container>> vecMap = data.getMap();
    for (MapIterator iter = vecMap.begin(); iter != vecMap.end(); iter++)
    {

        cout << "Key: " << iter->first << endl << "Values:" << iter->second << endl;
        counter ++;
        cout << counter;
    }
}

//Overloaded operators for easier output of data
ostream & operator <<( ostream & os, const Container & R )
{
   os << R.getDate() << "   " << R.getTime() << "   " << R.getWindSpeed().getSpeed() << "    " << R.getAmbientTemperature().getTemp() <<
   "    " << R.getSolarRadiation().getRadiation() << '\n';

  return os;
}

ostream & operator <<( ostream & os, const Vector<Container> & R )
{
    //Intentionally left stub in in case seeing every record is required.
    /*for(int i = 0; i < R.getCurrentSize(); i++)
    {
        os << R[i].getDate() << "   " << R[i].getTime() << "   " << R[i].getWindSpeed().getSpeed() << "    " << R[i].getAmbientTemperature().getTemp() <<
        "    " << R[i].getSolarRadiation().getRadiation() << '\n';

    }*/

  return os;
}

ostream & operator <<( ostream & os, const Date & R )
{
   os << R.GetDay() << "/" << R.GetMonth() << "/" << R.GetYear();

  return os;
}

ostream & operator <<( ostream & os, const Time & R )
{
   os << R.getHours() << ":" << R.getMinutes();

  return os;
}

int compare_dates (const Date &d1, const Date& d2)
{
    bool result;

    if (d1.GetYear() < d2.GetYear())
       result = -1;

    else if (d1.GetYear() > d2.GetYear())
       result = 1;

    if (d1.GetYear() == d2.GetYear())
    {
         if (d1.GetMonth()<d2.GetMonth())
              result = -1;
         else if (d1.GetMonth()>d2.GetMonth())
              result = 1;
         else if (d1.GetDay()<d2.GetDay())
              result = -1;
         else if(d1.GetDay()>d2.GetDay())
              result = 1;
         else
              result = 0;
    }

    return result;
}

bool operator <(const Date &d, const Date &d2)
{
    if(compare_dates(d, d2) == -1)
    {
        return true;
    }
    else
        return false;
}

bool operator >(const Date &d, const Date &d2)
{
    if(compare_dates(d, d2) == 1)
    {
        return true;
    }
    else
        return false;
}

bool operator ==(const Date &d, const Date &d2)
{
    if(compare_dates(d, d2) == 0)
    {
        return true;
    }
    else
        return false;
}

ostream & operator <<( ostream & os, const DateMap & R )
{
    cout << R.getMap();

  return os;
}

ostream & operator <<( ostream & os, const map<Date, Vector<Container>> & R )
{
    typedef map<Date, Vector<Container>>::const_iterator MapIterator;

    for (MapIterator iter = R.begin(); iter != R.end(); iter++)
    {
        cout << "Key: " << iter->first << endl << "Values:" << iter->second << endl;
    }

    return os;
}

bool operator ==(const DateMap &d, const DateMap &d2)
{
    if(d.getDate() == d2.getDate())
    {
        return true;
    }
    else
        return false;

    if(d.getDate() < d2.getDate())
    {
        return true;
    }
    else
        return false;
}

bool operator <(const DateMap &d, const DateMap &d2)
{
    if(d.getDate() < d2.getDate())
    {
        return true;
    }
    else
        return false;
}

bool operator >(const DateMap &d, const DateMap &d2)
{
    if(d.getDate() > d2.getDate())
    {
        return true;
    }
    else
        return false;
}

bool operator <(const Time &d, const Time &d2)
{
    if(d.getHours() < d2.getHours())
    {
        return true;
    }
    else if(d.getHours() == d2.getHours())
    {
        if(d.getMinutes() < d2.getMinutes())
        {
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool operator >(const Time &d, const Time &d2)
{
    if(d.getHours() > d2.getHours())
    {
        return true;
    }
    else if(d.getHours() == d2.getHours())
    {
        if(d.getMinutes() > d2.getMinutes())
        {
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool operator ==(const Time &d, const Time &d2)
{
    if(d.getHours() == d2.getHours())
    {
        if(d.getMinutes() == d2.getMinutes())
        {
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

