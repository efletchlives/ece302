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
  list1.insert(0,10);
  list1.insert(1,20);
  list1.insert(2,30);

  ArrayList<int> list2(list1);
  REQUIRE(list2.getEntry(0) == 10);
  REQUIRE(list2.getEntry(1) == 20);
  REQUIRE(list2.getEntry(2) == 30);
}

TEST_CASE("test copy assignment operator", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  list1.insert(0,10);
  list1.insert(1,20);
  list1.insert(2,30);

  ArrayList<int> list2 = list1;
  REQUIRE(list2.getEntry(0) == 10);
  REQUIRE(list2.getEntry(1) == 20);
  REQUIRE(list2.getEntry(2) == 30);
}

TEST_CASE("test swap method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  list1.insert(0,1);
  list1.insert(1,2);
  list1.insert(2,3);

  ArrayList<int> list2;
  list2.insert(0,3);
  list2.insert(1,2);
  list2.insert(2,1);

  list1.swap(list2);

  REQUIRE(list1.getEntry(0) == 3);
  REQUIRE(list1.getEntry(1) == 2);
  REQUIRE(list1.getEntry(2) == 1);

  REQUIRE(list2.getEntry(0) == 1);
  REQUIRE(list2.getEntry(1) == 2);
  REQUIRE(list2.getEntry(2) == 3);
}

TEST_CASE("test isEmpty method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  REQUIRE(list1.isEmpty());

  ArrayList<int> list2;
  list2.insert(0,1);
  REQUIRE_FALSE(list2.isEmpty());
}

TEST_CASE("test getLength method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  list1.insert(0,1);
  list1.insert(1,2);
  list1.insert(2,3);
  list1.insert(3,4);

  REQUIRE(list1.getLength() == 4);
}

TEST_CASE("test insert method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  for(int i=0; i<100; i++) {
    list1.insert(i,i*2);
    REQUIRE(list1.getEntry(i) == i*2);
  }
}

TEST_CASE("test remove method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  for(int i=0; i<100; i++) {
    list1.insert(i,i*5);
    REQUIRE(list1.getEntry(i) == i*5);
  }
  for(int i=99; i>0; i--) {
    list1.remove(i);
    REQUIRE(list1.getEntry(i-1) == (i*5-5));
  }
}

TEST_CASE("test clear method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  list1.insert(0,5);
  list1.insert(1,4);
  list1.insert(2,3);
  list1.insert(3,2);
  list1.insert(4,1);

  REQUIRE(list1.getEntry(0) == 5);
  REQUIRE(list1.getEntry(1) == 4);
  REQUIRE(list1.getEntry(2) == 3);
  REQUIRE(list1.getEntry(3) == 2);
  REQUIRE(list1.getEntry(4) == 1);

  list1.clear();
  REQUIRE(list1.isEmpty());
}

TEST_CASE("test getEntry method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
    for(int i=0; i<100; i++) {
      list1.insert(i,i*9);
      REQUIRE(list1.getEntry(i) == i*9);
    }
}

TEST_CASE("test setEntry method", "[ArrayList]")
{
  // integer array list
  ArrayList<int> list1;
  list1.insert(0,5);
  list1.insert(1,4);
  list1.insert(2,3);
  list1.insert(3,2);
  list1.insert(4,1);

  REQUIRE(list1.getEntry(0) == 5);
  REQUIRE(list1.getEntry(1) == 4);
  REQUIRE(list1.getEntry(2) == 3);
  REQUIRE(list1.getEntry(3) == 2);
  REQUIRE(list1.getEntry(4) == 1);

  list1.setEntry(0,10);
  list1.setEntry(1,8);
  list1.setEntry(2,6);
  list1.setEntry(3,4);
  list1.setEntry(4,2);

  REQUIRE(list1.getEntry(0) == 10);
  REQUIRE(list1.getEntry(1) == 8);
  REQUIRE(list1.getEntry(2) == 6);
  REQUIRE(list1.getEntry(3) == 4);
  REQUIRE(list1.getEntry(4) == 2);
}

