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
  List<double> c;
  c.insert(1,1.203);
  c.insert(2,0.405);
  c.insert(3,2.05);
  SortedList<double> d(c);
  REQUIRE(d.getLength() == 3);
  REQUIRE(d.getEntry(1) == 0.405);
  REQUIRE(d.getEntry(2) == 1.203);
  REQUIRE(d.getEntry(3) == 2.05);

  // string sorted list
  List<std::string> e;
  e.insert(1,"hey");
  e.insert(2,"gavin");
  e.insert(3,"again");
  SortedList<std::string> f(e);
  REQUIRE(f.getLength() == 3);
  REQUIRE(f.getEntry(1) == "again");
  REQUIRE(f.getEntry(2) == "gavin");
  REQUIRE(f.getEntry(3) == "hey");

}


TEST_CASE("copy constructor (sorted -> sorted)","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;
  a.insert(10);
  a.insert(0);
  a.insert(5);
  SortedList<int> b(a);
  REQUIRE(b.getLength() == 3);
  REQUIRE(b.getEntry(1) == 0);
  REQUIRE(b.getEntry(2) == 5);
  REQUIRE(b.getEntry(3) == 10);

  // double sorted list
  SortedList<double> c;
  c.insert(1.203);
  c.insert(0.405);
  c.insert(2.05);
  SortedList<double> d(c);
  REQUIRE(d.getLength() == 3);
  REQUIRE(d.getEntry(1) == 0.405);
  REQUIRE(d.getEntry(2) == 1.203);
  REQUIRE(d.getEntry(3) == 2.05);

  // string sorted list
  SortedList<std::string> e;
  e.insert("hey");
  e.insert("gavin");
  e.insert("again");
  SortedList<std::string> f(e);
  REQUIRE(f.getLength() == 3);
  REQUIRE(f.getEntry(1) == "again");
  REQUIRE(f.getEntry(2) == "gavin");
  REQUIRE(f.getEntry(3) == "hey");

}


TEST_CASE("copy assignment operator","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;
  a.insert(10);
  a.insert(0);
  a.insert(5);

  SortedList<int> b;
  b.insert(20);
  b.insert(10);
  b.insert(0);
  REQUIRE(b.getEntry(1) == 0);
  REQUIRE(b.getEntry(2) == 10);
  REQUIRE(b.getEntry(3) == 20);

  b = a;

  REQUIRE(a.getEntry(1) == 0);
  REQUIRE(a.getEntry(2) == 5);
  REQUIRE(a.getEntry(3) == 10);

  REQUIRE(b.getEntry(1) == 0);
  REQUIRE(b.getEntry(2) == 5);
  REQUIRE(b.getEntry(3) == 10);

  // double sorted list
  SortedList<double> c;
  c.insert(1.203);
  c.insert(0.405);
  c.insert(2.05);
  SortedList<double> d = c;

  REQUIRE(c.getEntry(1) == 0.405);
  REQUIRE(c.getEntry(2) == 1.203);
  REQUIRE(c.getEntry(3) == 2.05);

  REQUIRE(d.getEntry(1) == 0.405);
  REQUIRE(d.getEntry(2) == 1.203);
  REQUIRE(d.getEntry(3) == 2.05);

  // string sorted list
  SortedList<std::string> e;
  e.insert("hey");
  e.insert("gavin");
  e.insert("again");

  SortedList<std::string> f = e;
  REQUIRE(f.getEntry(1) == "again");
  REQUIRE(f.getEntry(2) == "gavin");
  REQUIRE(f.getEntry(3) == "hey");

}


TEST_CASE("isEmpty method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;
  a.insert(3);
  a.insert(2);
  a.insert(1);
  REQUIRE(a.getEntry(1) == 1);
  REQUIRE(a.getEntry(2) == 2);
  REQUIRE(a.getEntry(3) == 3);

  REQUIRE_FALSE(a.isEmpty());

  a.clear();
  REQUIRE(a.isEmpty());
  REQUIRE_THROWS_AS(a.getEntry(1),std::out_of_range);
  REQUIRE_THROWS_AS(a.getEntry(2),std::out_of_range);
  REQUIRE_THROWS_AS(a.getEntry(3),std::out_of_range);

  // double sorted list
  SortedList<double> b;
  b.insert(20);
  b.insert(10);
  b.insert(0);
  REQUIRE(b.getEntry(1) == 0);
  REQUIRE(b.getEntry(2) == 10);
  REQUIRE(b.getEntry(3) == 20);

  REQUIRE_FALSE(b.isEmpty());

  b.clear();
  REQUIRE(b.isEmpty());
  REQUIRE_THROWS_AS(b.getEntry(1),std::out_of_range);
  REQUIRE_THROWS_AS(b.getEntry(2),std::out_of_range);
  REQUIRE_THROWS_AS(b.getEntry(3),std::out_of_range);

  // string sorted list
  SortedList<std::string> c;
  c.insert("hey");
  c.insert("gavin");
  c.insert("again");
  REQUIRE(c.getEntry(1) == "again");
  REQUIRE(c.getEntry(2) == "gavin");
  REQUIRE(c.getEntry(3) == "hey");

  REQUIRE_FALSE(c.isEmpty());

  c.clear();
  REQUIRE_THROWS_AS(c.getEntry(1),std::out_of_range);
  REQUIRE_THROWS_AS(c.getEntry(2),std::out_of_range);
  REQUIRE_THROWS_AS(c.getEntry(3),std::out_of_range);

}


