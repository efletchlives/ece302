// Project 3 -- XML Parser

/** @file XMLParse.hpp  */

#ifndef XMLPARSE_HPP
#define XMLPARSE_HPP

#include <string>
#include "Bag.hpp"
#include "Stack.hpp"

/** enum definition for possible string token types. */
enum StringTokenType
{
	START_TAG = 1,
	END_TAG,
	EMPTY_TAG,
	CONTENT,
	DECLARATION
};

/** TokenStruct definition. Used to store tokens and their corresponding types. */
struct TokenStruct
{
	StringTokenType tokenType;
	std::string tokenString;
};

class XMLParser
{
private:
	/** Bag to store the XML element names. Uses your Bag implementation. */
	// has to declared mutable so that i can alter it within the const function getFrequencyof 
	mutable Bag<std::string> elementNameBag;
	/** Stack to store XML tag names while parsing. Uses your Stack implementation. */
	Stack<std::string> parseStack;
	/** Vector to store the tokenized input string and the token types */
	std::vector<TokenStruct> tokenizedInputVector;

	/** private members add below */

	// flag
	bool token_flag = false;
	bool parse_flag = false;

public:
	/** The class constructor.
		@post  Creates an instance of the class that can be used to tokenize and parse an input string . */
	XMLParser();

	// no custom destructor or copy, should not need dynamic memory

	/** Scans and tokenizes the input string into XML markup and content. Returns true if all tokens
			in the input string are valid. Valid markup (tokens) are the characters included in a '<' '>' character
		delimiter pair. The delimiter pairs may not be nested, and the first delimiter in the input string
		must be '<', and the final delimiter must be '>'. If the input string is non-valid (i.e., the function
		returns false, the internal data structure should be cleared on exit).
		@post  If successful, the input string is tokenized, the tokens are stored internally.
		@param inputString  The input string.
		@return  true if tokenization was successful, or false if not. */
	bool tokenizeInputString(const std::string &inputString);

	/** Parses a valid tokenized string (stored internally after a successful call to tokenizeInputString)
			and returns true if the tokenized input is valid XML.  Valid XML satisfies the BPG discussed
		in the Project Description, where open braces are replaced with a start tag,
		and the closed brace is replaced by the corresponding end tag. For tag matching, the start tag
		has all white space and attributes removed. For example, the start tag with attributes
		"<note date="02/22/2017">" matches with the end tag "</note>". To be a valid XML file, the tokenized string must also follow the other
			constraints noted in the Project Description (e.g., must have one parent element).	If the tokenized
		data is empty (e.g., we just called clear()), this method should also return false.
		@pre  A successfully tokenized input string is stored internally.
		@post If successful, the tokenized input string is determined to be valid XML.
		@param None.
		@return True if the tokenized string is valid XML, or false if not. */
	bool parseTokenizedInput();

	/** Empties and then fills a given vector with the tokenized input string. This
			method returns a vector whether or not the tokenized input string was valid XML or not.
			The vector elements are of type TokenStruct. This data type has two fields,
			"tokenString" and "tokenType". The types for "tokenType" is an enum
			with the possible values: START_TAG, END_TAG, EMPTY_TAG, CONTENT, and DECLARATION.
			These values are available to the application programmer through including the
			"XMLParser.hpp" header file. The token strings corresponding to markup do not
			include the '<', '>', "<?", "?>", "</", and "/>" delimiters.
		@return  A vector containing all the tokenized input as a vector of type "TokenStruct". */
	std::vector<TokenStruct> returnTokenizedInput() const;

	/** Determines if an element name is contained in valid XML input string.
			Only finds element names if both the tokenizeInputString() and
		parseTokenizedInput() methods have returned true; throws a logic_error otherwise.
		@pre  A valid XML tokenized input string is stored internally.
		@param A string containing the element name (case sensitive!).
		@return True if the element name is in the valid XML, or false if not.
		@throws std::logic_error if input has not been both tokenized and parsed */
	bool containsElementName(const std::string &element) const;

	/** Returns the number of times an element name is contained in valid XML input string.
			Only returns non-zero frequencies if both the tokenizeInputString() and
		parseTokenizedInput() methods have returned true; throws a logic_error otherwise.
		@pre  A valid XML tokenized input string is stored internally.
		@param A string containing the element name (case sensitive!).
		@return An int representing the frequency of the element name in the valid XML string.
		@throws std::logic_error if input has not been both tokenized and parsed */
	int frequencyElementName(const std::string &element) const;

