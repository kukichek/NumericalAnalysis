#include <iostream>
#include "LES.h"
#include "PrintToFile.h"

using namespace std;

const int N = 12, M = 5;
int k = 1;

int main() {
	LES les(N, M, k);
	PrintToFile()(les);
	les.LDLtDecompos();
	PrintToFile()(les);
	les.findSolution();
	PrintToFile()(les);
	cout << "RelativeError: " << fixed << les.relativeError() << '%' << endl;

	system("pause");

	return 0;
}