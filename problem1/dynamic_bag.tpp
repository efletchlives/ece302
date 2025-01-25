#include "dynamic_bag.hpp"

// default constructor
template <typename T>
DynamicBag<T>::DynamicBag()
{
  // initialize data, size, and max_size to x's
  data = new T[10];
  size = 0;
  max_size = 10;
}

// copy constructor
template <typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T> &x)
{
  // initialize data, size, and max_size to x's
  data = new T[x.max_size];
  size = x.size;
  max_size = x.max_size;

  for(int i=0;i<x.size;i++) {
    data[i] = x.data[i]; // copy data in bag cell by cell from the x bag
  }
}

// destructor
template <typename T>
DynamicBag<T>::~DynamicBag()
{
  delete[] data; // use delete to properly deallocate array memory
}

// copy assignment operator
template <typename T>
DynamicBag<T> &DynamicBag<T>::operator=(DynamicBag<T> x)
{
  swap(x); // uses copy swap idiom below
  return *this;
}

template <typename T>
// copy swap idiom (swap the current bag's private members with the x bag's private members)
void DynamicBag<T>::swap(DynamicBag<T> &x)
{
  // uses the std swap function to swap each private member of the current object with the x object
  std::swap(data,x.data);
  std::swap(size,x.size);
  std::swap(max_size,x.max_size);
}

template <typename T>
// adds an item to the end of the bag
bool DynamicBag<T>::add(const T &item)
{
  // if the current size is equal to the maximum size (meaning there is no more room in the data array)
  if(size == max_size){
    return false; // hi gavin, do you want us to expand the bag if there is no room or not?

    // if so, below is the code: 

    // max_size = 2*max_size; // double maximum size
    // T* new_data = new T[max_size]; // expand the array data to the new maximum size

    // // copy element by element from old array into new array
    // for(int i=0;i<size;i++){
    //   new_data[i] = data[i];
    // }

    // // properly deallocate the old array to avoid dangling pointers and memory leaks
    // delete[] data;
    // data = new_data;
  }

  // add the new data to the end
  data[size++] =  item;
  return true; // item added successfully
}

template <typename T>
// removes an item from the bag
bool DynamicBag<T>::remove(const T &item)
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
bool DynamicBag<T>::isEmpty() const
{
  // it is empty if the size is 0
  if (size == 0){
    return true;
  }
  return false;
}

template <typename T>
// return the current size of the bag
std::size_t DynamicBag<T>::getCurrentSize() const
{
  return size;
}

template <typename T>
// checks to see if the item is in the bag
bool DynamicBag<T>::contains(const T &item) const
{
  // for loop to loop through all of the data in the bag
  for(int i=0;i<size;i++){
    if(data[i] == item){
      return true;
    }
  }
  return false;
}

template <typename T>
// clears the bag of all data
void DynamicBag<T>::clear()
{
  size = 0; // no need to deallocate because we will be reusing the bag
}

template <typename T>
// counts the number of instances of the item in the bag
std::size_t DynamicBag<T>::getFrequencyOf(const T &item) const
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
bool DynamicBag<T>::operator==(const AbstractBag<T> &other) const
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