	/** Clears the internal data structures for a instance of the class.
		@post  The class instance can be used to tokenize a new input string. */
	void clear();


	/* helper functions below */

	/** returns true/false for if the string is a valid token
	 * @param a string for storing the token to be tested
	 * @return bool: true if string is valid token, false if string contains invalid characters */
	bool valid_token1(std::string token_str) {
		for(int i=1;i<token_str.length();i++) {
			char current_char = token_str[i];
			if(current_char == '<') {
				return false;
			}
		}
		// exception: tag name represents both end and empty tag
		if(token_str[0] == '/' && token_str[token_str.length()-1] == '/') {
			return false;
		}
		return true; // token is valid
	}

	// add javadoc here!!!
	StringTokenType type_token(std::string token_str) {
		// check for declaration
		if(token_str[0] == '?' || token_str[token_str.length()-2] == '?') {
			return DECLARATION;
		}
		// check for end tag
		else if(token_str[0] == '/') {
			return END_TAG;
		}
		// check for empty tag
		else if(token_str[token_str.length()-1] == '/') {
			return EMPTY_TAG;
		}
		// start tag if else
		else {
			return START_TAG;
		}
	}

	// add javadoc here!!!
	bool check_tagname(std::string token_str) {
		if(token_str[0] == ' ') {
			return false;
		}
		return true;
	}

	// add javadoc here!!!
	std::string find_tagname(std::string token_str) {
		std::string tagname;

		bool space_found = false;
		int i=0;
		int tagname_end = -4;

		while (i < token_str.length() && space_found == false) {
			if(std::isspace(token_str[i])) {
				space_found = true;
				tagname_end = i;
			}
			i++; // increment if no space found
		}

		if (space_found == true) {
			tagname = token_str.substr(0,tagname_end);
		}
		else {
			tagname = token_str; // tag name is the entire string
		}
		return tagname;
	}

	// add javadoc here!
	bool valid_token2(std::string token_str) {
		// exception: first char is number
		if(token_str[0] >= '0' && token_str[0] <= '9') {
			return false;
		}

		// exception: first char cannot be - or . or a space
		if(token_str[0] == 45 || token_str[0] == 46 || token_str[0] == ' ') {
			return false;
		}
	
		for(char c: token_str) {
			// exception: any char is '?' or '/' after removing identification for end, empty, and declaration tags 
			if(c == 47 || c == 63) {
				return false;
			}

			// exception: special characters are not allowed
			if ((c >= 33 && c <= 44) ||   // !"#$%&'()*+,
			(c >= 58 && c <= 62) ||   // :;<=>
			(c == 64)			 ||	  // @
			(c >= 91 && c <= 94) ||   // [\]^
			(c == 96)			 ||	  // `
			(c >= 123 && c <= 126)) { // {|}~
				return false; // is invalid character
			}
		}
		return true; // token is valid
	}

	// this function is used to identify between the different tags since the getfrequencyof function doesn't know and can mess up empty tags
	void change_bag() const {
		// clear the bag
		elementNameBag.clear();
		int length = tokenizedInputVector.size();

		// loop through and add '1' or '2' according to the token type
		for(int i = 0; i < length; i++) {
			// start and end tag (identifier = '1')
			if(tokenizedInputVector[i].tokenType == START_TAG || tokenizedInputVector[i].tokenType == END_TAG) {
				elementNameBag.add(tokenizedInputVector[i].tokenString + '1');
			} 
			// declarations and empty tags
			else if(tokenizedInputVector[i].tokenType == DECLARATION || tokenizedInputVector[i].tokenType == EMPTY_TAG) {
				elementNameBag.add(tokenizedInputVector[i].tokenString + '2');
			}

			// content (not included in getFrequencyat count)
			else {
				elementNameBag.add(tokenizedInputVector[i].tokenString + '3');
			}
		}
	}

	// revert back from the different tags
	void change_back() const {
		// clear the bag
		elementNameBag.clear();
		int length = tokenizedInputVector.size();

		// loop through to add the original data to the bag
		for(int i = 0;i < length; i++) {
			elementNameBag.add(tokenizedInputVector[i].tokenString);
		}
	}

}; // end XMLParser

#endif
