//
// Created by acer on 15.12.2019.
//

#include <cmath>
#include "IterationMethod.h"

IterationMethod::IterationMethod(std::initializer_list<float> coefs, float c) {
  int size = coefs.size();
  function.resize(size);

  for (int i = 0, k = size - 1; i < size; ++i, k--) {
    function[k] = *(coefs.begin() + i) * c;
  }

  function[1]++;
}

float IterationMethod::getX(float x0) {
  float xk = x0;
  float xkPlus = multiply(function, xk);

  while (fabs(xk - xkPlus) > E) {
    xk = xkPlus;
    xkPlus = multiply(function, xk);
  }

  return xkPlus;
}
