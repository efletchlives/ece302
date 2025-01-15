#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "add.hpp"

// force template expansion
template class Add<int>;

TEST_CASE("Test add", "[Add]"){

  Add<int> a;
  REQUIRE(a.call(1,2)==3);
}

TEST_CASE("test long","[Add]"){
  Add<long> b;
  REQUIRE(b.call(1000000000000,999695949933) == 1999695949933);
}

TEST_CASE("test double","[Add]"){
  Add<double> c;
  double THRESHOLD = 1e-9;
  REQUIRE(c.call((3-sqrt(2)),(4+sqrt(2)))-((3-sqrt(2))+(4+sqrt(2))) <= THRESHOLD);
}

TEST_CASE("test char","[Add]"){
  Add<char> d;
  // adding the char '2' and char '3' does not equal char '5'. it instead is equal to the char 'e'
  REQUIRE(d.call('2','3') == 'e');
}

TEST_CASE("test std::string","[Add]"){
  Add<std::string> e;
  // adding the string "2" and the string "3" does not equal "5". Instead it equals "23", showing that when strings are adding together, the second argument just appends onto the first argument
  REQUIRE(e.call("2","3") == "23");
}

TEST_CASE("test bool","[Add]"){
  Add<bool> f;
  // adding 2 bool 1's together does not equal 2. Just like in logic gates, when you add two 1s or trues together, it just equals 1 or true, not 2.
  REQUIRE(f.call(true,true) == 1); // you can also write true on the right side of the argument
}

/* 
Answer 1: the destructor in the Add class remains untested while both the default constructor and call function are tested thoroughly.
Answer 2: Yes, the std::string uses operator overloading since it uses the overloaded "+" operator to append the strings together. In the std::string test case, "2" + "3" = "23".
*/