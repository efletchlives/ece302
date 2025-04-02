#include "list.hpp"

template <typename T>
List<T>::List()
{
  size = 0;
  max_size = 10;
  data = new T[max_size];
}

template <typename T>
List<T>::~List()
{
  delete [] data; // deallocate memory
}

template <typename T>
List<T>::List(const List<T> &x)
{
  // copy size and max size from List x
  size = x.size;
  max_size = x.max_size;
  data = new T[max_size]; // allocate memory for data array

  // deep copy of array data
  for(int i=0;i<size;i++) {
    data[i] = x.data[i];
  }
}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List &x)
{
  std::swap(size,x.size);
  std::swap(max_size,x.max_size);
  std::swap(data,x.data);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  return size==0;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  return size;
}

template <typename T>
void List<T>::insert(std::size_t position, const T &item)
{
  // first check if the position is in the array list
  if(position < 1 || position > size + 1) { // position bounds adjusted to starting index at 1
    throw std::out_of_range("insert position out of range"); // insertion unsuccessful
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
  // insert successful
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  // if position is outside range of size or equal to size since you are removing
  if(position < 1 || position > size) { // position bounds adjusted to starting index at 1
    throw std::out_of_range("remove position out of range"); // removal unsuccessful
  }

  // shift data over in case position is in the middle of data
  for(std::size_t i=(position-1);i<(size-1);i++) { // using size_t makes it more memory efficient than if you were using int
      data[i] = std::move(data[i+1]); 
  }

  size--;
  // removal successful
}

template <typename T>
void List<T>::clear()
{
  size = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  // if the specified position is outside range of size or equal to it, return blank
  if(position < 1 || position > size) {
    throw std::out_of_range("position out of range");
  }
  return data[position-1];
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T &newValue)
{
  if(position < 1 || position > size) {
    throw std::out_of_range("position out of range");
  }
  data[position-1] = newValue;
}
