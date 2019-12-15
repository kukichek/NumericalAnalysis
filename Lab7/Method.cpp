//
// Created by acer on 15.12.2019.
//

#include "Method.h"

float Method::multiply(std::vector<float>& f, float x) {
  float ans = f[f.size() - 1];

  for (int i = f.size() - 1; i > 0; --i) {
    ans = ans * x + f[i - 1];
  }

  return ans;
}