#include "queue.hpp"

template <typename T, typename L>
void Queue<T, L>::enqueue(const T &item)
{
  // insert item at 1st position
  internal_list.insert(1,item);
}

template <typename T, typename L>
void Queue<T, L>::dequeue()
{
  // queue's front is the last item in the sorted list
  internal_list.remove(internal_list.getLength());
}

template <typename T, typename L>
T Queue<T, L>::peekFront()
{
  // queue's front is the last item in the sorted list
  return internal_list.getEntry(internal_list.getLength());
}

template <typename T, typename L>
bool Queue<T, L>::isEmpty() const
{
  return internal_list.isEmpty();
}