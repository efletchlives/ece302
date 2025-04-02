#include "binary_search_tree.hpp"

// default constructor
template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = nullptr;
}

// copy constructor
// this constructor uses a stack to copy the tree
template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(
    const BinarySearchTree<KeyType, ItemType> &tree_to_copy)
{
    root = nullptr;
    Node<KeyType, ItemType> **this_tree_root = &root;

    std::stack<stackvar<KeyType, ItemType>> s;

    stackvar<KeyType, ItemType> rootvar;
    rootvar.node_to_copy = tree_to_copy.root;
    rootvar.this_node_address = this_tree_root;
    s.push(rootvar);

    while (!s.empty())
    {
        stackvar<KeyType, ItemType> currentvar = s.top();
        s.pop();

        Node<KeyType, ItemType> *curr_node_to_copy = currentvar.node_to_copy;
        Node<KeyType, ItemType> **curr_this_node_address = currentvar.this_node_address;

        if (curr_node_to_copy == nullptr)
            continue;

        // allocate new node and copy contents
        Node<KeyType, ItemType> *temp = new Node<KeyType, ItemType>;
        temp->key = curr_node_to_copy->key;
        temp->data = curr_node_to_copy->data;
        temp->left = nullptr;
        temp->right = nullptr;
        *curr_this_node_address = temp; // assigns value using this node address

        // push left subtree
        stackvar<KeyType, ItemType> left_subtree_root;
        left_subtree_root.node_to_copy = curr_node_to_copy->left;
        left_subtree_root.this_node_address = &((*curr_this_node_address)->left);
        s.push(left_subtree_root);

        // push right subtree
        stackvar<KeyType, ItemType> right_subtree_root;
        right_subtree_root.node_to_copy = curr_node_to_copy->right;
        right_subtree_root.this_node_address = &((*curr_this_node_address)->right);
        s.push(right_subtree_root);
    }
}

