#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

#include "bigint.hpp"

BigInt::BigInt(int32_t value) {
  size_t capacity = 1;
  data = new int32_t [capacity]();
  size = 0;
  sign = (value >= 0) ? 1 : -1;

  value = std::abs(value);

  while (value >= 0) {
    if (size == capacity) {
      capacity *= 2;
      Realloc(capacity);
    }

    data[size] = value % max_ten_pow;
    size++;
    value /= max_ten_pow;
    if (value == 0) {
      break;
    }
  }
  Realloc();
}

BigInt::BigInt(const std::string &data_, size_t size_) {
  if (data_.empty() && size_ <= 0) {
    throw std::runtime_error("Error: not a number!");
  }

  if (data_.empty()) {
    size = size_;
    data = new int32_t [size]();
    return;
  }

  size_t offset = !std::isdigit(data_[0]);
  size = (data_.size() - offset);
  sign = (data_[0] == '-') ? -1 : 1;

  if (size == 0 || (!std::isdigit(data_[0]) && data_[0] != '+' && data_[0] != '-')) {
    throw std::runtime_error("Error: not a number!");
  }

  size = size / MAX_DIG_AMOUNT + (size % MAX_DIG_AMOUNT != 0);

  data = new int32_t [size]();

  ReverseNumber(data_, offset);
}

BigInt::BigInt(const BigInt &other_bigint) : sign(other_bigint.sign),
                                             size(other_bigint.size) {
  data = new int32_t [size];

  for (size_t i = 0; i < size; ++i) {
    data[i] = other_bigint.data[i];
  }
}

BigInt::BigInt(BigInt &&other_bigint) : data(other_bigint.data),
                                        sign(other_bigint.sign),
                                        size(other_bigint.size) {
  other_bigint.data = nullptr;
  other_bigint.size = 0;
}

BigInt& BigInt::operator=(const BigInt &other_bigint) {
  if (data == other_bigint.data) {
    return *this;
  }

  if (data != nullptr) {
    delete [] data;
  }

  sign = other_bigint.sign;
  size = other_bigint.size;

  data = new int32_t [size];

  for (size_t i = 0; i < size; ++i) {
    data[i] = other_bigint.data[i];
  }

  return *this;
}

BigInt& BigInt::operator=(BigInt &&other_bigint) {
  if (data == other_bigint.data) {
    return *this;
  }

  if (data != nullptr) {
    delete [] data;
  }

  data = other_bigint.data;
  sign = other_bigint.sign;
  size = other_bigint.size;

  other_bigint.data = nullptr;
  other_bigint.size = 0;

  return *this;
}

BigInt::~BigInt() {
  if (data != nullptr) {
    delete [] data;
  }
  size = 0;
}

BigInt BigInt::operator+(const BigInt &other_bigint) const {
  if (sign != other_bigint.sign) {
    return *this - (-other_bigint);
  }

  BigInt res("", std::max(size, other_bigint.size));
  res.sign = sign;

  unsigned int dec = 0;
  for (size_t i = 0; i < res.size; ++i) {
    unsigned int next_part = dec + ((i < size) ? data[i]  : 0);
    next_part += (i < other_bigint.size) ?
                      other_bigint.data[i] : 0;

    res.data[i] = next_part % max_ten_pow;
    dec = next_part / max_ten_pow;
  }

  if (dec == 1) {
    res.AddExtraPart(dec);
  }

  return res;
}

BigInt BigInt::operator-(const BigInt &other_bigint) const {
  if (sign != other_bigint.sign) {
    return *this + (-other_bigint);
  }

  int comp_res = this->CompareAbs(other_bigint);

  if (comp_res == 0) {
    return BigInt("0");
  }

  bool reverse = (comp_res == 1);

  BigInt res("", std::max(size, other_bigint.size));
  res.sign = ((sign == 1) == reverse) ? -1 : 1;

  int leading_zero_counter = res.SubstractWithLeading(*this, other_bigint, reverse);

  if (leading_zero_counter != 0) {
    res.size -= leading_zero_counter;
    res.Realloc();
  }

  return res;
}

BigInt BigInt::operator*(const BigInt &other_bigint) const {
  BigInt res(0);
  BigInt cur_part(*this);

  for (size_t i = 0; i < other_bigint.size; ++i) {
    unsigned int cur_mult = other_bigint.data[i];
    int cur_part_len = MAX_DIG_AMOUNT;

    while (cur_mult >= 0) {
      res = res + cur_part * (cur_mult % 10);
      cur_mult /= 10;
      cur_part_len--;
      cur_part.MulTen();
      if (cur_mult == 0) {
        if (i != other_bigint.size - 1) {
          for (int zeros = 0; zeros < cur_part_len; ++zeros) {
            cur_part.MulTen();
          }
        }
        break;
      }
    }
  }

  res.sign = sign * other_bigint.sign;

  return res;
}

BigInt BigInt::operator-() const {
  BigInt res(*this);
  res.sign *= -1;
  return res;
}

bool BigInt::operator<(const BigInt &other_bigint) const {
  if (sign != other_bigint.sign) {
    return sign < other_bigint.sign;
  }

  return this->CompareAbs(other_bigint) * sign == 1;
}

