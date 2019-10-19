//
// Created by acer on 18.10.2019.
//

#ifndef LAB4_EXTENDEDMATRIX_H
#define LAB4_EXTENDEDMATRIX_H
#include <ctime>
#include <cstdlib>

class ExtendedMatrix {
 public:
  ExtendedMatrix(const ExtendedMatrix&);
  ExtendedMatrix(int, int);
  ~ExtendedMatrix();

  float* operator[] (int) const;
  int size() const;

 private:
  void generateCoefs();
  void generateCTerms(int);

  float** a;
  int mSize;
};

#endif //LAB4_EXTENDEDMATRIX_H
