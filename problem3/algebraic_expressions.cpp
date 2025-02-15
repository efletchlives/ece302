#include <string>
#include <iostream>
#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch)
{
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}
// the end of expression is where the first postfix ends. ex given) "ab+" returns 0 because the first postfix is at index 0
int endPost(std::string s, int last)
{
  int first = 0;

  // invalid: the end of the expression is before index 0
  if ((first > last))
  {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch))
  {
    return last;
  }
  else
  {
    if (isoperator(ch))
    {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1)
      {
        return endPost(s, lastEnd - 1);
      }
      else
      {
        return -1;
      }
    }
    else
    {
      return -1;
    }
  }
}

bool isPost(std::string s)
{
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}


// global variable to check for the first test to ensure it doesn't check for the postfix past the first iteration
bool firstcall = true;

// referenced the textbook problem and set up similarly to the endPost function
// convert postfix to prefix
void convert(const std::string &postfix, std::string &prefix)
{
  // check if the input postfix is invalid, ensures that it only steps into this check on the first call
  if(!isPost(postfix) && firstcall) {
    throw std::invalid_argument("invalid input postfix");
    firstcall = false;
  }

  // store the last character of the postfix
  int last = postfix.length()-1;

  // store the operator as a character
  char ch = postfix[last];

  // uses a similar structure to endPost for recursion
  if(isalpha(ch)) {
    prefix = std::string(1,ch); // stores the operator as the first character in the string
  }
  else if(isoperator(ch)) {
    std::string left,right;

    // find the end of first postfix
    int end = endPost(postfix,last-1);
    // if there is only one character in the string
    if(end == -1)
      throw std::invalid_argument("invalid postfix");

    std::string substr1 = postfix.substr(end,last-end); // stores the second value in substr1
    convert(substr1,right); // combines substr1 and right, so that the second postfix is stored in the string

    std::string substr2 = postfix.substr(0,end); // stores the first value in substr2
    convert(substr2,left); // combines substr2 and left, so that the first postfix is stored in the string

    // store into prefix parameter
    prefix = ch + left + right; // brings substrings together and organizes them as a prefix from a postfix ex) "+ab"
  }
  else {
    throw std::invalid_argument("invalid character in postfix expression"); // if the character in the operator's place in not a listed operator
  }

  // if the postfix is the length of the prefix, set firstcall to true to reset the function for its next use
  if(postfix.length() == prefix.length()) {
    firstcall = true;
  }
}