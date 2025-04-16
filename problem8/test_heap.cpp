#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "ArrayMaxHeap.hpp"

/* Provided test cases */
// all passed 
TEST_CASE("Heap: test construct from array", "[construct]")
{
   int array[] = {80, 70, 60, 50, 40, 30, 20, 10};
   ArrayMaxHeap<int> heap(array, 8);
   REQUIRE(heap.getNumberOfNodes() == 8);
   REQUIRE(heap.getHeight() == 4);
   REQUIRE(heap.isEmpty() == false);
   heap.clear();
   REQUIRE(heap.getNumberOfNodes() == 0);
   REQUIRE(heap.getHeight() == 0);
   REQUIRE(heap.isEmpty() == true);
}

TEST_CASE("Heap: test heap sort", "[sort]")
{
   int array[] = {15, 5, 20, 10, 30};
   ArrayMaxHeap<int> heap(array, 5);
   heap.heapSort(array, 5);
   REQUIRE(array[0] == 30);
   REQUIRE(array[1] == 20);
   REQUIRE(array[2] == 15);
   REQUIRE(array[3] == 10);
   REQUIRE(array[4] == 5);
}

/* Additional test cases */

TEST_CASE("my test cases") {
   // sort testing
   int array1[] = {8, 1, 6, 3, 10};
   ArrayMaxHeap<int> heap1;
   heap1.heapSort(array1, 5);
   REQUIRE(array1[0] == 10);
   REQUIRE(array1[1] == 8);
   REQUIRE(array1[2] == 6);
   REQUIRE(array1[3] == 3);
   REQUIRE(array1[4] == 1);

   // testing duplicate value input
   int array2[] = {7, 2, 2, 9, 5};
   ArrayMaxHeap<int> heap2;
   REQUIRE_THROWS_AS(heap2.heapSort(array2, 5), std::invalid_argument);

   // testing array size larger than heap size
   int array3[100];
   for (int i = 0; i < 100; ++i) {
      array3[i] = i;
   }
   ArrayMaxHeap<int> heap3;
   REQUIRE_THROWS_AS(heap3.heapSort(array3, 100), std::invalid_argument);

   // testing if already sorted correctly
   int array4[] = {50, 40, 30, 20, 10};
   ArrayMaxHeap<int> heap4;
   heap4.heapSort(array4, 5);
   REQUIRE(array4[0] == 50);
   REQUIRE(array4[1] == 40);
   REQUIRE(array4[2] == 30);
   REQUIRE(array4[3] == 20);
   REQUIRE(array4[4] == 10);
}

TEST_CASE("test add and remove") {
   ArrayMaxHeap<int> heap1;
   REQUIRE(heap1.isEmpty());

   heap1.add(10);
   REQUIRE_FALSE(heap1.isEmpty());
   REQUIRE(heap1.getNumberOfNodes() == 1);
   REQUIRE(heap1.peekTop() == 10);

   heap1.add(20);
   REQUIRE(heap1.getNumberOfNodes() == 2);
   REQUIRE(heap1.peekTop() == 20);

   heap1.add(5);
   REQUIRE(heap1.getNumberOfNodes() == 3);
   REQUIRE(heap1.peekTop() == 20);

   // adding duplicate value
   ArrayMaxHeap<int> heap2;
   heap2.add(10);
   REQUIRE_FALSE(heap2.add(10));

   // adding item to max heap
   ArrayMaxHeap<int> heap3;
   for (int i = 0; i < 63; ++i) {
      heap3.add(i + 1);
   }
   REQUIRE(heap3.getNumberOfNodes() == 63);
   REQUIRE_FALSE(heap3.add(100)); // Should throw when full


   // adding and removing
   ArrayMaxHeap<int> heap4;

   heap4.add(10);
   heap4.add(30);
   heap4.add(20);

   REQUIRE(heap4.getNumberOfNodes() == 3);
   REQUIRE(heap4.peekTop() == 30);

   REQUIRE(heap4.remove()); // 30 removed
   REQUIRE(heap4.getNumberOfNodes() == 2);
   REQUIRE(heap4.peekTop() == 20);

   REQUIRE(heap4.remove()); // 20 removed
   REQUIRE(heap4.getNumberOfNodes() == 1);
   REQUIRE(heap4.peekTop() == 10);

   REQUIRE(heap4.remove()); // 10 removed
   REQUIRE(heap4.isEmpty());

   // removing from empty heap
   REQUIRE_FALSE(heap4.remove()); 
}