#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
    /**
    * @class Vector
    * @brief  Encapsulates an STL vector with minimal but complete methods
    *
    * @author Gareth Griffiths
    * @version 03
    * @date 09/04/2019
    *
    * @todo nill.
    *
    * @bug nill.
    */

template <class T>
class Vector
{
    public:
            /**
            * @brief  Constructor to initialise and configure the array
            * properly and the create the array.
            */
        Vector();

            /**
            * @brief  Copy constructor to clone an object into another
            * useful for changing not const to const vector
            */
        Vector(const Vector& tVec);

            /**
            * @brief  Destructor to delete tArray as it is created on the heap.
            */
        ~Vector();


            /**
            * @brief  Gets the current amount of used objects in the vector
            * (Not including elements that are empty)
            *@return unsigned curSize.
            */
        int getCurrentSize() const;


            /**
            * @brief  Overloaded operator [] that returns
            * a constant reference to an array object at
            * specified index. This overloaded operater is used for getting.
            *@param T data.
            *@return void
            */
        T operator [](const unsigned i) const;


            /**
            * @brief  Clear routine that will clear the contents of the vector
            *@return void
            */
        void clear();

            /**
            * @brief  Adds specified data to the vector
            *@param T& data - the data to be added.
            *@return bool - whether adding the data was successful or not.
            */
        bool push_back(T& data);

        Vector<T> & operator=( const Vector<T> &other );

    private:
        vector<T> vec;

};

template<class T>
Vector<T>::Vector()
{
}

template<class T>
Vector<T>::~Vector()
{

}

template<class T>
Vector<T>::Vector(const Vector& tVec)
{
    for(int i = 0; i < tVec.getCurrentSize(); i++)
    {
        vec.push_back(tVec[i]);
    }
}

template<class T>
void Vector<T>::clear()
{
   vec.clear();
}

template<class T>
int Vector<T>::getCurrentSize() const
{
    return vec.size();
}

template<class T>
T Vector<T>::operator [](const unsigned i) const
{
     return vec.at(i);
}

template<class T>
bool Vector<T>::push_back(T& data)
{
    bool okay = true;
	try
	{
		vec.push_back(data);
	}
	catch (...)
	{
		okay = false;
	}

	return okay;
}

template<class T>
Vector<T> & Vector<T>::operator=( const Vector<T> &other )
{
    vec = other.vec;
}

#endif
