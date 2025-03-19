#include "sorted_list.hpp"

template <typename T, typename L>
SortedList<T, L>::SortedList()
{
  // nothing to do, plist gets created on the stack
}

template <typename T, typename L>
SortedList<T, L>::SortedList(const SortedList<T, L> &x)
{
  plist = x.plist; // use plist copy assignment
}

template <typename T, typename L>
SortedList<T, L> &SortedList<T, L>::operator=(SortedList<T, L> x)
{
  plist = x.plist; // use plist copy assignment
  return *this;
}

template <typename T, typename L>
SortedList<T, L>::~SortedList()
{
  // plist destructor gets called automatically
}

template <typename T, typename L>
bool SortedList<T, L>::isEmpty() const noexcept
{
  return plist.isEmpty();
}

template <typename T, typename L>
std::size_t SortedList<T, L>::getLength() const noexcept
{
  return plist.getLength();
}

template <typename T, typename L>
// insert method: inserts item in array in correct sorted position
void SortedList<T, L>::insert(const T &item)
{
  size_t pos = 1; // variable used to iterate through positions
  while (pos <= getLength() && getEntry(pos) < item) { // increment position as long as the current position is less than the length of the array and the current entry is less than the item's value
    pos++;
  }
  plist.insert(pos,item); // insert item at sorted position
}

template <typename T, typename L>
// remove method: removes item in sorted list
void SortedList<T, L>::remove(const T &item)
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
  plist.remove(pos); // remove item at sorted position
}

template <typename T, typename L>
void SortedList<T, L>::removeAt(std::size_t position)
{
  plist.remove(position);
}

template <typename T, typename L>
void SortedList<T, L>::clear()
{
  plist.clear();
}

template <typename T, typename L>
T SortedList<T, L>::getEntry(std::size_t position) const
{
  return plist.getEntry(position);
}

template <typename T, typename L>
std::size_t SortedList<T, L>::getPosition(const T &newValue)
{
  // loop through the array to find where the item is in the position
  for(size_t i=1;i<=getLength();i++) {
    if(getEntry(i)==newValue) {
      return i;
    }
  }
  throw std::invalid_argument("item does not exist in the sorted list"); // throw exception if item is not in sorted list
}