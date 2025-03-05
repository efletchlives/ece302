#include "sorted_list.hpp"
#include <stdexcept>

template <typename T>
// default constructor
SortedList<T>::SortedList(): List<T>()
{
  // uses the list implementation
}

template <typename T>
// copy constructor (unsorted -> sorted)
SortedList<T>::SortedList(const List<T>& unsorted_list) 
{
  for(size_t i=1;i<=unsorted_list.getLength();i++) {
    insert(unsorted_list.getEntry(i)); // uses the sorted list insert to insert the items of the unsorted list in order
  }
}

template <typename T>
// copy constructor (sorted -> sorted)
SortedList<T>::SortedList(const SortedList<T> & x):
  List<T>(x)
{
  // uses the List implementation so nothing needed here
}

template <typename T>
// copy assignment operator
SortedList<T>& SortedList<T>::operator=(SortedList<T> x)
{
  List<T>::operator=(x);
  return *this;
}

template <typename T>
SortedList<T>::~SortedList()
{
  // base destructor gets called automatically
}

template <typename T>
// isEmpty method: checks if sorted list is empty using List implementation
bool SortedList<T>::isEmpty() const noexcept
{
  return List<T>::isEmpty();
}

template <typename T>
// getLength method: returns length of array using List implementation
std::size_t SortedList<T>::getLength() const noexcept
{
  return List<T>::getLength();
}

template <typename T>
// insert method: inserts item in array in correct sorted position
void SortedList<T>::insert(const T& item)
{
  size_t pos = 1; // variable used to iterate through positions
  while (pos <= getLength() && getEntry(pos) < item) { // increment position as long as the current position is less than the length of the array and the current entry is less than the item's value
    pos++;
  }
  List<T>::insert(pos,item); // insert item at sorted position
}

template <typename T>
// remove method: removes item in sorted list
void SortedList<T>::remove(const T& item)
{
  size_t pos = 1; // variable to iterate through positions
  for(size_t i=1;i<=getLength();i++) {
    if(getEntry(i)!=item) {
      pos++;
    }
    else { // added to ensure it breaks out when it reaches the item
      break;
    }
  }
  if (pos > getLength()) {
    throw std::invalid_argument("position outside of length of sorted list");
  }
  List<T>::remove(pos); // remove item at sorted position
}

template <typename T>
// removeAt method: removes item at specific position
void SortedList<T>::removeAt(std::size_t position)
{
  if(getLength() == 0 || position > getLength()) {
    throw std::out_of_range("input position is out of range (size = 0 or position > length)");
  }
  // check for empty list or invalid position, throw std::range_error
  List<T>::remove(position); // otherwise remove at position
}

template <typename T>
// clear method: clears items from the sorted list
void SortedList<T>::clear()
{
  List<T>::clear();
}

template <typename T>
// getEntry method: gets entry at specific position
T SortedList<T>::getEntry(std::size_t position) const
{
  return List<T>::getEntry(position);
}

template <typename T>
// getPosition method: gets position of a specific item
size_t SortedList<T>::getPosition(const T& item)
{
  // loop through the array to find where the item is in the position
  for(size_t i=1;i<=getLength();i++) {
    if(getEntry(i)==item) {
      return i;
    }
  }
  throw std::invalid_argument("item does not exist in the sorted list"); // throw exception if item is not in sorted list
}
