#include <iostream>
#include "LES.h"
#include "PrintToFile.h"

using namespace std;

const int N = 12, M = 5, K = 1;

int main() {
	LES les(N, M, K);
	PrintToFile()(les);
	les.forwardSweep();
	PrintToFile()(les);
	les.backSubstitution();
	PrintToFile()(les);
	cout << "Relative error: " << fixed << les.relativeError() << "%" << endl;

	system("pause");

	return 0;
}