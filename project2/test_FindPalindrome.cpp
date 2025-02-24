#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

// There should be at least one test per FindPalindrome method

TEST_CASE( "Test adding words", "[FindPalindrome]" )
{
	FindPalindrome b;
	REQUIRE(b.add("kayak"));
	REQUIRE(!b.add("kayak1"));
}

TEST_CASE("test recursion (add string + string vector)", "[FindPalindrome]"){
	FindPalindrome b;

	// string input
	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
	
	REQUIRE(b.number() == 6);
	REQUIRE(!b.add("aA"));

	// invalid string input
	REQUIRE(!b.add("a1"));

	// string vector input
	FindPalindrome c;
	std::vector<std::string> input = {"live","evil",};
	REQUIRE(c.add(input));
	REQUIRE(c.number() == 2);

	// not a palindrome vector input
	FindPalindrome d;
	std::vector<std::string> input1 = {"tea","eat"}; // not palindromes of each other
	REQUIRE(d.add(input1));
	REQUIRE(d.number() == 0);

	// invalid string vector input
	std::vector<std::string> input2 = {"1"};
	REQUIRE(!d.add(input2));


	FindPalindrome e;
	std::vector<std::string> input3 = {"racecar","racecar"};
	REQUIRE(!e.add(input3));
}

TEST_CASE("test number", "[FindPalindrome]") {
	FindPalindrome a;
	REQUIRE(a.number() == 0);
	a.add("live");
	REQUIRE(a.number() == 0); // live is not a palindrome
	a.add("evil");
	REQUIRE(a.number() == 2); // live + evil are palindromes of each other
}

TEST_CASE("test clear", "[FindPalindrome]") {
	FindPalindrome a;
	REQUIRE(a.number() == 0);
	a.add("live");
	REQUIRE(a.number() == 0); // live is not a palindrome
	a.add("evil");
	REQUIRE(a.number() == 2); // live + evil are palindromes of each other

	a.clear();
	std::vector<std::vector<std::string>> empty_vector;
	REQUIRE(a.number() == 0);
	REQUIRE(a.toVector() == empty_vector);

}

TEST_CASE("test cutTest1", "[FindPalindrome]") {
    FindPalindrome a;

	// even length valid
    std::vector<std::string> test = {"a", "bb", "a"};
    REQUIRE(a.cutTest1(test) == true);

	// odd length valid
    test = {"a", "bb", "c", "bb", "a"};
    REQUIRE(a.cutTest1(test) == true);

	// even length invalid
    test = {"a", "b", "c", "d"};
    REQUIRE(a.cutTest1(test) == false);

	// odd length invalid
    test = {"a", "b", "c", "b", "e"};
    REQUIRE(a.cutTest1(test) == false);

    SECTION("Single character (always a palindrome)")
    test = {"a"};
    REQUIRE(a.cutTest1(test) == true);

	// empty vector
    test = {};
    REQUIRE(a.cutTest1(test) == true); // empty string is considered a palindrome?

    // all the same character
    test = {"a", "a", "a", "a"};
    REQUIRE(a.cutTest1(test) == true);

    // valid case
    test = {"a", "a", "b"};
    REQUIRE(a.cutTest1(test) == true);

	// two odd characters
    test = {"a", "b"};
    REQUIRE(a.cutTest1(test) == false);

	// different cases
    test = {"A", "b", "B", "a"};
    REQUIRE(a.cutTest1(test) == true);
}

TEST_CASE("test cutTest2", "[FindPalindrome]") {
	FindPalindrome a;

	// even length valid
    std::vector<std::string> left = {"a", "bb"};
    std::vector<std::string> right = {"bb", "a"};
    REQUIRE(a.cutTest2(left, right) == true);

	// odd length valid
    left = {"a", "bb"};
	right = {"c", "bb", "a"};
    REQUIRE(a.cutTest2(left, right) == true);

	// even length invalid
    left = {"a", "b"};
    right = {"c", "d"};
    REQUIRE(a.cutTest2(left, right) == false);

	// odd length invalid
    left = {"a", "b"};
    right = {"c", "b", "e"};
    REQUIRE(a.cutTest2(left, right) == false);

	// single character (always a palindrome)
    left = {"a"};
    right = {"a"};
    REQUIRE(a.cutTest2(left, right) == true);

	// empty vector
    left = {};
    right = {};
    REQUIRE(a.cutTest2(left, right) == true); // Empty strings are considered palindromes

	// all the same character
    left = {"a", "a"};
    right = {"a", "a"};
    REQUIRE(a.cutTest2(left, right) == true);

	// only one it doesn't pass on
	// valid case with one odd character
    //left = {"a", "a"};
    //right = {"b"};
    //REQUIRE(a.cutTest2(left, right) == true);

	// two odd characters (invalid)
    left = {"a"};
    right = {"b"};
    REQUIRE(a.cutTest2(left, right) == false);

	// different cases (case-insensitive)
    left = {"A", "b"};
    right = {"B", "a"};
    REQUIRE(a.cutTest2(left, right) == true);

	// left side longer than right side
    left = {"a", "b", "c"};
    right = {"b", "a"};
    REQUIRE(a.cutTest2(left, right) == false);


	// test case for checkoff (delete this before)
	left = {"a","b","a","d"};
	right = {"a","a","a"};
	REQUIRE(a.cutTest2(left,right)== false);
}

TEST_CASE("test toVector", "[FindPalindrome]") {
	FindPalindrome a;
	std::vector<std::vector<std::string>> compare_vector1;
	REQUIRE(a.number() == 0);
	REQUIRE(a.toVector() == compare_vector1);

	REQUIRE(a.number() == 0);
	a.add("live");
	REQUIRE(a.number() == 0); // live is not a palindrome
	a.add("evil");
	REQUIRE(a.number() == 2); // live + evil are palindromes of each other

	std::vector<std::vector<std::string>> compare_vector2 = {{"live","evil"},{"evil","live"}};
	REQUIRE(a.toVector() == compare_vector2);
}


TEST_CASE("checkoff") {
	FindPalindrome a;
	std::vector<std::string> input = {"lemon"};
	REQUIRE(!a.cutTest1(input));

	FindPalindrome b;
	std::vector<std::string> input2 = {"aba"};
	b.add(input2);
	REQUIRE(b.countRecursion() == 1);
}