#pragma once

#include <iostream>

#include "error.hpp"

class Serializer {
  static constexpr char Separator = ' ';
 public:
  explicit Serializer(std::ostream &out_);

  template <class ArgT>
  Error save_arg(ArgT &&arg);

  template <class ArgT, class... ArgsT>
  Error save_arg(ArgT &&arg, ArgsT &&...args);

  template <class T>
  Error save(T& object);

  template <class... ArgsT>
  Error operator()(ArgsT &&...args);

 private:
  Error serialize(bool arg);
  Error serialize(uint64_t arg);

  template<typename ArgT>
  Error serialize(ArgT &&arg);

  std::ostream& out;
};

#include "serializer.tpp"
