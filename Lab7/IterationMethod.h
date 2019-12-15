//
// Created by acer on 15.12.2019.
//

#ifndef LAB7_ITERATIONMETHOD_H
#define LAB7_ITERATIONMETHOD_H

#include <initializer_list>
#include <vector>
#include "Method.h"

class IterationMethod: public Method{
 public:
  IterationMethod(std::initializer_list<float>, float);

  float getX(float);
 private:
  const float E = 1e-9;
};

#endif //LAB7_ITERATIONMETHOD_H
