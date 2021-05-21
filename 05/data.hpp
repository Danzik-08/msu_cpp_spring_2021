#pragma once

#include <iostream>

#include "error.hpp"

template<typename First, typename Second, typename Third>
struct Data {
  First a;
  Second b;
  Third c;

  template <class Serializer>
  Error serialize(Serializer& serializer);
};

#include "data.tpp"
