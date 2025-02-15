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
	REQUIRE(!b.add("kayaaa")); // THIS RETURNS FALSE
}

TEST_CASE("test recursion (add string + string vector)", "[FindPalindrome]"){
	FindPalindrome b;

	// string input
	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
	REQUIRE(b.number() == 6);

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
}

TEST_CASE("test default constructor", "[FindPalindrome]") {
	FindPalindrome a;
	std::vector<std::vector<std::string>> compare_vector;
	REQUIRE(a.toVector() == compare_vector);
	REQUIRE(a.number() == 0);
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

    // Test even-length palindrome
    std::vector<std::string> even_palindrome = {"baab"};
    REQUIRE(a.cutTest1(even_palindrome) == true);  // Even length, all characters even counts

    // test odd-length palindrome
    std::vector<std::string> odd_palindrome = {"abcba"};
    REQUIRE(a.cutTest1(odd_palindrome) == true);  // Odd length, one character with odd count

    // test invalid palindrome (multiple odd counts)
    //std::vector<std::string> invalid_palindrome = {"aabbb"};
    //REQUIRE(a.cutTest1(invalid_palindrome) == false);  // More than one character with odd counts
}

TEST_CASE("test cutTest2", "[FindPalindrome]") {
	
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

