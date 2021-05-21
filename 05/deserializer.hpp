#pragma once

#include <iostream>
#include <string>

#include "error.hpp"

class Deserializer {
  static constexpr char Separator = ' ';
public:
  explicit Deserializer(std::istream& inp_);

  template <typename ArgT>
  Error load_arg(ArgT &&arg);

  template <typename ArgT, typename... ArgsT>
  Error load_arg(ArgT &&arg, ArgsT &&...args);

  template <class T>
  Error load(T& object);

  template <class... ArgsT>
  Error operator()(ArgsT &&...args);

private:
  Error HandleError();

  Error deserialize(bool &arg, const std::string& next_var);
  Error deserialize(uint64_t &arg, const std::string& next_var);

  template<typename ArgT>
  Error deserialize(ArgT &&arg, const std::string& next_var);

  std::istream& inp;
};

#include "deserializer.tpp"
