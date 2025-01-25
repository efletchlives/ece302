#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "dynamic_bag.hpp"

// force template expansion for ints
template class DynamicBag<int>;

TEST_CASE("Calling all public members", "[DynamicBag]")
{
  DynamicBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}

TEST_CASE("test default constructor","[DynamicBag]") {
  // integer bag
  DynamicBag<int> a;
  REQUIRE(a.getCurrentSize() == 0);
  REQUIRE(a.isEmpty()); // since default, data array should be empty 

  // double bag
  DynamicBag<double> b;
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty()); // since default, data array should be empty 

  // string bag
  DynamicBag<std::string> c;
  REQUIRE(c.getCurrentSize() == 0);
  REQUIRE(c.isEmpty()); // since default, data array should be empty 
}

TEST_CASE("test copy constructor","[DynamicBag]") {
  // integer bag copy
  DynamicBag<int> a;
  a.add(1);
  a.add(2);
  a.add(3);

  DynamicBag<int> b(a);
  REQUIRE(b.contains(1));
  REQUIRE(b.contains(2));
  REQUIRE(b.contains(3));

  // double bag copy
  DynamicBag<double> c;
  c.add(0.333);
  c.add(0.666);
  c.add(0.999);

  DynamicBag<double> d(c);
  REQUIRE(d.contains(0.333));
  REQUIRE(d.contains(0.666));
  REQUIRE(d.contains(0.999));

  // string bag copy
  DynamicBag<std::string> e;
  e.add("hi");
  e.add("gavin");

  DynamicBag<std::string> f(e);
  REQUIRE(f.contains("hi"));
  REQUIRE(f.contains("gavin"));
}

TEST_CASE("test destructor","[DynamicBag]") {
  // integer bag
  DynamicBag<int> a;
  a.add(1);
  a.add(2);
  a.add(3);

  // double bag
  DynamicBag<double> b;
  b.add(0.333);
  b.add(0.666);
  b.add(0.999);

  // string bag copy
  DynamicBag<std::string> c;
  c.add("hi");
  c.add("gavin");

  // destructor stuff FINISH THIS!
}

TEST_CASE("test copy assignment operator","[DynamicBag]") {
  // integer bag copy using copy assignment operator
  DynamicBag<int> a;
  a.add(1);
  a.add(2);
  a.add(3);

  DynamicBag<int> b = a;
  REQUIRE(b.contains(1));
  REQUIRE(b.contains(2));
  REQUIRE(b.contains(3));

  // double bag copy using copy assignment operator
  DynamicBag<double> c;
  c.add(0.333);
  c.add(0.666);
  c.add(0.999);

  DynamicBag<double> d = c;
  REQUIRE(d.contains(0.333));
  REQUIRE(d.contains(0.666));
  REQUIRE(d.contains(0.999));

  // string bag copy using copy assignment operator
  DynamicBag<std::string> e;
  e.add("hi");
  e.add("gavin");

  DynamicBag<std::string> f = e;
  REQUIRE(f.contains("hi"));
  REQUIRE(f.contains("gavin"));
}

TEST_CASE("test copy swap idiom","[DynamicBag]") {
  // integer bag swap
  DynamicBag<int> a;
  a.add(1);
  a.add(2);
  a.add(3);

  DynamicBag<int> b;
  b.add(10);
  b.add(20);
  b.add(30);

  b.swap(a);
  REQUIRE(b.contains(1));
  REQUIRE(b.contains(2));
  REQUIRE(b.contains(3));
  REQUIRE(a.contains(10));
  REQUIRE(a.contains(20));
  REQUIRE(a.contains(30));

  // double bag swap
  DynamicBag<double> c;
  c.add(0.333);
  c.add(0.666);
  c.add(0.999);

  DynamicBag<double> d;
  d.add(0.1);
  d.add(0.2);
  d.add(0.3);

  d.swap(c);
  REQUIRE(d.contains(0.333));
  REQUIRE(d.contains(0.666));
  REQUIRE(d.contains(0.999));
  REQUIRE(c.contains(0.1));
  REQUIRE(c.contains(0.2));
  REQUIRE(c.contains(0.3));

  // string bag swap
  DynamicBag<std::string> e;
  e.add("hi");
  e.add("gavin");

  DynamicBag<std::string> f;
  f.add("ece0302");
  f.add("is");
  f.add("great");

  f.swap(e);
  REQUIRE(f.contains("hi"));
  REQUIRE(f.contains("gavin"));
  REQUIRE(e.contains("ece0302"));
  REQUIRE(e.contains("is"));
  REQUIRE(e.contains("great"));
}

TEST_CASE("test add method","[DynamicBag]") {
  // integer bag adding
  DynamicBag<int> a;
  a.add(1);
  a.add(2);
  a.add(3);
  REQUIRE(a.contains(1));
  REQUIRE(a.contains(2));
  REQUIRE(a.contains(3));

  // double bag adding
  DynamicBag<double> c;
  c.add(0.333);
  c.add(0.666);
  c.add(0.999);
  REQUIRE(c.contains(0.333));
  REQUIRE(c.contains(0.666));
  REQUIRE(c.contains(0.999));

  // string bag adding
  DynamicBag<std::string> e;
  e.add("hi");
  e.add("gavin");
  REQUIRE(e.contains("hi"));
  REQUIRE(e.contains("gavin"));
}

