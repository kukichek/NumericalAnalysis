#pragma once
#include <string>
#include <cstdlib>
#include "Matrix.h"
#include "PrintToFile.h"

class LES {
public:

	LES(int size, int offset, int option);

	void forwardSweep();
	void backSubstitution();

	float relativeError();

private:
	int n_, m_, k_;
	Matrix coefs, constTerms;
	std::string state;

	friend class PrintToFile;

	void generateCoefs();
	void generateCTerms();
};