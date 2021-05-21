#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include "data.hpp"
#include "deserializer.hpp"
#include "serializer.hpp"

int main() {

  Data<uint64_t, bool, uint64_t> x { 1, true, 2 };

  std::stringstream stream;

  Serializer serializer(stream);
  serializer.save(x);
  assert(stream.str() == "1 true 2");
  Data<uint64_t, bool, uint64_t> y { 0, false, 0 };

  Deserializer deserializer(stream);
  const Error no_err = deserializer.load(y);

  assert(no_err == Error::NoError);

  assert(x.a == y.a);
  assert(x.b == y.b);
  assert(x.c == y.c);

  serializer.save(x);
  Data<std::string, bool, uint64_t> wrong_ser {"not_right", false, 0 };
  const Error err = deserializer.load(wrong_ser);
  assert(err == Error::CorruptedArchive);

  serializer.save(wrong_ser);
  const Error huge_err = deserializer.load(y);
  assert(huge_err == Error::CorruptedArchive);

  std::cout << "Tests passed!" << std::endl;

  return 0;
}
