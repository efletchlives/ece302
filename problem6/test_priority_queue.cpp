#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "list.hpp"
#include "sorted_list.hpp"
#include "priority_queue.hpp"

using namespace std;

typedef SortedList<int, List<int>> SortedListType;
typedef PriorityQueue<int, SortedListType> PriorityQueueType;

/* Provided test cases */
TEST_CASE("Priority: Testing Sorted List", "[sorted list]")
{
  SortedList<int, List<int>> sort;

  REQUIRE(sort.isEmpty());
  REQUIRE(sort.getLength() == 0);

  sort.insert(1);
  REQUIRE_FALSE(sort.isEmpty());
  REQUIRE(sort.getLength() == 1);
  sort.insert(2);
  REQUIRE(sort.getLength() == 2);
  sort.insert(8);
  REQUIRE(sort.getLength() == 3);
  sort.insert(6);
  REQUIRE(sort.getLength() == 4);
  sort.insert(9);
  REQUIRE(sort.getLength() == 5);
  sort.insert(0);
  REQUIRE(sort.getLength() == 6);

  REQUIRE(sort.getEntry(1) == 0);
  REQUIRE(sort.getPosition(0) == 1);
  REQUIRE(sort.getEntry(2) == 1);
  REQUIRE(sort.getPosition(1) == 2);
  REQUIRE(sort.getEntry(3) == 2);
  REQUIRE(sort.getPosition(2) == 3);
  REQUIRE(sort.getEntry(4) == 6);
  REQUIRE(sort.getPosition(6) == 4);
  REQUIRE(sort.getEntry(5) == 8);
  REQUIRE(sort.getPosition(8) == 5);
  REQUIRE(sort.getEntry(6) == 9);
  REQUIRE(sort.getPosition(9) == 6);

  sort.remove(0);
  REQUIRE(sort.getEntry(1) == 1);
  REQUIRE(sort.getLength() == 5);

  sort.remove(1);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getLength() == 4);

  sort.remove(9);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getLength() == 3);

  sort.removeAt(2);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getLength() == 2);

  sort.removeAt(1);
  REQUIRE(sort.getEntry(1) == 8);
  REQUIRE(sort.getLength() == 1);

  sort.removeAt(1);
  REQUIRE(sort.getLength() == 0);
  REQUIRE(sort.isEmpty());
}

TEST_CASE("Priority: Testing Priority Queue Add/isEmpty/peek/remove", "[priority queue]")
{
  PriorityQueueType pq;

  REQUIRE(pq.isEmpty());

  pq.add(3);
  REQUIRE_FALSE(pq.isEmpty());

  pq.add(1);
  pq.add(5);
  pq.add(2);
  REQUIRE(pq.peek() == 5);

  pq.remove();
  REQUIRE(pq.peek() == 3);

  pq.remove();
  REQUIRE(pq.peek() == 2);
}


/*////////////////// my test cases \\\\\\\\\\\\\\\\\\\\\\\\\*/



TEST_CASE("double priority queue", "[priority queue]")
{
  PriorityQueue<double, SortedList<double, List<double>>> pq;

  REQUIRE(pq.isEmpty());

  pq.add(3.5);
  REQUIRE_FALSE(pq.isEmpty());

  pq.add(1.1);
  pq.add(5.8);
  pq.add(2.7);

  REQUIRE(pq.peek() == 5.8);

  pq.remove();
  REQUIRE(pq.peek() == 3.5);

  pq.remove();
  REQUIRE(pq.peek() == 2.7);
}

TEST_CASE("string priority queue", "[priority queue]")
{
  PriorityQueue<std::string, SortedList<std::string, List<std::string>>> pq;

  REQUIRE(pq.isEmpty());

  pq.add("orange");
  REQUIRE_FALSE(pq.isEmpty());

  pq.add("apple");
  pq.add("banana");
  pq.add("pear");

  REQUIRE(pq.peek() == "pear");

  pq.remove();
  REQUIRE(pq.peek() == "orange");

  pq.remove();
  REQUIRE(pq.peek() == "banana");
}

/* FINISH THIS!!! */
// date class that you mentioned
// template <typename T>
// class gavin {
// public:
//   // grades in classes gavin has taught
//   T c1 = "ece201", c2 = "ece301", c3 = "ece302"; // as far as i know
//   gavin(T a, T b, T c) : c1(a), c2(b), c3(c){}

//   // comparison operators
//   bool operator>(const gavin& other) const {
//     if (c1 != other.c1) return c1 < other.c1;
//     if (c2 != other.c2) return c2 < other.c2;
//     return c3 < other.c3;
//   }
//   bool operator<(const gavin& other) const {
//     if (c1 != other.c1) return c1 > other.c1;
//     if (c2 != other.c2) return c2 > other.c2;
//     return c3 > other.c3;
//   }
//   bool operator==(const gavin& other) const {
//     return c1 == other.c1 && c2 == other.c2 && c3 == other.c3;
//   }
// };

// TEST_CASE("priority with gavin class", "[priority queue]")
// {
//   PriorityQueue<gavin<std::string>, SortedList<gavin<std::string>, List<gavin<std::string>>>> pq;

//   REQUIRE(pq.isEmpty());

//   pq.add(gavin<string>("A","B","C"));
//   REQUIRE_FALSE(pq.isEmpty());

//   pq.add(gavin<string>("B","C","A"));
//   pq.add(gavin<string>("A","B","B"));
//   pq.add(gavin<string>("A","A","B"));

//   REQUIRE(pq.peek() == gavin<string>("A","A","B"));

//   pq.remove();
//   REQUIRE(pq.peek() == gavin<string>("A","B","B"));

//   pq.remove();
//   REQUIRE(pq.peek() == gavin<string>("A","B","C"));
// }
