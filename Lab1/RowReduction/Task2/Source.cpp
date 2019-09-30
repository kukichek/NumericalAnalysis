#include <iostream>
#include "LES.h"
#include "PrintToFile.h"

const int N = 15, M = 5;

int main() {
	LES lesPartialPivoting(N, M); // LES will be solved using the Gaussian elimination with partial pivoting
	LES lesWithoutPivoting(lesPartialPivoting); // LES will be solved using the Gaussian elimination without pivoting
	PrintToFile()(lesPartialPivoting);


	lesWithoutPivoting.firstStepWithoutPivoting();
	PrintToFile()(lesWithoutPivoting);
	lesWithoutPivoting.triangleFormWithoutPivoting();
	PrintToFile()(lesWithoutPivoting);
	lesWithoutPivoting.findSolution();
	PrintToFile()(lesWithoutPivoting);


	lesPartialPivoting.firstStepPartialPivoting();
	PrintToFile()(lesPartialPivoting);
	lesPartialPivoting.triangleFormPartialPivoting();
	PrintToFile()(lesPartialPivoting);
	lesPartialPivoting.findSolution(); 
	PrintToFile()(lesPartialPivoting);

	std::cout << std::fixed << lesWithoutPivoting.relativeError() << std::endl;
	std::cout << std::fixed << lesPartialPivoting.relativeError() << std::endl;

	system("pause");

	return 0;
}