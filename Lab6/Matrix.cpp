//
// Created by acer on 18.10.2019.
//

#include "Matrix.h"

Matrix::Matrix(const Matrix& matrix) : mSize(matrix.mSize) {
  a = new float* [mSize];

  for (int i = 0; i < mSize; ++i) {
    a[i] = new float[mSize];

    for (int j = 0; j < mSize; ++j) {
      a[i][j] = matrix[i][j];
    }
  }
}

Matrix::Matrix(int size) : mSize(size) {
  a = new float* [mSize];

  for (int i = 0; i < mSize; ++i) {
    a[i] = new float[mSize];
  }

  generateCoefs();
}

Matrix::~Matrix() {
  for (int i = 0; i < mSize; ++i) {
    delete[] a[i];
  }
}

float* Matrix::operator[](int index) const {
  return a[index];
}

int Matrix::size() const {
  return mSize;
}

Matrix& Matrix::operator= (const Matrix& other) {
  if (this == &other) return *this;

  for (int i = 0; i < mSize; ++i) {
    for (int j = 0; j < mSize; ++j) {
      a[i][j] = other[i][j];
    }
  }

  return *this;
}

void Matrix::generateCoefs() {
  srand(time(nullptr));

  for (int i = 0; i < mSize; ++i) {
    for (int j = i + 1; j < mSize; ++j) {
      a[i][j] = std::rand() % 5 - 4;
      a[j][i] = a[i][j];
    }
  }

  for (int i = 0; i < mSize; ++i) {
    for (int j = 0; j < mSize; ++j) {
      if (i != j) {
        a[i][i] -= a[i][j];
      }
    }
  }

  a[0][0] ++;
}