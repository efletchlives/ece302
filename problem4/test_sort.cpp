#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "list.hpp"
#include "sort.hpp"

/* Provided test cases */
TEST_CASE("Sort: Test move entry", "[sorting]") {
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  // move forward
  lst.moveEntry(1, 3);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 100);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 11);

  // move backward
  lst.moveEntry(5, 1);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(1) == 11);
  REQUIRE(lst.getEntry(2) == 4);
  REQUIRE(lst.getEntry(3) == 10);
  REQUIRE(lst.getEntry(4) == 100);
  REQUIRE(lst.getEntry(5) == 25);
}


TEST_CASE("Sort: Integer sorting", "[sorting]"){

  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  quick_sort(lst, 1, lst.getLength());

  // check sorted list
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 11);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 100);

}



TEST_CASE("quick sort algorithm","[sorting]") {
  // integer case
  List<int> list1;
  list1.insert(1,19);
  list1.insert(2,4);
  list1.insert(3,45);
  list1.insert(4,1);
  list1.insert(5,109);
  list1.insert(6,98);
  list1.insert(7,18);
  list1.insert(8,19);
  list1.insert(9,21);
  list1.insert(10,10);

  quick_sort(list1,1,list1.getLength());

  REQUIRE(list1.getEntry(1) == 1);
  REQUIRE(list1.getEntry(2) == 4);
  REQUIRE(list1.getEntry(3) == 10);
  REQUIRE(list1.getEntry(4) == 18);
  REQUIRE(list1.getEntry(5) == 19);
  REQUIRE(list1.getEntry(6) == 19);
  REQUIRE(list1.getEntry(7) == 21);
  REQUIRE(list1.getEntry(8) == 45);
  REQUIRE(list1.getEntry(9) == 98);
  REQUIRE(list1.getEntry(10) == 109);

  // double case
  List<double> list2;
  list2.insert(1,19.97);
  list2.insert(2,4.56);
  list2.insert(3,45.66);
  list2.insert(4,1.9);
  list2.insert(5,109.0);
  list2.insert(6,98.19);
  list2.insert(7,18.87);
  list2.insert(8,19.23);
  list2.insert(9,21.21);
  list2.insert(10,10.10);

  quick_sort(list2,1,list2.getLength());

  REQUIRE(list2.getEntry(1) == 1.9);
  REQUIRE(list2.getEntry(2) == 4.56);
  REQUIRE(list2.getEntry(3) == 10.10);
  REQUIRE(list2.getEntry(4) == 18.87);
  REQUIRE(list2.getEntry(5) == 19.23);
  REQUIRE(list2.getEntry(6) == 19.97);
  REQUIRE(list2.getEntry(7) == 21.21);
  REQUIRE(list2.getEntry(8) == 45.66);
  REQUIRE(list2.getEntry(9) == 98.19);
  REQUIRE(list2.getEntry(10) == 109.0);

  // string case
  List<std::string> list3;
  list3.insert(1,"hi");
  list3.insert(2,"gavin");
  list3.insert(3,"i");
  list3.insert(4,"hope");
  list3.insert(5,"you");
  list3.insert(6,"are");
  list3.insert(7,"doing");
  list3.insert(8,"well");
  list3.insert(9,"goodbye");
  list3.insert(10,"gavin");

  quick_sort(list3,1,list3.getLength());

  REQUIRE(list3.getEntry(1) == "are");
  REQUIRE(list3.getEntry(2) == "doing");
  REQUIRE(list3.getEntry(3) == "gavin");
  REQUIRE(list3.getEntry(4) == "gavin");
  REQUIRE(list3.getEntry(5) == "goodbye");
  REQUIRE(list3.getEntry(6) == "hi");
  REQUIRE(list3.getEntry(7) == "hope");
  REQUIRE(list3.getEntry(8) == "i");
  REQUIRE(list3.getEntry(9) == "well");
  REQUIRE(list3.getEntry(10) == "you");
}
