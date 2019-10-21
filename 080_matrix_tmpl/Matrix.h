#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>

class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() :
      numRows(0),
      numColumns(0),
      rows(std::vector<std::vector<T> >(0, std::vector<T>(0))) {}

  Matrix(int r, int c) :
      numRows(r),
      numColumns(c),
      rows(std::vector<std::vector<T> >(r, std::vector<T>(c))) {}

  Matrix(const Matrix & rhs) :
      numRows(rhs.getRows()),
      numColumns(rhs.getColumns()),
      rows(
          std::vector<std::vector<T> >(rhs.getRows(), std::vector<T>(rhs.getColumns()))) {
    for (int i = 0; i < numRows; i++) {
      rows[i] = rhs.rows[i];
    }

    // rows = rhs.rows;
  }

  ~Matrix() {}

  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      /*
      for (int i = 0; i < rhs.getRows(); i++) {
        rows[i] = rhs.rows[i];
      }
      */
      rows = rhs.rows;
      numRows = rhs.getRows();
      numColumns = rhs.getColumns();
    }
    return *this;
  }

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }

  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }

  bool operator==(const Matrix & rhs) const {
    if (rows == rhs.rows) {
      return true;
    }
    return false;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.getRows() && numColumns == rhs.getColumns());
    Matrix ans(rhs.getRows(), rhs.getColumns());
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        ans[i][j] = rows[i][j] + rhs[i][j];
      }
    }
    return ans;
  }

  template<typename X>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<X> & x);
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    if (i < rhs.getRows() - 1) {
      s << "{";
      for (int j = 0; j < rhs.getColumns(); j++) {
        if (j < rhs.getColumns() - 1) {
          s << rhs[i][j] << ", ";
        }
        else {
          s << rhs[i][j];
        }
      }
      s << "}";
      s << ",\n";
    }
    else {
      s << "{";
      for (int j = 0; j < rhs.getColumns(); j++) {
        if (j < rhs.getColumns() - 1) {
          s << rhs[i][j] << ", ";
        }
        else {
          s << rhs[i][j];
        }
      }
      s << "}";
    }
  }
  s << " ]";
  return s;
}

#endif