TEST_CASE("getLength method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;
  a.insert(3);
  a.insert(2);
  a.insert(1);
  REQUIRE(a.getLength() == 3);

  a.clear();
  REQUIRE(a.getLength() == 0);

  // double sorted list
  SortedList<double> b;
  b.insert(20);
  b.insert(10);
  b.insert(0);
  REQUIRE(b.getLength() == 3);

  b.clear();
  REQUIRE(b.getLength() == 0);

  // string sorted list
  SortedList<std::string> c;
  c.insert("hey");
  c.insert("gavin");
  c.insert("again");
  REQUIRE(c.getLength() == 3);

  c.clear();
  REQUIRE(c.getLength() == 0);

}


TEST_CASE("insert method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;
  for(int i=1000;i>0;i--) {
    a.insert(i);
  }
  REQUIRE(a.getLength() == 1000);

  for(int i=1;i<=1000;i++) {
    REQUIRE(a.getEntry(i) == i);
  }

  // double sorted list
  SortedList<double> b;
  for(int i=10;i>0;i--) {
    b.insert(i);
  }
  REQUIRE(b.getLength() == 10);

  for(int i=1;i<=10;i++) {
    REQUIRE(b.getEntry(i) == i);
  }
  // string sorted list
  SortedList<std::string> c;
  std::string entry = "0";
  for(int i=1;i<=1000;i++) {
    c.insert(entry);
    entry = entry + "1";
  }
  REQUIRE(c.getLength() == 1000);

  std::string entry2 = "0";
  for(int i=1;i<=1000;i++) {
    REQUIRE(c.getEntry(i) == entry2);
    entry2 = entry2 + "1";
  }

}


TEST_CASE("remove method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;
  for(int i=1000;i>0;i--) {
    a.insert(i);
  }
  REQUIRE(a.getLength() == 1000);

  for(int i=1;i<=1000;i++) {
    REQUIRE(a.getEntry(i) == i);
  }

  for(int i=1;i<=1000;i++) {
    a.remove(i);
  }
  REQUIRE(a.getLength() == 0);

  for(int i=1;i<=1000;i++) {
    REQUIRE_THROWS_AS(a.getEntry(i),std::out_of_range);
  }

  // double sorted list
  SortedList<double> b;
  for(int i=10;i>0;i--) {
    b.insert(i);
  }
  REQUIRE(b.getLength() == 10);

  for(int i=1;i<=10;i++) {
    REQUIRE(b.getEntry(i) == i);
  }

  for(int i=1;i<=10;i++) {
    b.remove(i);
  }
  REQUIRE(b.getLength() == 0);

  for(int i=1;i<=10;i++) {
    REQUIRE_THROWS_AS(b.getEntry(i),std::out_of_range);
  }

  // string sorted list
  SortedList<std::string> c;
  std::string entry = "0";
  for(int i=1;i<=1000;i++) {
    c.insert(entry);
    entry = entry + "1";
  }
  REQUIRE(c.getLength() == 1000);

  std::string entry2 = "0";
  for(int i=1;i<=1000;i++) {
    REQUIRE(c.getEntry(i) == entry2);
    entry2 = entry2 + "1";
  }

  std::string entry3 = "0";
  for(int i=1;i<=1000;i++) {
    c.remove(entry3);
    entry3 = entry3 + "1";
  }
  REQUIRE(c.getLength() == 0);

  for(int i=1;i<=1000;i++) {
    REQUIRE_THROWS_AS(c.getEntry(i),std::out_of_range);
  }
}


