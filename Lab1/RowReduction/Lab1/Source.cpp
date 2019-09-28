#include <iostream>
//#include<fstream>
#include "LinearEquationsSys.h"
#include "PrintToFile.h"

using namespace std;

const int M = 5, N = 12;
int k;

int main() {
	k = 0;
	LinearEquationsSys sys(N, k, M);
	PrintToFile()(&sys, "LinearEquation");
	GaussianElimination decision(sys);
	//decision.firstStep();
	//PrintToFile()(&decision, "FirstStep");
	decision.triangularForm();
	PrintToFile()(&decision, "TriangularForm");

	system("pause");

	return 0;
}