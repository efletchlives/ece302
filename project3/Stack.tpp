/** @file Stack.tpp */
// Finish this .tpp first to pass the first 3 unit tests

#include <stdexcept>
#include "Stack.hpp"
#include "Node.hpp"

template <typename ItemType>
// default constructor
Stack<ItemType>::Stack()
{
	headPtr = nullptr;
	currentSize = 0;
}

template <typename ItemType>
// destructor
Stack<ItemType>::~Stack()
{
	// pop items out until the stack is empty
	while(isEmpty() == false) {
		pop();
	}
}

template <typename ItemType>
// isEmpty method: returns true/false depending on if the stack is empty or not
bool Stack<ItemType>::isEmpty() const
{
	// if headPtr doesn't point to anything
	return headPtr == nullptr;
}

template <typename ItemType>
// size method: returns size of stack
int Stack<ItemType>::size() const
{
	return currentSize;
}

template <typename ItemType>
// push method: pushes newItem onto the stack
bool Stack<ItemType>::push(const ItemType &newItem)
{
	Node<ItemType> *newPtr = new Node<ItemType>(newItem, headPtr);
	headPtr = newPtr;
	newPtr = nullptr;

	currentSize++; // add item to size
	return true; // push successful
}

template <typename ItemType>
// peek method: peeks at the item at the top of the stack
ItemType Stack<ItemType>::peek() const
{
	if(isEmpty()) {
		throw std::out_of_range("the stack is empty so nothing to peek at");
	}
	return headPtr->getItem();
}

template <typename ItemType>
// pop method: pops top item out of the stack
bool Stack<ItemType>::pop()
{ 
	if(!isEmpty()) {
		Node<ItemType> *newPtr = headPtr;
		headPtr = headPtr->getNext();

		// remove item associated with headPtr
		newPtr->setNext(nullptr);
		delete newPtr;
		newPtr = nullptr;

		currentSize--; // remove item from size
		return true; // pop successful
	}
	return false;
}

template <typename ItemType>
// clear method: remove all of the items from the stack
void Stack<ItemType>::clear()
{
	while(!isEmpty()) {
		pop();
	}
	
}