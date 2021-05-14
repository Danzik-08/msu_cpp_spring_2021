#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "parser.hpp"

std::ostream& operator<< (std::ostream& out, std::vector<uint64_t> vec) {
  for (const uint64_t digit : vec) {
    out << ' ' << digit;
  }
  return out << std::endl;
}

int main() {
  TokenParser empty_parser("");
  empty_parser.SetStartCallback([&empty_parser](){empty_parser.GetStream() << "Empty text!" << std::endl;});
  empty_parser.SetEndCallback([&empty_parser](){empty_parser.GetStream() << "Nothing to parse. Terminating!\n" << std::endl;});
  std::ostringstream empty_res;
  empty_res << "Empty text!" << std::endl << "Nothing to parse. Terminating!\n" << std::endl;
  assert(empty_res.str() == empty_parser.Parse());



  std::ifstream text("text.txt");
  std::string data((std::istreambuf_iterator<char>(text)),
                    std::istreambuf_iterator<char>());


  TokenParser parser(data);
  std::ostringstream no_callback_res;
  no_callback_res << "\nParsing started!" << std::endl <<
                     "Found STRING token: " << "This" << std::endl <<
                     "Found STRING token: " << "program" << std::endl <<
                     "Found DIGIT token: " << 123 << std::endl <<
                     "Found STRING token: " << "works" << std::endl <<
                     "Found DIGIT token: " << 237458 << std::endl <<
                     "Found STRING token: " << "just" << std::endl <<
                     "Found STRING token: " << "fine!" << std::endl <<
                     "Found STRING token: " << "o7" << std::endl <<
                     "Found STRING token: " << "n0t," << std::endl <<
                     "Found STRING token: " << "5orry" << std::endl <<
                     "Found STRING token: " << "(((((" << std::endl <<
                     "Found STRING token: " << "123.345" << std::endl <<
                     "\nParsing finished!" << std::endl;

  assert(no_callback_res.str() == parser.Parse());


  std::vector<uint64_t> digit_tokens;
  parser.SetStringTokenCallback([&parser](const std::string& token)
                                {parser.GetStream() << token << ' ';});

  parser.SetDigitTokenCallback([&digit_tokens](uint64_t token)
                               {digit_tokens.push_back(token);});

  parser.SetEndCallback([&digit_tokens, &parser]()
                        {parser.GetStream() << "\nAll digit tokens in text:" << 
                        digit_tokens << "Finished parsing!" << std::endl;});

  std::ostringstream res;
  std::vector<uint64_t> real_digit_tokens = {123, 237458};
  res << "\nParsing started!" << std::endl <<
         "This program works just fine! o7 n0t, 5orry ((((( 123.345 " <<
         "\nAll digit tokens in text:" << real_digit_tokens <<
         "Finished parsing!" << std::endl;

  assert(res.str() == parser.Parse());

  std::cout << "Tests passed! Program accepted?" << std::endl;

  return 0;
}