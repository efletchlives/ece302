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


// referenced the textbook problem and set up similarly to the endPost function
// convert postfix to prefix
void convert(const std::string &postfix, std::string &prefix)
{
  std::cout << "Checking isPost: " << postfix << " -> " << (isPost(postfix) ? "Valid" : "Invalid") << std::endl;
  // check if the input postfix is invalid
  if(!isPost(postfix))
    throw std::invalid_argument("invalid input postfix");

  // store how many characters in postfix
  int num_char = postfix.length();

  // store the last and first characters of the postfix to get the bounds of the postfix
  int last = postfix.length()-1;
  int first = endPost(postfix,last);

  // store the operator as a character
  char ch = postfix[last];

  if(isalpha(ch)) {
    prefix = std::string(1,ch); // stores the operator as the first character in the string
  }
  else if(isoperator(ch)) {
    std::string left,right;
    std::string substr1 = postfix.substr(first,last-first); // stores the second value in substr1
    std::string substr2 = postfix.substr(0,first); // stores the second 

    convert(substr1,right); // combines substr1 and right, so that the second postfix is stored in the string
    convert(substr2,left); // combines substr2 and left, so that the first postfix is stored in the string

    // store into prefix parameter
    prefix += left + right; // brings substrings together and organizes them as a prefix from a postfix ex) "+ab"
  }
  else {
    throw std::invalid_argument("invalid character in postfix expression"); // if the character in the operator's place in not a listed operator
  }
}