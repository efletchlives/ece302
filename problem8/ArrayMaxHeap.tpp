#include <cmath> // for log2
#include "ArrayMaxHeap.hpp"
#include <stdexcept>

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 1;
} // end getLeftChildIndex, private method

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 2;
} // end getRightChildIndex, private method

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(const int nodeIndex) const
{
   return (nodeIndex - 1) / 2;
} // end getParentIndex, private method

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(const int nodeIndex) const
{
   return (getLeftChildIndex(nodeIndex) >= itemCount);
} // end isLeaf, private method

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(const int subTreeNodeIndex)
{
   if (!isLeaf(subTreeNodeIndex))
   {
      // get left and right child
      int left_child = getLeftChildIndex(subTreeNodeIndex);
      int right_child = getRightChildIndex(subTreeNodeIndex);
      int larger_child = left_child;

      // checks if right child exists and if right child is larger child
      if (right_child < itemCount && items[right_child] > items[left_child]) {
         larger_child = right_child;
      }

      // check if the parent node value is less than the larger child node value
      if (items[subTreeNodeIndex] < items[larger_child]) {
         std::swap(items[subTreeNodeIndex], items[larger_child]); // swap parent with larger child if node value is smaller
         heapRebuild(larger_child); // Continue with the recursion at that child
      }
   } // end if
} // end heapRebuild, private method

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
   // Start with the last parent node and rebuild the heap to the root
   for (int index = itemCount / 2 - 1; index >= 0; index--)
   {
      heapRebuild(index);
   } // end for
} // end heapCreate, private method

//******************************************************************
//
// Public methods start here
//
//******************************************************************

template <typename ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() : itemCount(0)
{
} // end default constructor

template <typename ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(const ItemType someArray[], const int arraySize) : itemCount(arraySize)
{
   // Copy given values into the array
   for (int i = 0; i < itemCount; i++)
      items[i] = someArray[i];

   // Reorganize the array into a heap
   heapCreate();
} // end constructor

template <typename ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{
   clear();
} // end destructor

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const noexcept
{
   return itemCount == 0;
} // end isEmpty

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const noexcept
{
   return ceil(log2(itemCount + 1));
} // end getHeight

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const noexcept
{
   return itemCount;
} // end getNumberOfNodes

template <typename ItemType>
void ArrayMaxHeap<ItemType>::clear() noexcept
{
   itemCount = 0;
} // end clear

template <typename ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const
{
   return items[0]; // peeks at the root of the heap
} // end peekTop

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType &newData)
{
   // make sure that all items not used are initialized to 0
   // for(int i=itemCount; i<DEFAULT_CAPACITY; i++) {
   //    items[i] = nullptr;
   // }

   // exception: heap is at max capacity
   if (itemCount >= DEFAULT_CAPACITY) {
      return false; // add unsuccessful
   }

   // exception: duplicate item
   for(int i=0; i<itemCount; i++) {
      if(items[i] == newData) {
         return false;
      }
   }

   int child = itemCount;
   items[itemCount] = newData; // add item at the end of the heap
   itemCount++; // add item to item count

   int parent = getParentIndex(child);
   // loop until we reach the root and if the child value is greater than the parent value
   while (child > 0 && items[child] > items[parent]) {
         std::swap(items[child], items[parent]); // swap the items
         child = parent; // move up a level
         parent = getParentIndex(child);
   }

   return true; // add successful
} // end add

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
   // exception: heap is empty
   if (isEmpty()) {
      return false;
   }

   std::swap(items[0], items[itemCount - 1]); // remove the last item and swap it with the root
   itemCount--; // remove item from item count
   heapRebuild(0); // rebuild heap from the root

   return true; // Placeholder
} // end remove

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapSort(ItemType anArray[], int n)
{
   // exception: if input size is greater than max size
   if (n > DEFAULT_CAPACITY) {
      throw std::invalid_argument("input is greater than max capacity");
   }

   // check for duplicates
   for(int i = 0; i < n-1; i++) {
      for(int j = 0; j < n; j++) {
         if (j == i) {
            continue;
         }
         else if(anArray[i] == anArray[j]) {
            throw std::invalid_argument("there are duplicate values in the input array");
         }
      }
   }
   
   // build initial heap
   ArrayMaxHeap<ItemType> initial_heap(anArray, n); 

   // loop through the heap in descending order
   for (int i = 0; i < n; i++) {
      anArray[i] = initial_heap.items[0]; // put the highest value item at the end of the array
      initial_heap.items[0] = initial_heap.items[initial_heap.itemCount - 1]; // move last item in heap to root
      initial_heap.itemCount--; // decrement item count since you removed item
      initial_heap.heapRebuild(0); // rebuild heap since you removed item
   }
   // Remove root, swap, and rebuild the heap

} // end heapSort
