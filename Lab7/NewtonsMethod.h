//
// Created by acer on 15.12.2019.
//

#ifndef LAB7_NEWTONSMETHOD_H
#define LAB7_NEWTONSMETHOD_H

#include <vector>
#include "Method.h"

class NewtonsMethod : public Method {
 public:
  NewtonsMethod(std::initializer_list<float>);

  float getFuncVal(float);
  float getDerivVal(float);

  float getX(float);
 private:
  const float E = 1e-10;

  std::vector<float> derivative;
};

#endif //LAB7_NEWTONSMETHOD_H
