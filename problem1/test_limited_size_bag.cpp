#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"

// force template expansion for ints
template class LimitedSizeBag<int>;

TEST_CASE("Calling all public members", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}

TEST_CASE("test default constructor","[LimitedSizeBag]") {
  LimitedSizeBag<int> a;
  REQUIRE(a.getCurrentSize() == 0);
}

TEST_CASE("test maxsize","[LimitedSizeBag]") {
  // integer bag
  LimitedSizeBag<int> a;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    a.add(i);
  }
  REQUIRE(a.getCurrentSize() == LimitedSizeBag<int>::maxsize);

  // double bag
  LimitedSizeBag<double> b;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    b.add(0.1);
  }
  REQUIRE(b.getCurrentSize() == LimitedSizeBag<int>::maxsize);

  // string bag
  LimitedSizeBag<std::string> c;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    c.add("hi");
  }
  REQUIRE(c.getCurrentSize() == LimitedSizeBag<int>::maxsize);
}

TEST_CASE("test add method","[LimitedSizeBag]") {
  // integer bag
  LimitedSizeBag<int> a;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    a.add(i);
    REQUIRE(a.contains(i));
  }
  REQUIRE_FALSE(a.add(101));

  // double bag
  LimitedSizeBag<double> b;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    b.add(i*0.1);
    REQUIRE(b.contains(i*0.1));
  }
  REQUIRE_FALSE(a.add(101*0.1));

  // string bag
  LimitedSizeBag<std::string> c;
  c.add("hi");
  c.add("hi");
  REQUIRE(c.getCurrentSize() == 2);
}

TEST_CASE("test remove method","[LimitedSizeBag]") {
  // integer bag
  LimitedSizeBag<int> a;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    a.add(i);
    REQUIRE(a.contains(i));
  }
  a.remove(99);
  REQUIRE_FALSE(a.contains(99));

  // double bag
  LimitedSizeBag<double> b;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    b.add(i*0.1);
    REQUIRE(b.contains(i*0.1));
  }
  b.remove(99*0.1);
  REQUIRE_FALSE(b.contains(99*0.1));

  // string bag
  LimitedSizeBag<std::string> c;
  c.add("hi");
  c.add("gavin");
  c.remove("hi");
  REQUIRE(c.getCurrentSize() == 1);
  REQUIRE_FALSE(c.contains("hi"));
}

TEST_CASE("test isEmpty method","[LimitedSizeBag]") {
  // integer bag
  LimitedSizeBag<int> a;
  REQUIRE(a.isEmpty());
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    a.add(i);
    REQUIRE(a.contains(i));
  }
  REQUIRE_FALSE(a.isEmpty());
  
  // double bag
  LimitedSizeBag<double> b;
  REQUIRE(b.isEmpty());
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    b.add(i*0.1);
    REQUIRE(b.contains(i*0.1));
  }
  REQUIRE_FALSE(b.isEmpty());

  // string bag
  LimitedSizeBag<std::string> c;
  REQUIRE(c.isEmpty());
  c.add("hi");
  c.add("gavin");
  REQUIRE_FALSE(c.isEmpty());
}

TEST_CASE("test getCurrentSize method","[LimitedSizeBag]") {
  // integer bag
  LimitedSizeBag<int> a;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    a.add(i);
    REQUIRE(a.contains(i));
  }
  REQUIRE(a.getCurrentSize() == 100);

  for(int i=49;i>=0;i--){
    a.remove(i);
    REQUIRE_FALSE(a.contains(i));
  }
  REQUIRE(a.getCurrentSize() == 50);
  
  // double bag
  LimitedSizeBag<double> b;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    b.add(i*0.1);
    REQUIRE(b.contains(i*0.1));
  }
  REQUIRE(b.getCurrentSize() == 100);

  for(int i=49;i>=0;i--){
    b.remove(i*0.1);
    REQUIRE_FALSE(a.contains(i*0.1));
  }
  REQUIRE(b.getCurrentSize() == 50);

  // string bag
  LimitedSizeBag<std::string> c;
  c.add("hi");
  c.add("gavin");
  REQUIRE(c.getCurrentSize() == 2);
  c.remove("gavin");
  REQUIRE(c.getCurrentSize() == 1);
}

TEST_CASE("test contains method","[LimitedSizeBag]") {
  // integer bag
  LimitedSizeBag<int> a;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    a.add(i);
    REQUIRE(a.contains(i));
  }
  
  // double bag
  LimitedSizeBag<double> b;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    b.add(i*0.1);
    REQUIRE(b.contains(i*0.1));
  }

  // string bag
  LimitedSizeBag<std::string> c;
  c.add("hi");
  c.add("gavin");
  REQUIRE(c.contains("hi"));
  REQUIRE(c.contains("gavin"));
}

TEST_CASE("test clear method","[LimitedSizeBag]") {
  // integer bag
  LimitedSizeBag<int> a;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    a.add(i);
    REQUIRE(a.contains(i));
  }
  a.clear();
  REQUIRE(a.getCurrentSize() == 0);
  
  // double bag
  LimitedSizeBag<double> b;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    b.add(i*0.1);
    REQUIRE(b.contains(i*0.1));
  }
  b.clear();
  REQUIRE(b.getCurrentSize() == 0);

  // string bag
  LimitedSizeBag<std::string> c;
  c.add("hi");
  c.add("gavin");
  REQUIRE(c.contains("hi"));
  REQUIRE(c.contains("gavin"));
  c.clear();
  REQUIRE(c.getCurrentSize() == 0);
}

TEST_CASE("test getFrequencyOf method","[LimitedSizeBag]") {
  // integer bag
  LimitedSizeBag<int> a;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    a.add(10);
    REQUIRE(a.contains(10));
  }
  REQUIRE(a.getFrequencyOf(10) == 100);
  
  // double bag
  LimitedSizeBag<double> b;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    b.add(10*0.1);
    REQUIRE(b.contains(10*0.1));
  }
  REQUIRE(b.getFrequencyOf(10*0.1) == 100);

  // string bag
  LimitedSizeBag<std::string> c;
  c.add("hi");
  c.add("gavin");
  REQUIRE(c.contains("hi"));
  REQUIRE(c.contains("gavin"));
  REQUIRE(c.getFrequencyOf("hi") == 1);
}

TEST_CASE("test operator==","[LimitedSizeBag]") {
  // integer bag
  LimitedSizeBag<int> a;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    a.add(i);
    REQUIRE(a.contains(i));
  }
  LimitedSizeBag<int> b;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    b.add(i);
    REQUIRE(b.contains(i));
  }

  REQUIRE(a == b);

  // double bag
  LimitedSizeBag<double> c;
  for(int i=0;i<50;i++) {
    c.add(i*0.1);
    REQUIRE(c.contains(i*0.1));
  }
  LimitedSizeBag<double> d;
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++) {
    d.add(i);
    REQUIRE(d.contains(i));
  }

  REQUIRE_FALSE(c == d);

  // string bag
  LimitedSizeBag<std::string> e;
  e.add("hi");
  e.add("gavin");
  REQUIRE(e.contains("hi"));
  REQUIRE(e.contains("gavin"));

  LimitedSizeBag<std::string> f;
  f.add("hi");
  f.add("gavin");
  REQUIRE(f.contains("hi"));
  REQUIRE(f.contains("gavin"));

  REQUIRE(e == f);

}