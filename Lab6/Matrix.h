//
// Created by acer on 18.10.2019.
//

#ifndef LAB4_MATRIX_H
#define LAB4_MATRIX_H
#include <ctime>
#include <cstdlib>
#include "PrintToFile.h"

class Matrix {
 public:
  Matrix(const Matrix&);
  Matrix(int);
  ~Matrix();

  float* operator[] (int) const;
  int size() const;

  Matrix& operator= (const Matrix&);

 protected:
  void generateCoefs();

  int mSize;
  float** a;

  friend class PrintToFile;
};

#endif //LAB4_MATRIX_H
