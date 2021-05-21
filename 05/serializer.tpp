#include <iostream>
#include <sstream>
#include <type_traits>

Serializer::Serializer(std::ostream &out_) : out(out_) {}

template <class ArgT>
Error Serializer::save_arg(ArgT &&arg) {
  return serialize(arg);
}

template <class ArgT, class... ArgsT>
Error Serializer::save_arg(ArgT &&arg, ArgsT &&...args) {
  Error res = serialize(std::forward<ArgT>(arg));
  if (res != Error::NoError) {
    return res;
  }
  out << Separator;
  return save_arg(std::forward<ArgsT>(args)...);
}

template <class T>
Error Serializer::save(T& object) {
  return object.serialize(*this);
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT &&...args) {
  return save_arg(std::forward<ArgsT>(args)...);
}

Error Serializer::serialize(bool arg) {
  std::ostringstream next_var;
  next_var << arg;
  if (next_var.str() == "1") {
    out << "true";
  } else {
    out << "false";
  }
  return Error::NoError;
}

Error Serializer::serialize(uint64_t arg) {
  out << arg;
  return Error::NoError;
}

template<typename ArgT>
Error Serializer::serialize(ArgT &&arg) {
  out << arg;
  return Error::NoError;
}
