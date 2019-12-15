//
// Created by acer on 15.12.2019.
//
#include <cmath>
#include "NewtonsMethod.h"

NewtonsMethod::NewtonsMethod(std::initializer_list<float> coefs) {
  int size = coefs.size();
  function.resize(size);
  derivative.resize(size - 1);

  for (int i = 0, k = size - 1; i < size; ++i, k--) {
    function[k] = *(coefs.begin() + i);
  }

  for (int i = size - 1; i > 0; --i) {
    derivative[i - 1] = function[i] * i;
  }
}
float NewtonsMethod::getFuncVal(float x) {
  return multiply(function, x);
}

float NewtonsMethod::getDerivVal(float x) {
  return multiply(derivative, x);
}

float NewtonsMethod::getX(float x0) {
  float xk = x0;
  float xkPlus = xk - getFuncVal(xk) / getDerivVal(xk);

  while(fabs(xk - xkPlus) > E) {
    xk = xkPlus;
    xkPlus = xk - getFuncVal(xk) / getDerivVal(xk);
  }

  return xkPlus;
}
