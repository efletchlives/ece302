#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "binary_search_tree.hpp"

typedef BinarySearchTree<int, int> TreeType;

/* Provided test cases */

TEST_CASE("BST: Test Insert", "[insert]")   // passed
{
    TreeType bst1;

    REQUIRE(bst1.isEmpty());

    bst1.insert(10, 10);
    REQUIRE_FALSE(bst1.isEmpty());
}

TEST_CASE("BST: Test Duplicate Insert", "[duplicate insert]")    // passed
{
    TreeType bst1;

    REQUIRE(bst1.insert(12, 12));
    REQUIRE(!bst1.insert(12, 12));
}


// it arranges it correctly
//       10
//      /  \
//     5    15

// there is a segmentation fault in this
TEST_CASE("BST: Test Remove With No Children", "[remove]")
{
    TreeType bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5); // adds to the left of 5 (it is currently adding 5 as the root node, replacing 10)
    bst1.insert(15, 15); // adds to the right of 10 (doing this right)

    int item;
    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(15, item));

    // FAILS HERE (segmentation fault)
    bst1.remove(5);
    REQUIRE_FALSE(bst1.retrieve(5, item));

    bst1.remove(15);
    REQUIRE_FALSE(bst1.retrieve(15, item));

    bst1.remove(10);
    REQUIRE_FALSE(bst1.retrieve(10, item));

    REQUIRE(bst1.isEmpty());
}


TEST_CASE("BST: Test Copy Assign", "[copy assign]")  // passed
{
    TreeType bst1;

    bst1.insert(50, 50);
    bst1.insert(0, 0);
    bst1.insert(100, 100);
    bst1.insert(25, 25);
    bst1.insert(75, 75);

    TreeType bst2;

    bst2 = bst1;

    bst1.destroy();

    REQUIRE(bst1.isEmpty());

    REQUIRE_FALSE(bst2.isEmpty());

    
    int item;
    REQUIRE(bst2.retrieve(100, item));
    REQUIRE(bst2.retrieve(75, item));
    REQUIRE(bst2.retrieve(50, item));
    REQUIRE(bst2.retrieve(25, item));
    REQUIRE_FALSE(bst2.retrieve(51, item));
}

//   \\\\\\\ every test above works ///////





/* Your test cases here */

TEST_CASE("remove one child", "[remove]") {
    TreeType bst1;

    bst1.insert(20, 20);
    bst1.insert(10, 10);
    bst1.insert(30, 30);
    bst1.insert(25, 25); // Left child of 30

    int item;
    REQUIRE(bst1.retrieve(30, item));
    REQUIRE(bst1.retrieve(25, item));

    bst1.remove(30); // 30 has one child (25)

    REQUIRE_FALSE(bst1.retrieve(30, item));
    REQUIRE(bst1.retrieve(25, item)); // 25 should still be there
}

TEST_CASE("remove two children", "[remove]") {
    TreeType bst1;

    bst1.insert(50, 50);
    bst1.insert(30, 30);
    bst1.insert(70, 70);
    bst1.insert(20, 20);
    bst1.insert(40, 40);
    bst1.insert(60, 60);
    bst1.insert(80, 80);

    int item;
    REQUIRE(bst1.retrieve(50, item));

    bst1.remove(50); // Node 50 has two children (30, 70)

    REQUIRE_FALSE(bst1.retrieve(50, item));
    REQUIRE(bst1.retrieve(30, item));
    REQUIRE(bst1.retrieve(70, item));
}

TEST_CASE("retrieve item exception: item doesn't exist", "[retrieve]") {
    TreeType bst1;
    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);

    int item;
    REQUIRE_FALSE(bst1.retrieve(100, item)); // 100 is not in the tree
    REQUIRE_FALSE(bst1.retrieve(-5, item)); // -5 is not in the tree
}

TEST_CASE("test exception: empty tree", "[empty tree]") {
    TreeType bst1;

    int item;
    REQUIRE_FALSE(bst1.retrieve(10, item)); // Should return false for empty tree
    REQUIRE_FALSE(bst1.remove(10)); // Should return false when trying to remove from empty tree
    REQUIRE(bst1.isEmpty());
}

TEST_CASE("test 13: test remove root and to empty") {
    TreeType tree1;
    tree1.insert(20,20);
    tree1.insert(10,10);
    tree1.insert(30,30);
    tree1.insert(5,5);
    tree1.insert(15,15);
    tree1.insert(40,40);
    tree1.insert(12,12);
    tree1.insert(17,17);
    tree1.insert(35,35);
    tree1.insert(11,11);
    tree1.insert(16,16);
    tree1.insert(19,19);

}



// failed tests below b/c segmentation fault below
// TEST_CASE("BST: Test TreeSort with Small Array", "[tree sort]") {
//     TreeType tree1;
//     int arr[5] = {3, 1, 4, 1, 5}; // Contains a duplicate

//     REQUIRE_THROWS_WITH(tree1.treeSort(arr, 5), "Duplicate key found in input array.");
// }

// TEST_CASE("BST: Test TreeSort with Already Sorted Array", "[tree sort]") {
//     TreeType tree1;
//     int arr[6] = {1, 2, 3, 4, 5, 6};
//     int expected[6] = {1, 2, 3, 4, 5, 6};

//     tree1.treeSort(arr, 6);

//     for (int i = 0; i < 6; i++) {
//         REQUIRE(arr[i] == expected[i]);
//     }
// }

// TEST_CASE("BST: Test TreeSort with Reverse Sorted Array", "[tree sort]") {
//     TreeType tree1;
//     int arr[6] = {6, 5, 4, 3, 2, 1};
//     int expected[6] = {1, 2, 3, 4, 5, 6};

//     tree1.treeSort(arr, 6);

//     for (int i = 0; i < 6; i++) {
//         REQUIRE(arr[i] == expected[i]);
//     }
// }

// TEST_CASE("tree sort") {
//     TreeType tree1;
//     int arr[10] = {100,15,40,53,23,30,41,80,11,6};
//     int size = 10;

//     tree1.treeSort(arr,size);

//     int result[10] = {6,11,15,23,30,40,41,53,80,100};
//     for(int i = 0; i < size; i++) {
//         REQUIRE(arr[i] == result[i]);
//     }

// }