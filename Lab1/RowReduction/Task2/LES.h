#pragma once
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Matrix.h"
#include "PrintToFile.h"

class LES {
public:

	LES(int size, int offset);
	LES(const LES& les);

	void firstStepPartialPivoting();
	void triangleFormPartialPivoting();

	void firstStepWithoutPivoting();
	void triangleFormWithoutPivoting();

	void findSolution();

	float relativeError();

private:
	Matrix coefs, constTerms, approximateSol;
	std::string state;
	int offset_;

	friend class PrintToFile;

	void generateCoefs();
	void generateCTerms(int offset);
};