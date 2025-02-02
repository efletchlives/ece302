#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

// force class expansion
template class ArrayList<int>;

/* my test cases below */

TEST_CASE("test default constructor", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  REQUIRE(list1.isEmpty());
  REQUIRE(list1.getLength() == 0);
}

TEST_CASE("test copy constructor", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  list1.insert(1,10);
  list1.insert(2,20);
  list1.insert(3,30);

  ArrayList<int> list2(list1);
  REQUIRE(list2.getEntry(1) == 10);
  REQUIRE(list2.getEntry(2) == 20);
  REQUIRE(list2.getEntry(3) == 30);
}

TEST_CASE("test copy assignment operator", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  list1.insert(1,10);
  list1.insert(2,20);
  list1.insert(3,30);

  ArrayList<int> list2 = list1;
  REQUIRE(list2.getEntry(1) == 10);
  REQUIRE(list2.getEntry(2) == 20);
  REQUIRE(list2.getEntry(3) == 30);
}

TEST_CASE("test swap method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  list1.insert(1,1);
  list1.insert(2,2);
  list1.insert(3,3);

  ArrayList<int> list2;
  list2.insert(1,3);
  list2.insert(2,2);
  list2.insert(3,1);

  list1.swap(list2);

  REQUIRE(list1.getEntry(1) == 3);
  REQUIRE(list1.getEntry(2) == 2);
  REQUIRE(list1.getEntry(3) == 1);

  REQUIRE(list2.getEntry(1) == 1);
  REQUIRE(list2.getEntry(2) == 2);
  REQUIRE(list2.getEntry(3) == 3);
}

TEST_CASE("test isEmpty method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  REQUIRE(list1.isEmpty());

  ArrayList<int> list2;
  list2.insert(1,1);
  REQUIRE_FALSE(list2.isEmpty());
}

TEST_CASE("test getLength method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  list1.insert(1,1);
  list1.insert(2,2);
  list1.insert(3,3);
  list1.insert(4,4);

  REQUIRE(list1.getLength() == 4);
}

TEST_CASE("test insert method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  for(int i=1; i<=100; i++) {
    list1.insert(i,i*2);
    REQUIRE(list1.getEntry(i) == i*2);
  }
}

TEST_CASE("test remove method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  for(int i=1; i<=100; i++) {
    list1.insert(i,i*5);
    REQUIRE(list1.getEntry(i) == i*5);
  }
  for(int i=100; i>1; i--) {
    list1.remove(i);
    REQUIRE(list1.getEntry(i-1) == (i*5-5));
  }
}

TEST_CASE("test clear method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  list1.insert(1,5);
  list1.insert(2,4);
  list1.insert(3,3);
  list1.insert(4,2);
  list1.insert(5,1);

  REQUIRE(list1.getEntry(1) == 5);
  REQUIRE(list1.getEntry(2) == 4);
  REQUIRE(list1.getEntry(3) == 3);
  REQUIRE(list1.getEntry(4) == 2);
  REQUIRE(list1.getEntry(5) == 1);

  list1.clear();
  REQUIRE(list1.isEmpty());
}

TEST_CASE("test getEntry method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
    for(int i=1; i<=100; i++) {
      list1.insert(i,i*9);
      REQUIRE(list1.getEntry(i) == i*9);
    }
}

TEST_CASE("test setEntry method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  list1.insert(1,5);
  list1.insert(2,4);
  list1.insert(3,3);
  list1.insert(4,2);
  list1.insert(5,1);

  REQUIRE(list1.getEntry(1) == 5);
  REQUIRE(list1.getEntry(2) == 4);
  REQUIRE(list1.getEntry(3) == 3);
  REQUIRE(list1.getEntry(4) == 2);
  REQUIRE(list1.getEntry(5) == 1);

  list1.setEntry(1,10);
  list1.setEntry(2,8);
  list1.setEntry(3,6);
  list1.setEntry(4,4);
  list1.setEntry(5,2);

  REQUIRE(list1.getEntry(1) == 10);
  REQUIRE(list1.getEntry(2) == 8);
  REQUIRE(list1.getEntry(3) == 6);
  REQUIRE(list1.getEntry(4) == 4);
  REQUIRE(list1.getEntry(5) == 2);
}