TEST_CASE("test remove method","[DynamicBag]") {
  // integer bag removing
  DynamicBag<int> a;
  a.add(1);
  a.add(2);
  a.add(3);
  REQUIRE(a.contains(1));
  REQUIRE(a.contains(2));
  REQUIRE(a.contains(3));

  a.remove(3);
  REQUIRE(a.contains(1));
  REQUIRE(a.contains(2));
  REQUIRE_FALSE(a.contains(3));

  // double bag removing
  DynamicBag<double> c;
  c.add(0.333);
  c.add(0.666);
  c.add(0.999);
  REQUIRE(c.contains(0.333));
  REQUIRE(c.contains(0.666));
  REQUIRE(c.contains(0.999));

  c.remove(0.999);
  REQUIRE(c.contains(0.333));
  REQUIRE(c.contains(0.666));
  REQUIRE_FALSE(c.contains(0.999));

  // string bag removing
  DynamicBag<std::string> e;
  e.add("hi");
  e.add("gavin");
  REQUIRE(e.contains("hi"));
  REQUIRE(e.contains("gavin"));

  e.remove("gavin");
  REQUIRE(e.contains("hi"));
  REQUIRE_FALSE(e.contains("gavin"));
}

TEST_CASE("test isEmpty method","[DynamicBag]") {
  // integer bag isEmpty
  DynamicBag<int> a;
  REQUIRE(a.isEmpty()); // since default, data array should be empty 

  // double bag isEmpty
  DynamicBag<double> b;
  REQUIRE(b.isEmpty()); // since default, data array should be empty 

  // string bag isEmpty
  DynamicBag<std::string> c;
  REQUIRE(c.isEmpty()); // since default, data array should be empty 
}

TEST_CASE("test getCurrentSize method","[DynamicBag]") {
  // integer bag getCurrentSize method
  DynamicBag<int> a;
  REQUIRE(a.getCurrentSize() == 0); 
  a.add(1);
  a.add(2);
  a.add(3);
  REQUIRE(a.getCurrentSize() == 3);

  // double bag getCurrentSize method
  DynamicBag<double> b;
  REQUIRE(b.getCurrentSize() == 0); 
  b.add(0.1);
  b.add(0.2);
  b.add(0.3);
  REQUIRE(b.getCurrentSize() == 3);

  // string bag getCurrentSize method
  DynamicBag<std::string> c;
  REQUIRE(c.getCurrentSize() == 0);
  c.add("hi");
  c.add("gavin");
  REQUIRE(c.getCurrentSize() == 2);
}

TEST_CASE("test contains method","[DynamicBag]") {
  // integer bag adding and removing to test contains method
  DynamicBag<int> a;
  a.add(1);
  a.add(2);
  a.add(3);
  REQUIRE(a.contains(1));
  REQUIRE(a.contains(2));
  REQUIRE(a.contains(3));

  a.remove(3);
  REQUIRE(a.contains(1));
  REQUIRE(a.contains(2));
  REQUIRE_FALSE(a.contains(3));

  // double bag adding and removing to test contains method
  DynamicBag<double> c;
  c.add(0.333);
  c.add(0.666);
  c.add(0.999);
  REQUIRE(c.contains(0.333));
  REQUIRE(c.contains(0.666));
  REQUIRE(c.contains(0.999));

  c.remove(0.999);
  REQUIRE(c.contains(0.333));
  REQUIRE(c.contains(0.666));
  REQUIRE_FALSE(c.contains(0.999));

  // string bag adding and removing to test contains method
  DynamicBag<std::string> e;
  e.add("hi");
  e.add("gavin");
  REQUIRE(e.contains("hi"));
  REQUIRE(e.contains("gavin"));

  e.remove("gavin");
  REQUIRE(e.contains("hi"));
  REQUIRE_FALSE(e.contains("gavin"));
}

TEST_CASE("test clear method","[DynamicBag]") {
  // integer bag clear method
  DynamicBag<int> a; 
  a.add(1);
  a.add(2);
  a.add(3);
  REQUIRE(a.getCurrentSize() == 3);
  a.clear();
  REQUIRE(a.getCurrentSize() == 0); 

  // double bag clear method
  DynamicBag<double> b;
  b.add(0.1);
  b.add(0.2);
  b.add(0.3);
  REQUIRE(b.getCurrentSize() == 3);
  b.clear();
  REQUIRE(b.getCurrentSize() == 0); 

  // string bag clear method
  DynamicBag<std::string> c;
  c.add("hi");
  c.add("gavin");
  REQUIRE(c.getCurrentSize() == 2);
  c.clear();
  REQUIRE(c.getCurrentSize() == 0);
}

TEST_CASE("test getFrequencyOf method","[DynamicBag]") {
  // integer bag getFrequencyOf method
  DynamicBag<int> a;
  a.add(1);
  a.add(1);
  a.add(3);
  REQUIRE(a.getFrequencyOf(1) == 2);

  // double bag getFrequencyOf method
  DynamicBag<double> b;
  b.add(0.1);
  b.add(0.2);
  b.add(0.3);
  REQUIRE(b.getFrequencyOf(0.1) == 1); 

  // string bag getFrequencyOf method
  DynamicBag<std::string> c;
  c.add("hi");
  c.add("gavin");
  c.add("hi");
  REQUIRE(c.getFrequencyOf("hi") == 2);
}

TEST_CASE("test operator==","[DynamicBag]") {
  // integer bag operator==
  DynamicBag<int> a; 
  a.add(1);
  a.add(2);
  a.add(3);

  DynamicBag<int> b;
  b.add(1);
  b.add(2);
  b.add(3);

  REQUIRE(a == b);


  // double bag operator==
  DynamicBag<double> c;
  c.add(0.1);
  c.add(0.2);
  c.add(0.3);

  DynamicBag<double> d;
  d.add(0.1);
  d.add(0.2);
  d.add(0.3);
  d.add(0.4);

  REQUIRE_FALSE(c == d);

  // string bag operator==
  DynamicBag<std::string> e;
  e.add("hi");
  e.add("gavin");

  DynamicBag<std::string> f;
  f.add("hi");
  f.add("gavin");

  REQUIRE(e == f);
}