#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>

class IntMatrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}

  IntMatrix(int r, int c) :
      numRows(r),
      numColumns(c),
      rows(std::vector<std::vector<T> >(r, std::vector<T>(c))) {}

  IntMatrix(const IntMatrix & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.Columns),
      rows(std::vector<std::vector<T> >(rhs.numRows, std::vector<T>(rhs.numColumns))) {
    /*
    for (int i = 0; i < numRows; i++) {
      rows[i] = rhs.rows[i];
    }
    */
    rows = rhs.rows;
  }

  ~IntMatrix() {}

  IntMatrix & operator=(const IntMatrix & rhs) {
    if (this != &rhs) {
      /*
      for (int i = 0; i < rhs.numRows; i++) {
        rows[i] = rhs.rows[i];
      }
    }
      */
      rows = rhs.rows;
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      return *this;
    }
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
  bool operator==(const IntMatrix & rhs) const {
    if (rows == rhs.rows) {
      return true;
    }
    return false;
  }
  IntMatrix operator+(const IntMatrix & rhs) const {
    assert(numRows == rhs.getRows() && numColumns == rhs.getColumns());
    IntMatrix ans(rhs.getRows(), rhs.getColumns());
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        ans[i][j] = rows[i][j] + rhs[i][j];
      }
    }
    return ans;
  }

  template<typename X>
  friend std::ostream & operator<<(std::ostream & s, const IntMatrix<X> & x);
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const IntMatrix<T> & rhs) {
  s << "[";
  for (size_t i = 0; i < rhs.size(); i++) {
    if (i > 0) {
      s << ", ";
    }
    s << rhs[i];
  }
  s << "]";
  return s;
}

#endif
