#include "list.hpp"

template <typename T>
// default constructor
List<T>::List()
{
  size = 0;
  max_size = 10;
  data = new T[max_size]; // allocates memory for the array list
}

template <typename T>
// destructor
List<T>::~List()
{
  clear(); // clearing the array helps to avoid dangling pointers and memory leaks
  delete [] data; // deallocate memory
}

template <typename T>
// copy constructor
List<T>::List(const List<T>& x)
{
  size = x.size;
  max_size = x.max_size;
  data = new T[max_size]; // allocates memory for the array list

  // copy data element by element
  for(std::size_t i=0;i<size;i++) { // using size_t makes it more memory efficient than if you were using int
    data[i] = x.data[i];
  }
}

template <typename T>
// copy assignment operator
List<T>& List<T>::operator=(List<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
// swap method
void List<T>::swap(List& x) 
{
  // swap each private member
  std::swap(size,x.size);
  std::swap(max_size,x.max_size);
  std::swap(data,x.data);
}

template <typename T>
// checks if the array is empty
bool List<T>::isEmpty() const noexcept
{
  return size == 0; // true: size = 0 or empty; false: size > 0
}

template <typename T>
// returns the length of array
std::size_t List<T>::getLength() const noexcept
{
  return size;
}

template <typename T>
// insert specified item at specified position in the array list
bool List<T>::insert(std::size_t position, const T& item)
{
  // first check if the position is in the array list
  if(position < 1 || position > size + 1) { // position bounds adjusted to starting index at 1
    return false; // position out of range
  }
  
  if (size == max_size) { // if array list is at max storage

    max_size *= 2; // double the size of the array list
    T* new_data = new T[max_size]; // allocate memory for the array list with more storage

    // copy array list to new array list
    for(std::size_t i=0;i<size;i++) { // using size_t makes it more memory efficient than if you were using int
      new_data[i] = std::move(data[i]);
    }
    delete[] data; // delete old full array
    data = new_data;
  } 

  // shift data over in case position is middle of data
  for(std::size_t i=size;i>(position-1);i--) { // using size_t makes it more memory efficient than if you were using int
    data[i] = std::move(data[i-1]); 
  }

  data[position-1] = item; // insert item in array list
  size++; // increment size
  return true; // insert successful
}

template <typename T>
// removes the value at the specified position from the array list
bool List<T>::remove(std::size_t position)
{
  // if position is outside range of size or equal to size since you are removing
  if(position < 1 || position > size) { // position bounds adjusted to starting index at 1
    return false; // removal unsuccessful
  }

  // shift data over in case position is in the middle of data
  for(std::size_t i=(position-1);i<(size-1);i++) { // using size_t makes it more memory efficient than if you were using int
      data[i] = std::move(data[i+1]); 
  }

  size--;
  // maybe put functionality in to resize the array later?
  return true; // removal successful
}

template <typename T>
// clears the array list
void List<T>::clear()
{
  size = 0;
  // maybe change max size and deallocate and allocate new memory
  max_size = 10;
}

template <typename T>
// gets the value at the specified position in the array list
T List<T>::getEntry(std::size_t position) const
{
  // if the specified position is outside range of size or equal to it, throw exception
  if(position < 1 || position > size) {
    throw std::out_of_range("position out of range (getEntry)");
  }
  return data[position-1];
}

template <typename T>
// set the entry at the specified position to the specified value in the array list
void List<T>::setEntry(std::size_t position, const T& newValue)
{
  if(position < 1 || position > size) {
    throw std::out_of_range("position out of range (setEntry)");
  }
  data[position-1] = newValue;
}

template <typename T>
// moves entry from one position to another position in the array and shifts the array over
void List<T>::moveEntry(std::size_t from, std::size_t to)
{
  if(from < 1 || from > size || to < 1 || to > size) {
    throw std::out_of_range("position out of range (moveEntry)");
  }
  if(from == to) { // if the 1st position is equal to the 2nd
    return;
  }

  T temp = data[from-1]; // store value at "from" position

  if(from < to) {
    // shift elements over 1 to the left in between the positions 
    for(int i=from;i<to;i++) {
      data[i-1] = data[i];
    }
  }
  else {
    // shift elements over 1 to the right in between the positions 
    for(int i=from;i>to;i--) {
      data[i-1] = data[i-2];
    }
  }

  // data[from-1] = data[to-1]; moveEntry doesn't swap the positions, it just moves the value at "from" position to "to" position and shifts the array between the two positions
  data[to-1] = temp;

}
