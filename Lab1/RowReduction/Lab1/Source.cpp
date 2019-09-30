#include <iostream>
#include "LES.h"
#include "PrintToFile.h"

const int N = 15, M = 5;
int k = 0;

int main() {
	LES les(N, M, k); // LES - linear equations system; Initializing of the system of linear equations;
	PrintToFile()(les); // Print the system of linear equations;
	les.firstStep(); // First step of calculating
	PrintToFile()(les);
	les.triangleForm(); // Calculating a triangle form of LES
	PrintToFile()(les);
	les.findSolution(); // Finding solution
	PrintToFile()(les);

	std::cout << std::fixed << les.relativeError();

	system("pause");

	return 0;
}