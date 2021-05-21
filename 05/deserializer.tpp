#include <iostream>
#include <string>

Deserializer::Deserializer(std::istream& inp_) : inp(inp_) {}

template <typename ArgT>
Error Deserializer::load_arg(ArgT &&arg) {
  std::string next_var;
  inp >> next_var;
  return deserialize(arg, next_var);
}

template <typename ArgT, typename... ArgsT>
Error Deserializer::load_arg(ArgT &&arg, ArgsT &&...args) {
  Error res = load_arg(std::forward<ArgT>(arg));
  if (res != Error::NoError) {
    return res;
  }
  return load_arg(std::forward<ArgsT>(args)...);
}

template <class T>
Error Deserializer::load(T& object) {
  return object.serialize(*this);
}

template <class... ArgsT>
Error Deserializer::operator()(ArgsT &&...args) {
  return load_arg(std::forward<ArgsT>(args)...);
}

Error Deserializer::HandleError() {
  inp.clear();
  return Error::CorruptedArchive;
}

Error Deserializer::deserialize(bool& arg, const std::string &next_var) {
  if (next_var == "true") {
    arg = true;
  } else if (next_var == "false") {
    arg = false;
  } else {
    return HandleError();
  }
  return Error::NoError;
}

Error Deserializer::deserialize(uint64_t& arg, const std::string &next_var) {
  try {
    arg = std::stoull(next_var);
  } catch (const std::logic_error&) {
    return HandleError();
  }
  return Error::NoError;
}

template<typename ArgT>
Error Deserializer::deserialize(ArgT &&, const std::string&) {
  return HandleError();
}
