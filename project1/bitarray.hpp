#ifndef BITARRAY_HPP
#define BITARRAY_HPP
#include <stdint.h>
#include <string>
#include <vector>

#include "bitset.hpp"

class BitArray : public Bitset
{
public:
  // default constructor
  BitArray();

  // other constructors
  BitArray(intmax_t size);
  BitArray(const std::string &value);

  // destructor
  ~BitArray();

  BitArray(const BitArray &) = delete;
  BitArray &operator=(const BitArray &) = delete;

  // member functions
  intmax_t size() const;
  bool good() const;
  void set(intmax_t index);
  void reset(intmax_t index);
  void toggle(intmax_t index);
  bool test(intmax_t index);
  std::string asString() const;
  //intmax_t countOnes();

private:
  uint8_t* bitdata; // holds the bit data in an array
  intmax_t bitsize; // # of bits in the bit array
  bool bitsetstate; // if the bit array is in a valid state
};

#endif