bool BigInt::operator<=(const BigInt &other_bigint) const {
  if (sign != other_bigint.sign) {
    return sign < other_bigint.sign;
  }

  return this->CompareAbs(other_bigint) * sign != -1;
}

bool BigInt::operator>(const BigInt &other_bigint) const {
  if (sign != other_bigint.sign) {
    return sign > other_bigint.sign;
  }

  return this->CompareAbs(other_bigint) * sign == -1;
}

bool BigInt::operator>=(const BigInt &other_bigint) const {
  if (sign != other_bigint.sign) {
    return sign > other_bigint.sign;
  }

  return this->CompareAbs(other_bigint) * sign <= -1;
}

bool BigInt::operator==(const BigInt &other_bigint) const {
  if (sign != other_bigint.sign) {
    return false;
  }

  return this->CompareAbs(other_bigint) == 0;
}

bool BigInt::operator!=(const BigInt &other_bigint) const {
  if (sign != other_bigint.sign) {
    return true;
  }

  return this->CompareAbs(other_bigint) != 0;
}

std::ostream &operator<<(std::ostream &out, const BigInt &bigint) {
  if (bigint.sign < 0) {
    out << '-';
  }
  for (size_t i = bigint.size; i > 0; --i) {
    if (i != bigint.size) {
      unsigned int cur_part = bigint.data[i - 1];
      int cur_part_len = MAX_DIG_AMOUNT;
      while (cur_part > 0) {
        cur_part /= 10;
        cur_part_len--;
      }

      for (int zeros = 0; zeros < cur_part_len; ++zeros) {
        out << 0;
      }
    }
    out << bigint.data[i - 1];
  }
  return out;
}

void BigInt::ReverseNumber(const std::string &not_reversed, size_t offset) {
  size_t cur_pos = 1;
  for (size_t i = not_reversed.size(); i > offset; --i) {
    if (!std::isdigit(not_reversed[i - 1])) {
        delete [] data;
        throw std::runtime_error("Error: not a number!");
    }
    data[(not_reversed.size() - i) / MAX_DIG_AMOUNT] += (not_reversed[i - 1] -  '0') * cur_pos;

    if ((not_reversed.size() - i + 1) % MAX_DIG_AMOUNT == 0) {
      cur_pos = 1;
    } else {
      cur_pos *= 10;
    }
  }
}


void BigInt::Realloc(int32_t capacity) {
  int32_t *new_res = new int32_t [(capacity == -1) ? size : capacity]();

  for (size_t i = 0; i < size; ++i) {
    new_res[i] = data[i];
  }
  delete [] data;
  data = new_res;
}

int BigInt::SubstractWithLeading(const BigInt &lhs, const BigInt &rhs, bool reverse) {
  int dec = 0;
  int leading_zero_counter = 0;
  for (size_t i = 0; i < size; ++i) {
    int first_dig = (i < lhs.size) ? lhs.data[i]  : 0;
    int second_dig = (i < rhs.size) ?
                      rhs.data[i] : 0;

    int next_dig = dec + ((reverse) ? second_dig - first_dig :
                                      first_dig - second_dig);

    leading_zero_counter = (next_dig == 0) ? leading_zero_counter + 1 : 0;

    if (next_dig < 0) {
      dec = -1;
      next_dig += max_ten_pow;
    } else {
      dec = 0;
    }

    data[i] = next_dig % max_ten_pow;
  }
  return leading_zero_counter;
}

void BigInt::AddExtraPart(int32_t dec) {
  this->size++;
  int32_t *new_res = new int32_t [this->size];
  new_res[this->size - 1] = dec;
  for (size_t i = 0; i < this->size - 1; ++i) {
    new_res[i] = this->data[i];
  }
  delete [] this->data;
  this->data = new_res;
}

void BigInt::MulTen() {
  unsigned int dec = 0;

  for (size_t i = 0; i < size; ++i) {
    unsigned int cur_part = 0;
    cur_part = data[i] * 10 + dec;
    data[i] = cur_part % max_ten_pow;
    dec = cur_part / max_ten_pow;
  }
  if (dec != 0) {
    AddExtraPart(dec);
  }

}


BigInt BigInt::operator*(int digit) const {
  BigInt part_res("", size);

  int dec = 0;
  for (size_t i = 0; i < size; ++i) {
    int next_dig = digit * data[i];
    part_res.data[i] = next_dig % max_ten_pow + dec;
    dec = next_dig / max_ten_pow;
  }

  if (dec > 0) {
    part_res.AddExtraPart(dec);
  }

  return part_res;
}

int BigInt::CompareAbs(const BigInt &other_bigint) const {
  if (other_bigint.size > size) {
    return 1;
  }
  if (other_bigint.size < size) {
    return -1;
  }

  for (size_t i = size; i > 0; --i) {
    if (other_bigint.data[i - 1] > data[i - 1]) {
      return 1;
    }
    if (other_bigint.data[i - 1] < data[i - 1]) {
      return -1;
    }
  }
  return 0;
}
