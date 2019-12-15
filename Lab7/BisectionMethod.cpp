//
// Created by acer on 15.12.2019.
//

#include <stdexcept>
#include <cmath>
#include "BisectionMethod.h"

BisectionMethod::BisectionMethod(std::initializer_list<float> coefs) {
  int size = coefs.size();
  function.resize(size);

  for (int i = 0, k = size - 1; i < size; ++i, k--) {
    function[k] = *(coefs.begin() + i);
  }
}
float BisectionMethod::getX(float a, float b) {
  if (multiply(function, a) * multiply(function, b) > 0) throw std::invalid_argument("Invalid range");

  float m;

  while (b - a > 2 * E) {
    m = (a + b) / 2;
    float fM = multiply(function, m);
    if (fabs(fM) < E) return m;

    (multiply(function, a) * fM < 0) ? b = m : a = m;
  }

  return (a + b) / 2;
}


