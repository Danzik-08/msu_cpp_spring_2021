#include <cassert>
#include <iostream>
#include <sstream>


#include "matrix.hpp"

int main() {
  const size_t rows = 5;

  const size_t cols = 3;

  Matrix first(cols, rows);

  assert(first.GetRows() == 5);
  assert(first.GetCols() == 3);

  Matrix test_1(first);
  assert(first == test_1);

  assert(first.GetRows() == 5);
  assert(first.GetCols() == 3);

  first[4][0] = 10;
  assert(first[4][0] == 10);
  assert(test_1[4][0] == 0);

  Matrix test_2 = test_1;
  assert(test_2[1] == test_1[1]);

  assert(test_2.GetRows() == 5);
  assert(test_2.GetCols() == 3);

  test_2[4][0] = 7;
  assert(test_2[4][0] == 7);
  assert(test_1[4][0] == 0);

  double x = first[4][1];
  assert(x == 0);

  first[1][2] = 5;
  double y = first[1][2];
  assert(y == 5);

  std::stringstream errc;
  Matrix except_check(cols + 1, rows);
  try {
    except_check + first;
  } catch (const std::out_of_range  & e) {
    errc << e.what() << std::endl;
  }
  try {
    except_check[10][0];
  } catch (const std::out_of_range  & e) {
    errc << e.what() << std::endl;
  }
  try {
    except_check[0][10];
  } catch (const std::out_of_range  & e) {
    errc << e.what() << std::endl;
  }
  try {
    std::cerr << (except_check == first);
  } catch (const std::out_of_range  & e) {
    errc << e.what() << std::endl;
  }
  try {
    Matrix row_diff(cols + 1, rows + 3);
    std::cerr << (except_check != row_diff);
  } catch (const std::out_of_range  & e) {
    errc << e.what() << std::endl;
  }

  std::stringstream real_errc;
  real_errc << "Wrong dims" << std::endl <<
               "Too big row" << std::endl <<
               "Too big col" << std::endl <<
               "Wrong dims" << std::endl <<
               "Wrong dims" << std::endl;
  assert(errc.str() == real_errc.str());

  first *= 3;
  double z = first[1][2];
  double new_x = first[4][1];
  assert(x == 0);
  assert(y == 5);
  assert(new_x == 0);
  assert(z == 15);

  Matrix second(cols, rows);
  assert(first != second);

  Matrix third = second + first;
  assert(third == first);

  std::stringstream res;
  res << third << std::endl;
  std::stringstream real_res;
  real_res << "   0   0   0" << std::endl <<
              "   0   0  15" << std::endl <<
              "   0   0   0" << std::endl <<
              "   0   0   0" << std::endl <<
              "  30   0   0" << std::endl;
  assert(res.str() == real_res.str());

  first = except_check;
  assert(first.GetRows() == 5);
  assert(first.GetCols() == 4);


  std::cout << "Tests passed! Program accepted?" << std::endl;

  return 0;
}
