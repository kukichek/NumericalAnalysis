//
// Created by acer on 08.12.2019.
//

#include <cmath>
#include "PowerMethod.h"

PowerMethod::PowerMethod(const Matrix& otherMatrix)
    : matrix(otherMatrix), curI(-1) {
  int size = matrix.size();

  u.resize(size);
  v.resize(size);
  v[0] = 1;

  calcNextIt();
}

std::vector<float> PowerMethod::getV() {
  return v;
}

std::vector<float> PowerMethod::getU() {
  return u;
}

void PowerMethod::calcNextIt() {
  int size = matrix.size();

  float maxV = v[0];
  for (int i = 0; i < size; ++i) {
    if (fabs(v[i]) > fabs(maxV)) {
      maxV = fabs(v[i]);
    }

    u[i] = v[i];
  }

  for (int i = 0; i < size; ++i) {
    u[i] /= maxV;
  }

  for (int i = 0; i < size; ++i) {
    v[i] = 0;

    for (int j = 0; j < size; ++j) {
      v[i] += matrix[i][j] * u[j];
    }
  }

  curI++;
}

float PowerMethod::getFirstLambdaCurEigenVal(bool isSymmetric) {
  float lambda;
  int size = matrix.size();

  if (isSymmetric) {
    float num, den;
    num = den = 0;

    for (int i = 0; i < size; ++i) {
      num += v[i] * u[i];
      den += u[i] * u[i];
    }

    lambda = num / den;
  } else {
    int maxUIndex = 0;

    for (int i = 1; i < size; ++i) {
      if (fabs(u[i]) > fabs(u[maxUIndex])) {
        maxUIndex = i;
      }
    }

    lambda = u[maxUIndex] < 0 ? -v[maxUIndex] : v[maxUIndex];
  }

  return lambda;
}

std::vector<float> PowerMethod::getFirstLambdaErrorVector(bool isSymmetric) {
  int size = matrix.size();
  float lambda = getFirstLambdaCurEigenVal(isSymmetric);

  std::vector<float> error(size);

  for (int i = 0; i < size; ++i) {
    error[i] = v[i] - lambda * u[i];
  }

  return error;
}

float PowerMethod::getSecondLambdaEigenVal(std::vector<float> u_mMinus,
                                           std::vector<float> v_m,
                                           std::vector<float> v_mPlus,
                                           float lambda1) {
  int maxAbsDenIndex = 0;
  int size = matrix.size();
  float v_mNorm = fabs(v_m[0]);

  for (int i = 1; i < size; ++i) {
    if (v_mNorm < fabs(v_m[i])) {
      v_mNorm = fabs(v_m[i]);
    }
  }

  for (int i = 1; i < size; ++i) {
    if (fabs(v_m[maxAbsDenIndex] - lambda1 * u_mMinus[maxAbsDenIndex]) <
        fabs(v_m[i] - lambda1 * u_mMinus[i])) {
      maxAbsDenIndex = i;
    }
  }

  return (v_mPlus[maxAbsDenIndex] * v_mNorm - lambda1 * v_m[maxAbsDenIndex])
      / (v_m[maxAbsDenIndex] - lambda1 * u_mMinus[maxAbsDenIndex]);
}

std::vector<float> PowerMethod::getSecondLambdaEigenVector(std::vector<float> v_mPlus,
                                               std::vector<float> u_m,
                                               float lambda1) {
  int size = matrix.size();
  std::vector<float> x(size);

  for (int i = 0; i < size; ++i) {
    x[i] = v_mPlus[i] - lambda1 * u_m[i];
  }

  return x;
}

std::vector<float> PowerMethod::getSecondLambdaErrorVector(std::vector<float> x, float lambda2) {
  int size = matrix.size();

  std::vector<float> error(size);

  for (int i = 0; i < size; ++i) {
    error[i] = 0;

    for (int j = 0; j < size; ++j) {
      error[i] += matrix[i][j] * x[j];
    }

    error[i] -= lambda2 * x[i];
  }

  return error;
}
