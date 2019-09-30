#pragma once
#include <string>
#include <cstdlib>
#include <ctime>
#include "Matrix.h"
#include "PrintToFile.h"

class LES {
public:

	LES(int size, int offset, int option);

	void firstStep();
	void triangleForm();
	void findSolution();

	float relativeError();

private:
	Matrix coefs, constTerms, approximateSol;
	int option_, offset_;
	std::string state;

	friend class PrintToFile;

	void generateCoefs(int option);
	void generateCTerms(int offset);
};