#include <iostream>

class Row {
 public:
  Row(size_t cols_ = 0);
  Row(const Row& other_row);
  Row& operator=(const Row& other_row);
  ~Row();
  const int& operator[](size_t i) const;
  int& operator[](size_t i);
  Row& operator*=(int num);
  Row operator+(const Row& rhs) const;
  bool operator==(const Row& rhs) const;
  bool operator!=(const Row& rhs) const;
 private:
  friend std::ostream& operator<<(std::ostream& out, const Row& data);
  size_t cols;
  int* row;
};

class Matrix {
 public:
  Matrix(size_t cols_, size_t rows_);
  Matrix(const Matrix& other_matrix);
  Matrix& operator=(const Matrix& other_matrix);
  ~Matrix();
  size_t GetCols() const;
  size_t GetRows() const;
  const Row& operator[](size_t i) const;
  Row& operator[](size_t i);
  Matrix& operator*=(int num);
  Matrix operator+(const Matrix& rhs) const;
  bool operator==(const Matrix& rhs) const;
  bool operator!=(const Matrix& rhs) const;
 private:
  friend std::ostream& operator<<(std::ostream& out, const Matrix& data);
  size_t cols;
  size_t rows;
  Row* matrix;
};
