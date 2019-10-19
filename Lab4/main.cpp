#include <iostream>
#include "ExtendedMatrix.h"
#include "LES.h"
#include "PrintToFile.h"

const int M = 5, N = 12, K = 1000;
const float E = 1e-4;

int main() {
  ExtendedMatrix matrix(N, M);
  LES lesJ(matrix), lesR05(matrix), lesR1(matrix), lesR15(matrix);

  PrintToFile()(lesJ);

  int jIt = lesJ.findSolJakobianMethod(K, E);
  int r05It = lesR05.findSolRelaxationMethod(K, E, 1.47);
  int r1It = lesR1.findSolRelaxationMethod(K, E, 1.5);
  int r15It = lesR15.findSolRelaxationMethod(K, E, 1.72);

  PrintToFile()(lesJ, jIt);
  PrintToFile()(lesR05, r05It);
  PrintToFile()(lesR1, r1It);
  PrintToFile()(lesR15, r15It);

  return 0;
}