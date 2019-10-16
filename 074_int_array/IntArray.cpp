#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}

IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

IntArray::IntArray(const IntArray & rhs) {
  data = new int[rhs.numElements];
  numElements = rhs.numElements;
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    numElements = rhs.numElements;
    delete[] data;
    data = temp;
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index >= 0 && index < numElements);
  return data[index];
}

int & IntArray::operator[](int index) {
  assert(index >= 0 && index < numElements);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (rhs.numElements != numElements) {
    return false;
  }
  else {
    for (int i = 0; i < numElements; i++) {
      if (data[i] != rhs.data[i]) {
        return false;
      }
    }
    return true;
  }
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (rhs.numElements != numElements) {
    return true;
  }
  else {
    for (int i = 0; i < numElements; i++) {
      if (data[i] != rhs.data[i]) {
        return true;
      }
    }
    return false;
  }
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  /*
  char arr[3 * 16 * rhs.size()];
  snprintf(arr, 1, "{");
  for (int i = 0; i < rhs.size(); i++) {
    if (i <= rhs.size() - 1) {
      snprintf(arr, 3, "%d, ", rhs[i]);
    }
    else {
      snprintf(arr, 1, "%d}", rhs[i]);
    }
  }
  s.write(arr, 3 * rhs.size());
  return s;
  */
  s << "{";
  for (int i = 0; i < rhs.size(); i++) {
    if (i < rhs.size() - 1) {
      s << rhs[i] << ", ";
    }
    else {
      s << rhs[i];
    }
  }
  s << "}";
  return s;
}