// copy assignment operator using copy-and-swap idiom
template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType> &BinarySearchTree<KeyType, ItemType>::
operator=(BinarySearchTree<KeyType, ItemType> tree_to_copy)
{
    swap(tree_to_copy);
    return *this;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::swap(BinarySearchTree<KeyType, ItemType> &tree_to_swap)
{
    std::swap(root, tree_to_swap.root);
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy();
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    // push root node to stack
    std::stack<Node<KeyType, ItemType> *> s;
    s.push(root);

    while (!s.empty())
    {
        // pop the top node from the stack
        Node<KeyType, ItemType> *curr = s.top();
        s.pop();

        // push left and right children to the stack
        // and delete the current node
        if (curr != nullptr)
        {
            s.push(curr->left);
            s.push(curr->right);
            delete curr;
        }
    }
    // set root to nullptr to avoid dangling pointer
    root = nullptr;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(
    const KeyType &key, const ItemType &item)
{
    // create a new node (node is ptr, use -> to update data members) using dynamic allocation
    Node<KeyType, ItemType> *added_node = new Node<KeyType, ItemType>;

    // added_node = current (was causing issues)
    added_node -> key = key;
    added_node -> data = item;
    added_node -> left = nullptr; 
    added_node -> right = nullptr;

    // 1. edge case, check if the tree is empty
    if(isEmpty()) {
        root = added_node;
    }
    else {
        // 2. edge case, check if the key already exists (search function can be used) and find where to insert the new node (review search function)
        Node<KeyType, ItemType> *current;
        Node<KeyType, ItemType> *cparent;
        search(key, current, cparent);

        if (key == current -> key) {
            delete added_node;
            return false;
        }
        else if (key < current -> key) {
            current -> left = added_node;
        }
        else {
            current -> right = added_node;
        }
    }

    return true; // insert successful
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    if(root == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(
    const KeyType &key, ItemType &item)
{
    Node<KeyType, ItemType> *curr;
    Node<KeyType, ItemType> *curr_parent;
    bool found = search(key, curr, curr_parent);

    if (found)
    {
        item = curr->data;
        return true;
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    // exception: check if the tree is empty
    if(isEmpty()) {
        return false;
    }

    // root is the only node in the tree
    if (root -> left == nullptr && root -> right == nullptr) {
        if (root -> key == key) {
            delete root;
            root = nullptr; 
            return true;
        } 
        else {
            return false;
        }
    }

    Node<KeyType, ItemType>* current = nullptr;
    Node<KeyType, ItemType>* parent = nullptr;
    search(key,current,parent); 
    ItemType item;

    if (current -> key != key) {
        return false;
    }

    // if the node has no children
    // ex: 
    //    parent  
    //        \
    //        ∨
    //      current
    //    /        \
    //   ∨         ∨ 
    // empty     empty
    else if(current -> left == nullptr && current -> right == nullptr) {
        // if the left child is equal to the node to remove
        if(parent -> left == current) {
            parent -> left = nullptr;
        }
        else if(parent -> right == current) {
            parent -> right = nullptr;
        }
        // deallocate removed node
        delete current;
    }


    // if the node to delete has only right child (delete right child)
    // ex: 
    //    parent
    //        \
    //        ∨
    //     current
    //    /      \
    //   ∨       ∨ 
    // empty   right

    // in this case the current node is removed and the child node replaces it
    // after deletion in example:
    //    parent
    //        \
    //        ∨
    //      right
    else if(current -> left == nullptr) {
        // if parent does not exist
        if (parent == nullptr) {
            root = current -> right; // replace the root with the right child
            delete current;
        }
        // if the left child of the parent is current
        else if (parent -> left == current) {
            parent -> left = current -> right;
            delete current;
        }
        // if the right child of the parent is current
        else {
            parent -> right = current -> right;
            delete current;
        }
    }


    // if the node to delete has only a left child (delete left child)
    //    parent
    //        \
    //        ∨
    //     current
    //    /      \
    //   ∨       ∨ 
    //  left   empty

    // in this case the current node is removed and the child node replaces it
    //    parent
    //        \
    //        ∨
    //       left
    else if (current -> right == nullptr) {
        // if the parent node does not exist
        if (parent == nullptr) {
            root = current -> left;
            delete current;
        }
        // if the current node is left node of the parent
        else if (parent -> left == current) {
            parent -> left = current -> left;
            delete current;
        }
        // if the current node is right node of the parent
        else {
            parent -> right = current -> left;
            delete current;
        }
    }

    // this has to be the issue below \\

    // if the node to delete has two children
    // ex: 
    //    parent
    //         \
    //       current
    //      /      \
    //     ∨       ∨ 
    //    left   right
    else {
        Node<KeyType, ItemType> *child;
        parent = nullptr;
        inorder_successor(current,child,parent);

        std::swap(current,child); // swap current with child to replace it
        child -> data = current -> data;
        child -> key = current -> key;

        if (parent -> left == current) {
            delete current;
            parent -> left = nullptr;
        }
        else if (parent -> right == current) {
            delete current;
            parent -> right = nullptr;
        }
    }
    
    return true; // remove successful
}



// My bonus doesn't work yet

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(KeyType arr[], int arr_size)
{
    // BONUS TODO: check for duplicate items in the input array (throw an exception if so)
    // this nested loop uses the binary search tree to sort the array
    for (int i = 0; i < arr_size; i++) {
        // checks if the item is in the correct order
        if(insert(arr[i], ItemType()) == false) {
            // loop through the array for every element after the element that it fails at
            for (int j = i; j < arr_size-1; j++) {
                // shift the elements over by one
                arr[j] = arr[j + 1];
            }
            arr_size--;
            i--;
        }
    }
    // BONUS TODO: overwrite input array values with sorted values
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder_successor(Node<KeyType, ItemType> *curr,
                                                            Node<KeyType, ItemType> *&inorder,
                                                            Node<KeyType, ItemType> *&inorder_parent)
{
    inorder_parent = curr;
    inorder = curr->right; // start with the right child

    // find the leftmost node in the right subtree, this is the inorder successor
    while (inorder != nullptr && inorder->left != nullptr)
    {
        inorder_parent = inorder;
        inorder = inorder->left;
    }
    // inorder points to the inorder successor at the end of this loop
    // inorder_parent points to the parent of the inorder successor
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::search(KeyType key,
                                                 Node<KeyType, ItemType> *&curr,
                                                 Node<KeyType, ItemType> *&curr_parent)
// last two parameters are passed by reference to allow the caller to modify them
{
    curr = root;
    curr_parent = nullptr;

    if (isEmpty())
        return false;

    while (true)
    {
        if (key == curr->key)
        {
            // found
            return true;
        }
        if (key < curr->key)
        {
            // search left
            if (curr->left != nullptr)
            {
                curr_parent = curr;
                curr = curr->left;
            }
            else
            {
                // nowhere further to search
                return false;
            }
        }
        else
        {
            // search right
            if (curr->right != nullptr)
            {
                curr_parent = curr;
                curr = curr->right;
            }
            else
            {
                // nowhere further to search
                return false;
            }
        }
    }
}
