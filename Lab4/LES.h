#pragma once
#include <string>
#include <cmath>
#include "PrintToFile.h"
#include "ExtendedMatrix.h"

class LES {
 public:

  LES(ExtendedMatrix);

  int findSolJakobianMethod(int, double);
  int findSolRelaxationMethod(int, double, double);

 private:
  ExtendedMatrix matrix;
  int mSize_;
  float* curSol_;
  float* prevSol_;
  std::string state;

  friend class PrintToFile;

  float maxDiff();
  float* operator[] (int);
};