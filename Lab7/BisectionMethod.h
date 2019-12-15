//
// Created by acer on 15.12.2019.
//

#ifndef LAB7_BISECTIONMETHOD_H
#define LAB7_BISECTIONMETHOD_H

#include "Method.h"

class BisectionMethod : public Method{
 public:
  BisectionMethod(std::initializer_list<float>);

  float getX(float, float);
 private:
  const float E = 2e-6;
};

#endif //LAB7_BISECTIONMETHOD_H
