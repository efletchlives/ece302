#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"

template class LinkedList<int>;

TEST_CASE("test default constructor", "[LinkedList]")
{
    // integer linked list
    LinkedList<int> list1;
    REQUIRE(list1.isEmpty());
    REQUIRE(list1.getLength() == 0);

    // string linked list
    LinkedList<std::string> list2;
    REQUIRE(list1.isEmpty());
    REQUIRE(list1.getLength() == 0);
}

TEST_CASE("test copy constructor", "[LinkedList]")
{
    // integer linked list
    LinkedList<int> list1;
    list1.insert(1,10);
    list1.insert(2,20);
    list1.insert(3,30);

    LinkedList<int> list2(list1);
    REQUIRE(list2.getEntry(1) == 10);
    REQUIRE(list2.getEntry(2) == 20);
    REQUIRE(list2.getEntry(3) == 30);

    // string linked list
    LinkedList<std::string> list3;
    list3.insert(1,"hi");
    list3.insert(2,"gavin");
    list3.insert(3,"again");

    LinkedList<std::string> list4(list3);
    REQUIRE(list4.getEntry(1) == "hi");
    REQUIRE(list4.getEntry(2) == "gavin");
    REQUIRE(list4.getEntry(3) == "again");
}

TEST_CASE("test copy assignment operator", "[LinkedList]")
{
    // integer linked list
    LinkedList<int> list1;
    list1.insert(1,5);
    list1.insert(2,10);
    list1.insert(3,15);
    list1.insert(4,20);

    LinkedList<int> list2 = list1;
    REQUIRE(list2.getEntry(1) == 5);
    REQUIRE(list2.getEntry(2) == 10);
    REQUIRE(list2.getEntry(3) == 15);
    REQUIRE(list2.getEntry(4) == 20);

    // string linked list
    LinkedList<std::string> list3;
    list3.insert(1,"302");
    list3.insert(2,"is");
    list3.insert(3,"super");
    list3.insert(4,"awesome");

    LinkedList<std::string> list4 = list3;
    REQUIRE(list4.getEntry(1) == "302");
    REQUIRE(list4.getEntry(2) == "is");
    REQUIRE(list4.getEntry(3) == "super");
    REQUIRE(list4.getEntry(4) == "awesome");
}

TEST_CASE("test swap method", "[LinkedList]")
{
    // integer linked list
    LinkedList<int> list1;
    list1.insert(1,5);
    list1.insert(2,10);
    list1.insert(3,15);
    list1.insert(4,20);

    LinkedList<int> list2;
    list2.insert(1,100);
    list2.insert(2,99);
    list2.insert(3,91);
    list2.insert(4,0);
    list2.swap(list1);

    REQUIRE(list1.getEntry(1) == 100);
    REQUIRE(list1.getEntry(2) == 99);
    REQUIRE(list1.getEntry(3) == 91);
    REQUIRE(list1.getEntry(4) == 0);
    REQUIRE(list2.getEntry(1) == 5);
    REQUIRE(list2.getEntry(2) == 10);
    REQUIRE(list2.getEntry(3) == 15);
    REQUIRE(list2.getEntry(4) == 20);

    // string linked list
    LinkedList<std::string> list3;
    list3.insert(1,"hi");
    list3.insert(2,"gavin");
    list3.insert(3,"again");

    LinkedList<std::string> list4;
    list4.insert(1,"i");
    list4.insert(2,"love");
    list4.insert(3,"302");
    list4.swap(list3);

    REQUIRE(list3.getEntry(1) == "i");
    REQUIRE(list3.getEntry(2) == "love");
    REQUIRE(list3.getEntry(3) == "302");

    REQUIRE(list4.getEntry(1) == "hi");
    REQUIRE(list4.getEntry(2) == "gavin");
    REQUIRE(list4.getEntry(3) == "again");
}

TEST_CASE("test isEmpty method", "[LinkedList]")
{
    // integer linked list
    LinkedList<int> list1;
    REQUIRE(list1.isEmpty());

    list1.insert(1,4);
    REQUIRE_FALSE(list1.isEmpty());

    // string linked list
    LinkedList<std::string> list3;
    REQUIRE(list3.isEmpty());

    list3.insert(1,"hi");
    REQUIRE_FALSE(list3.isEmpty());

}

