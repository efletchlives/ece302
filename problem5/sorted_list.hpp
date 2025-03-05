
#ifndef _SORTED_LIST_HPP_
#define _SORTED_LIST_HPP_

#include "abstract_sorted_list.hpp"
#include "list.hpp"

template <typename T>
class SortedList: public AbstractSortedList<T>, private List<T>
{
public:

  SortedList();

  // constructor from list (should sort the input list)
  SortedList(const List<T>& unsorted_list); // you should use const here or else the test case you used doesn't work properly

  SortedList(const SortedList & x);

  SortedList& operator=(SortedList x);

  ~SortedList();

  bool isEmpty() const noexcept;

  std::size_t getLength() const noexcept;

  void insert(const T& item);

  void remove(const T& item);

  void removeAt(std::size_t position);

  void clear();

  T getEntry(std::size_t position) const;

  size_t getPosition(const T& item);

private:

  // TODO

};

#include "sorted_list.tpp"

#endif 
