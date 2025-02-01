#include "array_list.hpp"

// things ive learned
// if you use size_t instead of int, you can save a lot of storage (use less memory).

template <typename T>
// default constructor
ArrayList<T>::ArrayList()
{
  size = 0;
  max_size = 10;
  data = new T[max_size]; // allocates memory for the array list
}

template <typename T>
// destructor
ArrayList<T>::~ArrayList()
{
  delete[] data; // delete data array to deallocate memory
}

template <typename T>
// copy constructor
ArrayList<T>::ArrayList(const ArrayList &rhs)
{
  size = rhs.size;
  max_size = rhs.max_size;
  data = new T[max_size]; // allocates memory for the array list

  // copy data element by element
  for(std::size_t i=0;i<size;++i) {
    data[i] = rhs.data[i];
  }
}

template <typename T>
// copy assignment operator
ArrayList<T> &ArrayList<T>::operator=(ArrayList rhs)
{
  swap(rhs); // uses swap function below
  return *this;
}

template <typename T>
// swap method
void ArrayList<T>::swap(ArrayList &rhs)
{
  std::swap(size, rhs.size);
  std::swap(max_size,rhs.max_size);
  std::swap(data,rhs.data);
}

template <typename T>
// checks if the array is empty
bool ArrayList<T>::isEmpty() const noexcept
{
  return size == 0; // true: size = 0 or empty; false: size > 0
}

template <typename T>
// returns the length of array
std::size_t ArrayList<T>::getLength() const noexcept
{
  return size;
}

template <typename T>
// insert specified item at specified position in the array list
bool ArrayList<T>::insert(std::size_t position, const T &item)
{
  // first check if the position is in the array list
  if(position > size) {
    return false; // if not, return false
  }
  
  if (size == max_size) { // if array list is at max storage

    max_size *= 2; // double the size of the array list
    T* new_data = new T[max_size]; // allocate memory for the array list with more storage

    // copy array list to new array list
    for(std::size_t i=0;i<size;i++) {
      new_data[i] = std::move(data[i]);
    }
    delete[] data; // delete old full array
    data = new_data;
  } 

  // shift data over in case position is middle of data
  for(std::size_t i=size;i>position;i--) {
    data[i] = std::move(data[i-1]); 
  }

  data[position] = item; // insert item in array list
  size++; // increment size
  return true; // insert successful
}

template <typename T>
// removes the value at the specified position from the array list
bool ArrayList<T>::remove(std::size_t position)
{
  // if position is outside range of size or equal to size since you are removing
  if(position >= size) {
    return false; // removal unsuccessful
  }

  // shift data over in case position is in the middle of data
  for(std::size_t i=position;i<(size-1);i++) {
      data[i] = std::move(data[i+1]); 
    }

  size--;
  return true; // removal successful

  // maybe add something that deallocates memory based on the amount of data? a later thing and only if necessary
}

template <typename T>
// clears the array list
void ArrayList<T>::clear()
{
  size = 0;
}

template <typename T>
// gets the value at the specified position in the array list
T ArrayList<T>::getEntry(std::size_t position) const
{
  // if the specified position is outside range of size or equal to it, return blank
  if(position >= size) {
    throw std::out_of_range("position out of range");
  }
  return data[position];
}

template <typename T>
// set the entry at the specified position to the specified value in the array list
void ArrayList<T>::setEntry(std::size_t position, const T &newValue)
{
  if(position < size) {
    data[position] = newValue;
  }
}
