#include "linked_list.hpp"

// things that i learned:
// when referencing next and item, you cannot interact with them directly since it is a private member of the Node class.
// you instead have to use the getter and setter functions in the Node class
// i had to replace the  "next =" with setNext() and the alone "next" with getNext()

template <typename T>
// default constructor
LinkedList<T>::LinkedList()
{
  head_node = nullptr; // to avoid dangling pointers and memory leaks since you aren't pointing to anything
  size = 0;
}

template <typename T>
// destructor
LinkedList<T>::~LinkedList()
{
  clear();
  delete head_node;
}

template <typename T>
// copy constructor
LinkedList<T>::LinkedList(const LinkedList<T> &x)
{
  head_node = nullptr; // to avoid dangling pointers and memory leaks since you aren't pointing to anything
  size = 0;
  Node<T>* copied_list = x.head_node; // set the new pointer to the head node of the linked list you are copying from
  for(int i=1;i<=(x.getLength());i++) { // while within the size of the linked list you are copying
    insert(size+1,copied_list->getItem()); // insert a node after the head node
    copied_list = copied_list->getNext(); // shift current to point to the next node
  }
}

template <typename T>
// copy assignment operator
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> x)
{
  swap(x); // using swap method below
  return *this;
}

template <typename T>
// swaps the private members of the current linked list with linked list x
void LinkedList<T>::swap(LinkedList &x)
{
  // use swap method from standard library to swap the head nodes and sizes
  std::swap(head_node,x.head_node); 
  std::swap(size,x.size);
}

template <typename T>
// checks if the linked list has no nodes in it
bool LinkedList<T>::isEmpty() const noexcept
{
  if(size == 0){
    return true;
  }
  return false;
}

template <typename T>
// returns # of nodes in the linked list
std::size_t LinkedList<T>::getLength() const noexcept
{
  return size;
}

template <typename T>
// inserts node at specified position in the linked list
bool LinkedList<T>::insert(std::size_t position, const T &item)
{
  if(position < 1 || position > size + 1) {
    return false; // insert unsuccessful
  }
  // allocate memory for new node
  Node<T>* new_node = new Node<T>(item);

  if(position == 1) {
    // have new node point to head and make that new node the head
    new_node->setNext(head_node);
    head_node = new_node;
  }
  else {
    // if position is within range [1,position]
    // set head node to a node to eventually mark the node before the position we are trying to change
    Node<T>* node_before = head_node;

    // shift over this node to the node before the specified position
    for(int i=1;i<(position-1);i++) {
      node_before = node_before->getNext();
    }
    // new node points at what the node before pointed at (this is allowed since multiple pointers can point at one piece of data)
    new_node->setNext(node_before->getNext());

    // node before points at the new node
    node_before->setNext(new_node);
  }

  size++; // increment size since new node inserted
  return true; // insert successful
}

template <typename T>
// removes node at specified position in the linked list
bool LinkedList<T>::remove(std::size_t position)
{
  if(position < 1 || position > size) {
    return false; // removal unsuccessful
  }

  // create a node to act as a placeholder for the node to be removed later
  Node<T>* temp_node = nullptr;

  // if position is the head node
  if(position == 1) {
    temp_node = head_node; // set temporary node to the head node
    head_node = head_node->getNext(); // make the head node the next element after the temporary node
  }
  else { // if position is in the middle of the data
    // create a node to represent the node before the specified position
    Node<T>* node_before = head_node;

    // shift this node over to the node before the specified position 
    for(int i=1;i<(position-1);i++) {
      node_before = node_before->getNext();
    } 
    temp_node = node_before->getNext(); // set the temporary node to the pointer pointing to the position node
    node_before->setNext(temp_node->getNext()); // set the node before to point at the value after the specified position (this essentially removes the node at the specified position from the linked list)
  }

  delete temp_node; // delete the temporary node (which also deletes the node at the specified position)
  size--; // decrement size
  return true; // removal successful
}

template <typename T>
// clears linked list of nodes
void LinkedList<T>::clear()
{
  // to prevent a memory leak
  while(head_node) {
    Node<T>* temp = head_node; // set a temporary pointer to the head node pointer
    head_node = head_node->getNext(); // set head node pointer to the pointer of the next node
    delete temp; // then delete the temporary pointer
  }

  size = 0; // clear linked list
}

template <typename T>
// gets entry in linked list
T LinkedList<T>::getEntry(std::size_t position) const
{
  // if position is outside range of size
  if(position < 1 || position > size) {
    throw std::out_of_range("position out of range");
  }
  Node<T>* current_node = head_node;
  // shift the pointer over to the node before the position
  for(int i=1;i<position;i++) {
    current_node = current_node->getNext();
  }

  return current_node->getItem(); // return the pointer of the node before since it is pointing at the specified position's value
  
}

template <typename T>
// sets entry at specified position to specified value
void LinkedList<T>::setEntry(std::size_t position, const T &newValue)
{
  // if position is outside range of size
  if(position < 1 || position > size) {
    throw std::out_of_range("position out of range"); // entry set successful
  }
  // create a node to represent the node before
  Node<T>* current_node = head_node;

  // shift this pointer over to the node before the position of the value you want to set
  for(int i=1;i<position;i++){
    current_node = current_node->getNext();
  }

  // change value through the pointer of node before since it points to the node at the specified position
  current_node->setItem(newValue);

  // entry set successful
}
