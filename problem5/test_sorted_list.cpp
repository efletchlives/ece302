#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "sorted_list.hpp"
#include "list.hpp"

/* Provided tests */
TEST_CASE("SortedList: Testing size", "[sorted list]") {
  SortedList<char> lst;

  REQUIRE(lst.isEmpty());
  REQUIRE(lst.getLength() == 0);

  lst.insert('b');
  REQUIRE(!lst.isEmpty());
  REQUIRE(lst.getLength() == 1);

  lst.insert('a');
  REQUIRE(lst.getLength() == 2);

  lst.removeAt(1);
  REQUIRE(lst.getLength() == 1);

  lst.removeAt(1);
  REQUIRE(lst.getLength() == 0);
  REQUIRE(lst.isEmpty());
}


TEST_CASE("SortedList: Testing insert", "[sorted list]") {
  SortedList<char> lst;

  char c = 'a';
  while (c <= 'z') {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 26);

  bool getEntryCheck = true;
  for (int i = 1; i <= 26; ++i) {
    if(lst.getEntry(i) != ('a' + (i-1))) {
      getEntryCheck = false;
      break;
    }
  }
  REQUIRE(getEntryCheck);
}


TEST_CASE("SortedList: Testing remove", "[sorted list]") {
  SortedList<char> lst;

  char c = 'a';
  int size = 10;
  while (c < 'a'+size) {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == size);

  lst.remove('c');
  REQUIRE(lst.getLength() == size-1);
  REQUIRE(lst.getEntry(3) == 'd');

  lst.remove('e');
  REQUIRE(lst.getLength() == size-2);
  REQUIRE(lst.getEntry(6) == 'h');

  lst.remove('a');
  REQUIRE(lst.getLength() == size-3);
  REQUIRE(lst.getEntry(1) == 'b');
}


TEST_CASE("SortedList: Testing getPosition", "[sorted list]") {
  SortedList<char> lst;

  lst.insert('a');
  lst.insert('d');
  lst.insert('e');
  lst.insert('c');
  lst.insert('b');

  REQUIRE(lst.getPosition('a') == 1);
  REQUIRE(lst.getPosition('b') == 2);
  REQUIRE(lst.getPosition('c') == 3);
  REQUIRE(lst.getPosition('d') == 4);
  REQUIRE(lst.getPosition('e') == 5);
}


TEST_CASE("Testing init from list", "[sorted list]") {
  List<char> unsorted;

  unsorted.insert(1,'a');
  unsorted.insert(2,'d');
  unsorted.insert(3,'e');
  unsorted.insert(4,'c');
  unsorted.insert(5,'b');

  SortedList<char> sorted(unsorted);

  REQUIRE(sorted.getPosition('a') == 1);
  REQUIRE(sorted.getPosition('b') == 2);
  REQUIRE(sorted.getPosition('c') == 3);
  REQUIRE(sorted.getPosition('d') == 4);
  REQUIRE(sorted.getPosition('e') == 5);
}

TEST_CASE("SortedList: Testing list exceptions", "[list]") {
  List<char> lst;

  REQUIRE_THROWS_AS(lst.remove(1), std::out_of_range);
  REQUIRE_THROWS_AS(lst.insert(2,'a'), std::out_of_range);
  REQUIRE_THROWS_AS(lst.getEntry(1), std::out_of_range);
  REQUIRE_THROWS_AS(lst.setEntry(1,'a'), std::out_of_range);

  lst.insert(1,'a');
  lst.insert(2,'b');

  REQUIRE_THROWS_AS(lst.remove(3), std::out_of_range);
  REQUIRE_THROWS_AS(lst.insert(4,'c'), std::out_of_range);
  REQUIRE_THROWS_AS(lst.getEntry(3), std::out_of_range);
  REQUIRE_THROWS_AS(lst.setEntry(3,'c'), std::out_of_range);

}

/* Your tests here */

TEST_CASE("default constructor","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;
  REQUIRE(a.getLength() == 0);
  // double sorted list
  SortedList<double> b;
  REQUIRE(b.getLength() == 0);
  // string sorted list
  SortedList<std::string> c;
  REQUIRE(c.getLength() == 0);
}

TEST_CASE("copy constructor (unsorted -> sorted)","[sortedlist]") {
  // integer sorted list
  List<int> a;
  a.insert(1,10);
  a.insert(2,0);
  a.insert(3,5);
  SortedList<int> b(a);
  REQUIRE(b.getLength() == 3);
  REQUIRE(b.getEntry(1) == 0);
  REQUIRE(b.getEntry(2) == 5);
  REQUIRE(b.getEntry(3) == 10);

  // double sorted list
  SortedList<double> c;
  
  // string sorted list
  SortedList<std::string> e;
}

TEST_CASE("copy constructor (sorted -> sorted)","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;

  // double sorted list
  SortedList<double> b;

  // string sorted list
  SortedList<std::string> c;
}

TEST_CASE("copy assignment operator","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;

  // double sorted list
  SortedList<double> b;

  // string sorted list
  SortedList<std::string> c;
}

TEST_CASE("isEmpty method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;

  // double sorted list
  SortedList<double> b;

  // string sorted list
  SortedList<std::string> c;
}

TEST_CASE("getLength method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;

  // double sorted list
  SortedList<double> b;

  // string sorted list
  SortedList<std::string> c;
}

TEST_CASE("insert method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;

  // double sorted list
  SortedList<double> b;

  // string sorted list
  SortedList<std::string> c;
}

TEST_CASE("remove method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;

  // double sorted list
  SortedList<double> b;

  // string sorted list
  SortedList<std::string> c;
}

TEST_CASE("removeAt method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;

  // double sorted list
  SortedList<double> b;

  // string sorted list
  SortedList<std::string> c;
}

TEST_CASE("clear method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;

  // double sorted list
  SortedList<double> b;

  // string sorted list
  SortedList<std::string> c;
}

TEST_CASE("getEntry method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;

  // double sorted list
  SortedList<double> b;

  // string sorted list
  SortedList<std::string> c;
}

TEST_CASE("getPosition method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;

  // double sorted list
  SortedList<double> b;

  // string sorted list
  SortedList<std::string> c;
}