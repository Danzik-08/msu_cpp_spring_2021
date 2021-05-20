#include <cassert>
#include <sstream>
#include <string>

#include "bigint.hpp"

int main() {
  assert(BigInt("115") - BigInt("115") == 0);
  assert(BigInt("115") - BigInt("234") == -119);
  assert(BigInt("59") - BigInt("93484") == -93425);

  assert(BigInt("234") - BigInt("115") == 119);
  assert(BigInt("12115") - BigInt("12678") == -563);
  assert(BigInt("93484") - BigInt("59") == 93425);

  assert(BigInt("99") + BigInt("90") == BigInt("189"));
  assert(BigInt("59") + BigInt("93484") == 93543);

  assert(-BigInt("115") - BigInt("-115") == BigInt("0"));
  assert(-BigInt("59") - BigInt("-93484") == BigInt("93425"));
  assert(-BigInt("59") - BigInt("93484") == -BigInt("93543"));
  assert(-BigInt("99") - BigInt("90") == BigInt("-189"));

  assert(-BigInt("115") + BigInt("-12115") == -BigInt("12230"));
  assert(BigInt("115") + BigInt("-12115") == -BigInt("12000"));
  assert(BigInt("-99") + -BigInt("90") == BigInt("-189"));


  assert(BigInt("333333333333333333333333289") - BigInt("333333333333333333333333987") == -698);
  assert(BigInt("333333333333333433333333289") -
         BigInt("333333333333373333333333987") == BigInt("-39900000000698"));
  assert(BigInt("333333333333333433333333987") -
         BigInt("333333333333373333333333289") == BigInt("-39899999999302"));

  assert(BigInt("12") * BigInt("12") == BigInt("144"));
  assert(BigInt("12") * BigInt("-12") == BigInt("-144"));
  assert(-BigInt("16") * BigInt("-16") == BigInt("256"));
  assert(-BigInt("18") * BigInt("13") == BigInt("-234"));

  assert(BigInt(2432) * BigInt(42342) == BigInt("102975744"));

  assert(BigInt(10000000) * BigInt(23) == BigInt("230000000"));


  assert(BigInt("6543210000") * BigInt(5) == BigInt("32716050000"));

  assert(BigInt("6543210000") * BigInt(5)  + BigInt("2827321041") == BigInt("35543371041"));

  assert(BigInt("654321") * BigInt("54321") == BigInt("35543371041"));

  assert(BigInt("127322394872386765765776234658423424298765432345678765432345678765432345678765998787534256447657534") *
         BigInt("-842832748327467251467252782364872364872364283746823674287") ==
         BigInt("-107311483993928761808290241465833184096365338489125984564625962103600164884669283892552896005713442053260530230089239286797955867480988130578241836137628258"));

  assert(BigInt("1000000000000000000000345626") * BigInt("1000000000000000000000487578783") == BigInt("1000000000000000000000833204783000000000000168519904453158"));

  assert(BigInt("12") == BigInt("12"));
  assert(BigInt("12") != BigInt("-12"));
  assert(BigInt("12") != -BigInt("12"));
  assert(BigInt("12") != BigInt("312"));

  assert(BigInt(345) <= BigInt(1000));
  assert(-BigInt("12") == BigInt("-12"));
  assert(-BigInt("123") < BigInt("-12"));
  assert(-BigInt("12") >= -BigInt("1234"));
  assert(BigInt(21342) > BigInt(24));
  assert(BigInt(-98) <= BigInt(1));
  assert(BigInt(23143432) != BigInt(23153432));

  std::stringstream output_res;
  BigInt a = 1;
  BigInt b("123456789012345678901234567890");
  assert(a == 1);
  assert(b == std::string("123456789012345678901234567890"));
  BigInt c = a * b + 2;
  assert(c == std::string("123456789012345678901234567892"));
  BigInt d;
  d = std::move(c);
  output_res << c << a;
  assert(d == std::string("123456789012345678901234567892"));
  a = d + b;
  assert(b == std::string("123456789012345678901234567890"));
  assert(d == std::string("123456789012345678901234567892"));
  assert(a == std::string("246913578024691357802469135782"));
  BigInt cp(a);
  assert(cp == std::string("246913578024691357802469135782"));

  output_res << d << a;

  std::stringstream real_res;
  real_res <<
  "1123456789012345678901234567892246913578024691357802469135782";

  assert(output_res.str() == real_res.str());

  std::cout << "Tests passed! Program accepted?" << std::endl;

  return 0;
}
