#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <string>

#include "algebraic_expressions.hpp"

/* Provided test cases */
TEST_CASE("Test endPost", "[postpre]")
{
  std::string postfix_valid = "ab+";
  int test_idx_valid = 0;
  std::string postfix_invalid = "+";
  int test_idx_invalid = -1;
  REQUIRE(endPost(postfix_valid, postfix_valid.length() - 1) == test_idx_valid);
  REQUIRE(endPost(postfix_invalid, postfix_invalid.length() - 1) == test_idx_invalid);
}

TEST_CASE("Test isPost", "[postpre]")
{
  std::string postfix_valid = "ab+";
  std::string postfix_invalid = "+ab";

  REQUIRE(isPost(postfix_valid));
  REQUIRE_FALSE(isPost(postfix_invalid));
}

TEST_CASE("Postpre: Test expression ab+", "[postpre]")
{
  std::string postfix = "ab+";
  std::string prefix = "";
  std::string test = "+ab";

  REQUIRE_NOTHROW(convert(postfix, prefix));

  REQUIRE(prefix == test);
}

TEST_CASE("Postpre: Test other operators", "[postpre]")
{
  std::string postfix = "ab-";
  std::string prefix = "";
  std::string test = "-ab";

  REQUIRE_NOTHROW(convert(postfix, prefix));
  REQUIRE(prefix == test);

  postfix = "ab*";
  prefix = "";
  test = "*ab";
  REQUIRE_NOTHROW(convert(postfix, prefix));
  REQUIRE(prefix == test);

  postfix = "ab/";
  prefix = "";
  test = "/ab";
  REQUIRE_NOTHROW(convert(postfix, prefix));
  REQUIRE(prefix == test);
}

/* TODO: Your test cases here */


TEST_CASE("input prefix invalid","[postpre]") {
  std::string input = "+ab";
  std::string prefix = "";

  REQUIRE_THROWS_AS(convert(input,prefix),std::invalid_argument);
}


TEST_CASE("input string longer than postfix","[postpre]") {
  std::string postfix = "ab*af";
  std::string prefix = "";
  std::string test = "*ab";

  REQUIRE_THROWS_AS(convert(postfix,prefix),std::invalid_argument);
  REQUIRE_FALSE(prefix == test); // this doesn't work since the string is longer than the postfix
}

TEST_CASE("invalid operator","[postpre]") {
  std::string postfix = "dt&";
  std::string prefix = "";
  std::string test = "&dt";

  REQUIRE_THROWS_AS(convert(postfix,prefix),std::invalid_argument);
}

TEST_CASE("postfix pass tests","[postpre]") {
  // addition operator
  std::string postfix = "gf+";
  std::string prefix = "";
  std::string test = "+gf";

  convert(postfix,prefix);
  REQUIRE(prefix == test);

  // subtraction operator
  postfix = "gf-";
  prefix = "";
  test = "-gf";

  convert(postfix,prefix);
  REQUIRE(prefix == test);

  // multiplication operator
  postfix = "gf*";
  prefix = "";
  test = "*gf";

  convert(postfix,prefix);
  REQUIRE(prefix == test);

  postfix = "gf/";
  prefix = "";
  test = "/gf";

  convert(postfix,prefix);
  REQUIRE(prefix == test);
}