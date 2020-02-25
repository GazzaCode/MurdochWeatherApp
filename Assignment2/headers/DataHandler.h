#ifndef DataHandler_H
#define DataHandler_H

#include <fstream>
#include <sstream>
#include <iostream>

#include "../headers/DATE.h"
#include "../headers/TIME.h"
#include "../headers/Container.h"
#include "../headers/VECTOR.h"
#include "../headers/BST.h"
#include "../headers/DateMap.h"

//operators were included with the classes that needed them, I
// decided it made more sense to have them in one place so the programmer
// does not have to search around for the operators.
bool operator <(const Time &d, const Time &d2);
bool operator >(const Time &d, const Time &d2);
bool operator ==(const Time &d, const Time &d2);

bool operator <(const Date &d, const Date &d2);
bool operator >(const Date &d, const Date &d2);
bool operator ==(const Date &d, const Date &d2);

bool operator ==(const DateMap &d, const DateMap &d2);
bool operator <(const DateMap &d, const DateMap &d2);
bool operator >(const DateMap &d, const DateMap &d2);

 //Method to dertimine if one date is greater, less than or equals to another date.
 //1 if greater than, 0 if equal, -1 if less than.
int compare_dates(const Date* d1, const Date& d2);

//overloaded operators to make output of data easier to deal with
ostream & operator <<( ostream & os, const Vector<Container> & R );
ostream & operator <<( ostream & os, const map<Date, Vector<Container>> & R );
ostream & operator <<( ostream & os,  const Container & R);
ostream & operator <<( ostream & os,  const Date & R);
ostream & operator <<( ostream & os,  const Time & R);
ostream & operator <<( ostream & os, const DateMap & R );

//Pointer function for outputting data in BST
//Used in traversal routines (processNodeInOrder, preOrder, postOrder)
void f1t(const DateMap &data);

 /**
    * @class DataHandler
    * @brief  DataHandler is used to encapsulate all the data gathered and provide
    * routines to process the data for a client program.
    *
    * @author Gareth Griffiths
    * @version 03
    * @date 13/05/2019
    *
    * @todo nill.
    *
    * @bug getDataFromFile requires there to be a next month and revtrieve the last month of data.
    * i.e. month 1/4/2015 must be added to retrieve 1/3/2015
    */

class DataHandler
{
    public:
        DataHandler();
        ~DataHandler();

            /**
            * @brief  Copy constructor to duplicate a DataHandler.
            * @param BST<T> &bst - another BST to copy to this BST
            */
        DataHandler(const DataHandler &other);

            /**
            * @brief  Gets windspeed data for a specified month and stores into a Vecto<float> that is
            * passed in by reference.
            * @param const Date &date - The date object to define what month and year of data to obtain.
            * @param Vector<float> &outputMonth - Where the month of data is going to be stored (created by the client).
            * @return bool - true if the data was read successfully, false if not.
            * @pre data should have already been loaded with getDataFromFile or getMultipleDataFiles.
            */
        bool getWS_M_Y(const Date &date, Vector<float> &outputMonth) const;

            /**
            * @brief  Gets ambient temperature data for a specified month and stores into a Vecto<float> that is
            * passed in by reference.
            * @param const Date &date - The date object to define what month and year of data to obtain.
            * @param Vector<float> &outputMonth - Where the month of data is going to be stored (created by the client).
            * @return bool - true if the data was read successfully, false if not.
            * @pre data should have already been loaded with getDataFromFile or getMultipleDataFiles.
            */
        bool getAT_M_Y(const Date &date, Vector<float> &outputMonth) const;

            /**
            * @brief  Gets solar radiation data for a specified month and stores into a Vecto<float> that is
            * passed in by reference.
            * @param const Date &date - The date object to define what month and year of data to obtain.
            * @param Vector<float> &outputMonth - Where the month of data is going to be stored (created by the client).
            * @return bool - true if the data was read successfully, false if not.
            * @pre data should have already been loaded with getDataFromFile or getMultipleDataFiles.
            */
        bool getSR_M_Y(const Date &date, Vector<float> &outputMonth) const;


            /**
            * @brief  Gets ambient temperature data for a specified day and month and stores into a Vecto<float> that is
            * passed in by reference.
            * @param const Date &date - The date object to define what month and year of data to obtain.
            * @param Vector<float> &outputDay - Where the month of data is going to be stored (created by the client).
            * @return bool - true if the data was read successfully, false if not.
            * @pre data should have already been loaded with getDataFromFile or getMultipleDataFiles.
            */
        bool getSR_D_M_Y(const Date &date, map<Time, float> &outputDay) const;

            /**
            * @brief  The main routine to read the .csv files and store the data into a data structure/s. Will read each
            * cell of data on each row, ignoring data we do not want. If other data is needed, it will need to be added to
            * this routine.
            * @param string file - The csv file to be loaded.
            * @return int - returns 1 if file loaded successfully, -1 if it was not.
            */
        int getDataFromFile(string file);

            /**
            * @brief  This routine is used for loading multiple .csv files into the data structure/s.
            * A file should be created to define which files are to be loaded, this routine will go through
            * that list and load each one of them (Calling getDataFromFile).
            * @param string file - The csv file to be loaded.
            * @return bool - true if the data was read successfully, false if not.
            */
        bool getMultipleDataFiles(string file);

            /**
            * @brief  Gets the mapTree from the DataHandler
            * @return BST<DateMap> - The mapTree contained in DataHandler
            */
        const BST<DateMap> getMapTree() const;

            /**
            * @brief  Sets the BST of this DataHandler
            * @param const BST<DateMap> &other - the other BST to set as this BST
            */

    private:
            ///The encapsulated mapTree
        BST<DateMap> mapTree;

};




#endif