TEST_CASE("test getLength method", "[LinkedList]")
{
    // integer linked list
    LinkedList<int> list1;
    REQUIRE(list1.getLength() == 0);

    list1.insert(1,10);
    list1.insert(2,20);
    list1.insert(3,30);
    REQUIRE(list1.getLength() == 3);

    // string linked list
    LinkedList<std::string> list2;
    REQUIRE(list2.getLength() == 0);

    list2.insert(1,"i");
    list2.insert(2,"love");
    list2.insert(3,"302");
    REQUIRE(list2.getLength() == 3);
}

TEST_CASE("test insert method", "[LinkedList]")
{
    // integer linked list
    LinkedList<int> list1;
    for(int i=1; i<=100; i++) {
        list1.insert(i,i*2);
        REQUIRE(list1.getEntry(i) == i*2);
    }

    // string linked list
    LinkedList<std::string> list2;
    for(int i=1; i<=100; i++) {
        list2.insert(i,"hi gavin");
        REQUIRE(list2.getEntry(i) == "hi gavin");
    }
}

TEST_CASE("test remove method", "[LinkedList]")
{
    // integer linked list
    LinkedList<int> list1;
    for(int i=1; i<=100; i++) {
        list1.insert(i,i*5);
        REQUIRE(list1.getEntry(i) == i*5);
    }
    for(int i=100; i>1; i--) {
        list1.remove(i);
        REQUIRE(list1.getEntry(i-1) == (i*5-5));
    }

    // string linked list
    LinkedList<std::string> list2;
    for(int i=1; i<=100; i++) {
        list2.insert(i,"I give gavin a " + std::to_string(i+10) + "/10");
        REQUIRE(list2.getEntry(i) == "I give gavin a " + std::to_string(i+10) + "/10");
    }
    for(int i=100; i>1; i--) {
        list2.remove(i);
        REQUIRE(list2.getEntry(i-1) == "I give gavin a " + std::to_string(i+9) + "/10");
    }

}

TEST_CASE("test clear method", "[LinkedList]")
{
    // integer linked list
    LinkedList<int> list1;
    for(int i=1; i<=100; i++) {
        list1.insert(i,i*5);
        REQUIRE(list1.getEntry(i) == i*5);
    }
    list1.clear();
    REQUIRE(list1.isEmpty());

    // string linked list
    LinkedList<std::string> list2;
    for(int i=1; i<=100; i++) {
        list2.insert(i,"I will get a " + std::to_string(i) + "% in 302");
        REQUIRE(list2.getEntry(i) == "I will get a " + std::to_string(i) + "% in 302");
    }
    list2.clear();
    REQUIRE(list2.isEmpty());
}

TEST_CASE("test getEntry method", "[LinkedList]")
{
    // integer linked list
    LinkedList<int> list1;
    for(int i=1; i<=100; i++) {
        list1.insert(i,i*9);
        REQUIRE(list1.getEntry(i) == i*9);
    }

    // string linked list
    LinkedList<std::string> list2;
    for(int i=1; i<=100; i++) {
        list2.insert(i,"I give gavin a " + std::to_string(i+20) + "/10");
        REQUIRE(list2.getEntry(i) == "I give gavin a " + std::to_string(i+20) + "/10");
    }
}

TEST_CASE("test setEntry method", "[LinkedList]")
{
    // integer linked list
    LinkedList<int> list1;
    for(int i=1; i<=100; i++) {
        list1.insert(i,i*5);
        REQUIRE(list1.getEntry(i) == i*5);
        list1.setEntry(i,i*7);
        REQUIRE(list1.getEntry(i) == i*7);
    }

    // string linked list
    LinkedList<std::string> list2;
    for(int i=1; i<=100; i++) {
        list2.insert(i,"I will get a " + std::to_string(i) + "% in 302");
        REQUIRE(list2.getEntry(i) == "I will get a " + std::to_string(i) + "% in 302");
        list2.setEntry(i,"I will get a " + std::to_string(i+1) + "% in 302");
        REQUIRE(list2.getEntry(i) == "I will get a " + std::to_string(i+1) + "% in 302");
    }
}
