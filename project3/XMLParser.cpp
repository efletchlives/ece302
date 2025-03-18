// Project 3 -- XML Parser

/** @file XMLParser.cpp */

#include <string>
#include "XMLParser.hpp"

// default constructor
XMLParser::XMLParser() : elementNameBag(), parseStack(), tokenizedInputVector()
{
}

// Then finish this function to pass the 4th~6th unit tests
// tokenizeInputString method: returns if the tokenizing worked or not
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	int i=0;
	int length = inputString.length();
	bool valid_char = false;

	// prepare containers in the class to tokenize input string by clearing
	clear();

	
	while(i < length) {

		/* part 1: checks for valid tag and stores token */

		char current_char = inputString[i]; // stores current character

		// check for beginning of tag
		if(current_char == '<') {
			valid_char = true;
			std::string token_str; // contains the characters inside the '<' and '>' otherwise known as a token
			i++;

			// exception: tag is empty
			if (inputString[i] == '>') {
				return false;
			}

			// exception: contains an open tag '<'
			if(i >= length) {
				return false;
			}

			current_char = inputString[i];
			// loop through characters after '<' to store possible valid token
			while(current_char != '>' && i < length) {
				token_str += current_char; // add character to token (add them in a 0-index fashion, storing '<' first)
				i++;

				// exception: no '>'
				if(i >= length) {
					return false;
				}
				current_char = inputString[i];
			}


			/* part 2: checks if token is valid and stores valid tokens in vector */
			bool valid = valid_token1(token_str);
			if(valid) {
				// find type of token and store type in token
				StringTokenType type = type_token(token_str);
				TokenStruct token;
				token.tokenType = type;

				// sorted by tag
				if(type == END_TAG) {
					token_str.erase(0,1); // remove '/'
					// remove everything but tag name
					if(check_tagname(token_str) == false) {
						return false;
					}
					std::string tagname = find_tagname(token_str);
					// check tag name for invalid char
					if(valid_token2(tagname) == false) {
						return false;
					}
					token_str = tagname;
					i++;
				}

				if(type == EMPTY_TAG) {
					token_str.erase(token_str.length()-1);
					// remove everything but tag name
					if(check_tagname(token_str) == false) {
						return false;
					}
					std::string tagname = find_tagname(token_str);
					// check tag name for invalid char
					if(valid_token2(tagname) == false) {
						return false;
					}
					token_str = tagname;
					i++;
				}

				if(type == START_TAG) {
					// remove everything but tag name
					if(check_tagname(token_str) == false) {
						return false;
					}
					std::string tagname = find_tagname(token_str);
					// check tag name for invalid char
					if(valid_token2(tagname) == false) {
						return false;
					}
					token_str = tagname;
					i++;
				}

				if(type == DECLARATION) {
					// remove the question marks at beginning and end from the string
					token_str.erase(token_str.length()-1);
					token_str.erase(0,1);
					i++;
				}

				token.tokenString = token_str;
				tokenizedInputVector.push_back(token);
				token_str.clear(); // reset string to take in the next tag/content
			}
			else {
				return false;
			}
		}

		// exception: open tag
		else if(current_char == '>') {
			return false;
		}

		else if(current_char != '<' && current_char != 32) { // if not a space or start of tag
			valid_char = true;
			std::string content_str;
			while(current_char != '<' && i < length) {
				content_str += current_char;
				i++;
				current_char = inputString[i];
			}

			TokenStruct token;
			token.tokenType = CONTENT; // must be content since it doesn't start with '<' and it doesn't start with a space
			token.tokenString = content_str;
			tokenizedInputVector.push_back(token);
			content_str.clear(); // reset string to take in the next tag/content

		}



		// increment if only a space
		else if(current_char == ' ') {
			i++;
		}

		else {
			i++;
		}

	} // end length while loop

	if(valid_char == false){
		return false;
	}

	// exception: a content token cannot exist alone
	if(!tokenizedInputVector.empty() && tokenizedInputVector[0].tokenType == CONTENT) {
		return false;
	}
	return true; // string successfully tokenized
} // end

// Then finish this function to pass the 7th~9th unit test
// parseTokenizedInput method: checks that the TokenizedInputVector follows the correct XML grammar and order
// involves pushing to and popping off the parseStack
bool XMLParser::parseTokenizedInput()
{
	int length = tokenizedInputVector.size();

	// exception: input vector has no items in it
	if(length == 0) {
		return false;
	}

	/* part 1: check that the input starts with a declaration or start tag */ 
	else if(tokenizedInputVector[0].tokenType != DECLARATION && tokenizedInputVector[0].tokenType != START_TAG) {
		return false;
	}

	/* part 2: loop through the vector to check order */
	for(int i = 0; i < length; i++) {
		// check for start tag
		if(tokenizedInputVector[0].tokenType == START_TAG) {
			
		}
		// check for end tag
		else if(tokenizedInputVector[0].tokenType == END_TAG) {

		}
		// check for declaration
		else if(tokenizedInputVector[0].tokenType == )
	}

	if(parseStack.isEmpty()) {
		return true;
	}
	return false;
}

// TODO, iterate through tokenizedInputVector to check validity
	// and update stack and bag accordingly, and refer to the following code structure:

	// for (int i = 0; i < tokenizedInputVector.size(); i++)
	// {
	//   if (?? == START_TAG) {?? continue;}
	// 	 else if (?? == END_TAG) {?? continue;}
	// 	 else if (?? == EMPTY_TAG) {?? continue;}
	// 	 ...
	// }

// clear method: clears all of the containers in the class
void XMLParser::clear()
{
	elementNameBag.clear();
	parseStack.clear();
	tokenizedInputVector.clear();
}

// returnTokenizedInput method: returns tokenizedInputVector
std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// containsElementName method: returns if the Bag contains the element
bool XMLParser::containsElementName(const std::string &element) const
{
	// if token and parser pass and contains the element (stack passes all items to bag)
	if(tokenizedInputVector.empty() || parseStack.size() != 0) {
		throw std::logic_error("string cannot be tokenized and/or parsed");
	}
	// if token and/or parser fail, and/or bag does not contain the element
	if(elementNameBag.isEmpty()) {
		throw std::logic_error("string cannot be tokenized and/or parsed");
	}
	return elementNameBag.contains(element);
}

// frequencyElementName method: returns number of times that the specified element exists in the Bag
int XMLParser::frequencyElementName(const std::string &element) const
{
	// if token and parser pass and contains element (stack passes all items to bag)
	if(tokenizedInputVector.empty() || parseStack.size() != 0) {
		throw std::logic_error("string cannot be tokenized and/or parsed");
	}
	// if bag does not contain the element
	if(elementNameBag.getFrequencyOf(element) == 0) {
		throw std::logic_error("string cannot be parsed");
	}
	return (elementNameBag.getFrequencyOf(element));
}