TEST_CASE("removeAt method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;
  for(int i=1000;i>0;i--) {
    a.insert(i);
  }
  REQUIRE(a.getLength() == 1000);

  for(int i=1;i<=1000;i++) {
    REQUIRE(a.getEntry(i) == i);
  }

  for(int i=1000;i>=1;i--) {
    a.removeAt(i);
  }
  REQUIRE(a.getLength() == 0);

  for(int i=1;i<=1000;i++) {
    REQUIRE_THROWS_AS(a.getEntry(i),std::out_of_range);
  }

  // double sorted list
  SortedList<double> b;
  for(int i=10;i>0;i--) {
    b.insert(i);
  }
  REQUIRE(b.getLength() == 10);

  for(int i=1;i<=10;i++) {
    REQUIRE(b.getEntry(i) == i);
  }

  for(int i=10;i>=1;i--) {
    b.removeAt(i);
  }
  REQUIRE(b.getLength() == 0);

  for(int i=1;i<=10;i++) {
    REQUIRE_THROWS_AS(b.getEntry(i),std::out_of_range);
  }

  // string sorted list
  SortedList<std::string> c;
  std::string entry = "0";
  for(int i=1;i<=1000;i++) {
    c.insert(entry);
    entry = entry + "1";
  }
  REQUIRE(c.getLength() == 1000);

  std::string entry2 = "0";
  for(int i=1;i<=1000;i++) {
    REQUIRE(c.getEntry(i) == entry2);
    entry2 = entry2 + "1";
  }

  for(int i=1000;i>=1;i--) {
    c.removeAt(i);
  }
  REQUIRE(c.getLength() == 0);

  for(int i=1;i<=1000;i++) {
    REQUIRE_THROWS_AS(c.getEntry(i),std::out_of_range);
  }
}


TEST_CASE("clear method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;
  a.insert(3);
  a.insert(2);
  a.insert(1);
  REQUIRE(a.getEntry(1) == 1);
  REQUIRE(a.getEntry(2) == 2);
  REQUIRE(a.getEntry(3) == 3);

  a.clear();
  REQUIRE_THROWS_AS(a.getEntry(1),std::out_of_range);
  REQUIRE_THROWS_AS(a.getEntry(2),std::out_of_range);
  REQUIRE_THROWS_AS(a.getEntry(3),std::out_of_range);

  // double sorted list
  SortedList<double> b;
  b.insert(20);
  b.insert(10);
  b.insert(0);
  REQUIRE(b.getEntry(1) == 0);
  REQUIRE(b.getEntry(2) == 10);
  REQUIRE(b.getEntry(3) == 20);

  b.clear();
  REQUIRE_THROWS_AS(b.getEntry(1),std::out_of_range);
  REQUIRE_THROWS_AS(b.getEntry(2),std::out_of_range);
  REQUIRE_THROWS_AS(b.getEntry(3),std::out_of_range);

  // string sorted list
  SortedList<std::string> c;
  c.insert("hey");
  c.insert("gavin");
  c.insert("again");
  REQUIRE(c.getEntry(1) == "again");
  REQUIRE(c.getEntry(2) == "gavin");
  REQUIRE(c.getEntry(3) == "hey");

  c.clear();
  REQUIRE_THROWS_AS(c.getEntry(1),std::out_of_range);
  REQUIRE_THROWS_AS(c.getEntry(2),std::out_of_range);
  REQUIRE_THROWS_AS(c.getEntry(3),std::out_of_range);
}


TEST_CASE("getEntry method","[sortedlist]") {
  // integer sorted list
  List<int> a;
  a.insert(1,10);
  a.insert(2,0);
  a.insert(3,5);
  SortedList<int> b(a);
  REQUIRE(b.getEntry(1) == 0);
  REQUIRE(b.getEntry(2) == 5);
  REQUIRE(b.getEntry(3) == 10);

  // double sorted list
  List<double> c;
  c.insert(1,1.203);
  c.insert(2,0.405);
  c.insert(3,2.05);
  SortedList<double> d(c);
  REQUIRE(d.getEntry(1) == 0.405);
  REQUIRE(d.getEntry(2) == 1.203);
  REQUIRE(d.getEntry(3) == 2.05);

  // string sorted list
  List<std::string> e;
  e.insert(1,"hey");
  e.insert(2,"gavin");
  e.insert(3,"again");
  SortedList<std::string> f(e);
  REQUIRE(f.getEntry(1) == "again");
  REQUIRE(f.getEntry(2) == "gavin");
  REQUIRE(f.getEntry(3) == "hey");
}


TEST_CASE("getPosition method","[sortedlist]") {
  // integer sorted list
  SortedList<int> a;
  a.insert(3);
  a.insert(2);
  a.insert(1);

  REQUIRE(a.getPosition(1) == 1);
  REQUIRE(a.getPosition(2) == 2);
  REQUIRE(a.getPosition(3) == 3);

  // double sorted list
  SortedList<double> b;
  b.insert(0.3);
  b.insert(0.2);
  b.insert(0.1);

  REQUIRE(b.getPosition(0.1) == 1);
  REQUIRE(b.getPosition(0.2) == 2);
  REQUIRE(b.getPosition(0.3) == 3);

  // string sorted list
  SortedList<std::string> c;
  c.insert("a");
  c.insert("b");
  c.insert("c");

  REQUIRE(c.getPosition("a") == 1);
  REQUIRE(c.getPosition("b") == 2);
  REQUIRE(c.getPosition("c") == 3);

}