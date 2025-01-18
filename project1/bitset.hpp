#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <string>

// this base class is an interface
class Bitset
{
public:
  virtual ~Bitset() {}; // virtual destructor, no need to comment

  // gets the size of the bitset that returns the number of bits in the bitset
  virtual intmax_t size() const = 0;

  // checks whether the bitset is in a valid state and returns true if the bitset is valid
  virtual bool good() const = 0;

  // sets the bit at the specified index to 1
  virtual void set(intmax_t index) = 0;

  // rests the bit at the specified index to 0
  virtual void reset(intmax_t index) = 0;

  // toggles the bit at the specified index (0 becomes 1, and 1 becomes 0)
  /* index must be in the range from 0 to N-1 */
  virtual void toggle(intmax_t index) = 0;

  // checks the value of the bit at the specified index
  /* index must be in the range from 0 to N-1 
     returns true if the bit is set to 1, false if set to 0 
     if invalid, returns false and bitset is invalid */
  virtual bool test(intmax_t index) = 0;

  // takes a bit array to a string of the bitset
  // returns a string of '0' and '1' characters to represent the bits from most to least significant bit
  virtual std::string asString() const = 0;
};

#endif
