#include <iostream>
#include <iomanip>
#include "NewtonsMethod.h"
#include "IterationMethod.h"
#include "BisectionMethod.h"

int main() {
  NewtonsMethod derivativeNewton({2, -78, 813, 145734});
  IterationMethod derivativeIteration({2, -78, 813, 145734}, -1e-4);

  std::cout << std::fixed << std::setprecision(11) << derivativeNewton.getX(-32) << std::endl;
  std::cout << std::fixed << std::setprecision(11) << derivativeIteration.getX(-32) << std::endl;

  NewtonsMethod funcNewtonRoot({1, -52, 813, 291468, -841577});
  BisectionMethod funcBisecRoot({1, -52, 813, 291468, -841577});

  std::cout << std::fixed << std::setprecision(11) << funcNewtonRoot.getX(-50) << std::endl;
  std::cout << std::fixed << std::setprecision(11) << funcBisecRoot.getX(-55, -50) << std::endl;

  std::cout << std::fixed << std::setprecision(11) << funcNewtonRoot.getX(5) << std::endl;
  std::cout << std::fixed << std::setprecision(11) << funcBisecRoot.getX(0, 5) << std::endl;
}