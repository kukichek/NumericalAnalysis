//
// Created by acer on 08.12.2019.
//

#ifndef LAB6_POWERMETHOD_H
#define LAB6_POWERMETHOD_H

#include <vector>
#include "Matrix.h"

class PowerMethod {
 public:
  explicit PowerMethod(const Matrix&);

  std::vector<float> getV();
  std::vector<float> getU(); // eigen vector with respect to lambda_1 calculated via function getCurEigenVal

  void calcNextIt();

  float getFirstLambdaCurEigenVal(bool); // is equal lambda_1^k with respect to k = curI
  std::vector<float> getFirstLambdaErrorVector(); // is equal to error on iteration curI

  float getSecondLambdaEigenVal(std::vector<float>, std::vector<float>, std::vector<float>, float);
  std::vector<float> getSecondLambdaEigenVector(std::vector<float>, std::vector<float>, float);
  std::vector<float> getSecondLambdaErrorVector(std::vector<float>, float);

 private:
  Matrix matrix;
  std::vector<float> u; // u^k according to k = curI
  std::vector<float> v; // u^k according to k = curI
  int curI;
};

#endif //LAB6_POWERMETHOD_H
