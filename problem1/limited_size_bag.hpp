#ifndef LIMITED_SIZE_BAG_HPP
#define LIMITED_SIZE_BAG_HPP

#include "abstract_bag.hpp"

// static memory not dynamic 

template <typename T>
class LimitedSizeBag : public AbstractBag<T>
{
public:
  // default constructor
  LimitedSizeBag();

  // add an item to the bag
  bool add(const T &item);

  // remove an item
  bool remove(const T &item);

  // check is the bag is empty
  bool isEmpty() const;

  // get number of items in the bag
  std::size_t getCurrentSize() const;

  // clear the bag contents
  void clear();

  // count how many time item occurs in bag
  std::size_t getFrequencyOf(const T &item) const;

  // check if item is in the bag
  bool contains(const T &item) const;

  // check if two bags are equal
  bool operator==(const AbstractBag<T> &other) const;

  // static variable to store the limited size
  static const std::size_t maxsize = 100;

private:
  T data[maxsize]; // data array of items (limited size bag)
  std::size_t size; // current # of items in bag
};

#include "limited_size_bag.tpp"

#endif
