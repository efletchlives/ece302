#ifndef _ABSTRACT_OPERATOR_HPP
#define _ABSTRACT_OPERATOR_HPP

#include <cstdlib>

// AbstractOperator is an interface.
template <typename T>
class AbstractOperator
{
  public:
    virtual ~AbstractOperator() {};
    virtual T call(T arg1, T arg2) const = 0;

  private:
};

#endif