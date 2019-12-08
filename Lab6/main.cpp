#include <iostream>
#include <cmath>
#include "PowerMethod.h"
#include "Matrix.h"

const int N = 12;

int main() {
  Matrix m(N);

  std::vector<float> u_m30Minus;
  std::vector<float> v_m30;
  std::vector<float> v_m30Plus;

  std::vector<float> u_m50Minus;
  std::vector<float> v_m50;
  std::vector<float> v_m50Plus;

  std::vector<float> u_k;
  std::vector<float> v_kPlus;

  PrintToFile::printMatrix(m, "matrix");

  PowerMethod powerMethod(m);

  for (int i = 0; i < 46; ++i) {
    if (i == 30) {
      u_m30Minus = powerMethod.getU();
      v_m30 = powerMethod.getV();

      powerMethod.calcNextIt();

      v_m30Plus = powerMethod.getV();
    }

    powerMethod.calcNextIt();
  }

  std::vector<float> errorVector;
  float error;
  for (int i = 46; i < 51; ++i) {
    if (i == 50) {
      u_m50Minus = powerMethod.getU();
      v_m50 = powerMethod.getV();
    }

    powerMethod.calcNextIt();

    errorVector = powerMethod.getFirstLambdaErrorVector();
    error = fabs(errorVector[0]);
    for (int i = 1; i < N; ++i) {
      if (fabs(error) < fabs(errorVector[i])) {
        error = fabs(errorVector[i]);
      }
    }

    PrintToFile::printEigen(powerMethod.getFirstLambdaCurEigenVal(true),
                            powerMethod.getU(),
                            errorVector,
                            error,
                            "lambda" + std::to_string(i));
  }

  u_k = powerMethod.getU();
  v_m50Plus = powerMethod.getV();
  v_kPlus = powerMethod.getV();

  float lambda1, lambda2, lambda2Error;
  std::vector<float> x;
  std::vector<float> lambda2ErrorVector;

  ////////////////// m = 30, not symmetric /////////////////////////

  lambda1 = powerMethod.getFirstLambdaCurEigenVal(false);
  lambda2 = powerMethod
      .getSecondLambdaEigenVal(u_m30Minus, v_m30, v_m30Plus, lambda1);
  x = powerMethod.getSecondLambdaEigenVector(v_kPlus, u_k, lambda1);
  lambda2ErrorVector = powerMethod.getSecondLambdaErrorVector(x, lambda2);

  lambda2Error = fabs(lambda2ErrorVector[0]);
  for (int i = 1; i < N; ++i) {
    if (fabs(lambda2Error) < fabs(lambda2ErrorVector[i])) {
      lambda2Error = fabs(lambda2ErrorVector[i]);
    }
  }

  PrintToFile::printEigen(lambda2, x, lambda2ErrorVector,
                          lambda2Error, "lambda2FirstCase");

  ////////////////// m = 50, not symmetric /////////////////////////

  lambda2 = powerMethod
      .getSecondLambdaEigenVal(u_m50Minus, v_m50, v_m50Plus, lambda1);
  lambda2ErrorVector = powerMethod.getSecondLambdaErrorVector(x, lambda2);

  lambda2Error = fabs(lambda2ErrorVector[0]);
  for (int i = 1; i < N; ++i) {
    if (fabs(lambda2Error) < fabs(lambda2ErrorVector[i])) {
      lambda2Error = fabs(lambda2ErrorVector[i]);
    }
  }

  PrintToFile::printEigen(lambda2, x, lambda2ErrorVector,
                          lambda2Error, "lambda2SecondCase");

  ////////////////// m = 50, symmetric /////////////////////////

  lambda1 = powerMethod.getFirstLambdaCurEigenVal(true);
  lambda2 = powerMethod
      .getSecondLambdaEigenVal(u_m50Minus, v_m50, v_m50Plus, lambda1);
  x = powerMethod.getSecondLambdaEigenVector(v_kPlus, u_k, lambda1);
  lambda2ErrorVector = powerMethod.getSecondLambdaErrorVector(x, lambda2);

  lambda2Error = fabs(lambda2ErrorVector[0]);
  for (int i = 1; i < N; ++i) {
    if (fabs(lambda2Error) < fabs(lambda2ErrorVector[i])) {
      lambda2Error = fabs(lambda2ErrorVector[i]);
    }
  }

  PrintToFile::printEigen(lambda2, x, lambda2ErrorVector,
                          lambda2Error, "lambda2ThirdCase");

  return 0;
}