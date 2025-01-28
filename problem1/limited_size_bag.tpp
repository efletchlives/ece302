#include "limited_size_bag.hpp"


// i copied most of this from the dynamic bag

// default constructor
template <typename T>
LimitedSizeBag<T>::LimitedSizeBag()
{
  size = 0;
}

template <typename T>
// adds an item to the end of the bag
bool LimitedSizeBag<T>::add(const T &item)
{
  // if the current size is equal to the maximum size (meaning there is no more room in the data array?)
  if(size == maxsize){
    return false;
  }

  // add the new data to the end
  data[size++] =  item;
  return true; // item added successfully
}

template <typename T>
// removes an item from the bag
bool LimitedSizeBag<T>::remove(const T &item)
{
  // for loop to loop through all of the data in the bag
  for(int i=0;i<size;i++){
    if(data[i] == item){
      data[i] = data[size-1]; // replace the place where item was with the last item
      size--; // decrement size by 1 since you removed item
      return true; // item removed successfully
    }
  }
  return false; // item wasn't found
}

template <typename T>
// check if the bag is empty
bool LimitedSizeBag<T>::isEmpty() const
{
  if(size == 0){
    return true;
  }
  return false;
}

template <typename T>
// return the current size of the bag
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return size;
}

template <typename T>
// checks to see if the item is in the bag
bool LimitedSizeBag<T>::contains(const T &item) const
{
  // for loop to loop through all of the data in the bag
  for(int i=0;i<size;i++){
    if(data[i] == item){ // if item in bag is equal to item we are checking for
      return true; // item found
    }
  }
  return false; // item not found
}

template <typename T>
// clears the bag of all data
void LimitedSizeBag<T>::clear()
{
  size = 0; // since it is being reused, no need to deallocate
}

template <typename T>
// counts the number of instances of the item in the bag
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T &item) const
{
  // create count variable
  std::size_t frequency = 0;

  for (int i=0;i<size;i++){
    if(data[i] == item) { // if equals item
    frequency++; // increment frequency if so
    }
  }
  return frequency; // returns # of instances
};

template <typename T>
// equals operator (checks to see if 2 bags have the same size and items inside)
bool LimitedSizeBag<T>::operator==(const AbstractBag<T> &other) const
{
  // test that the sizes are the same
  if(getCurrentSize() != other.getCurrentSize()){
    return false;
  }

  // test the data array element by element and if they don't equal each other, return false
  for(int i=0;i<size;i++){
    if(getFrequencyOf(data[i]) != other.getFrequencyOf(data[i])){
      return false;
    }
  }

  return true;
}

// maxsize tpp part (since you declared it as a public member in the bag)
template <typename T>
const std::size_t LimitedSizeBag<T>::maxsize;