#pragma once
#include <string>
#include <cstdlib>
#include <ctime>
#include "Matrix.h"
#include "PrintToFile.h"

class LES {
public:

	LES(int size, int offset, int option);

	void LDLtDecompos();
	void findSolution();

	float relativeError();

private:
	Matrix coefs, constTerms;
	int option_, offset_;
	std::string state;

	friend class PrintToFile;

	void generateCoefs(int option);
	void generateCTerms(int offset);

	void findY();
	void findZ();
	void findX();
};