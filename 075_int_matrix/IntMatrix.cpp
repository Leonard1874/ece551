#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}

IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray[c];
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(new IntArray *[rhs.numRows]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray[numColumns];
    for (int j = 0; j < numColumns; j++) {
      rows[i][j] = rhs.rows[i][j];
    }
  }
}
IntMatrix::~IntMatrix() {
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
}
int IntMatrix::getRows() const {
}
int IntMatrix::getColumns() const {
}
const IntArray & IntMatrix::operator[](int index) const {
}
IntArray & IntMatrix::operator[](int index) {
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
}