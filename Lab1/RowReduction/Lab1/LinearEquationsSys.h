#pragma once
#include <cstdlib>
#include <ctime>
#include "PrintToFile.h"
#include "GaussianElimination.h"

class LinearEquationsSys {
public:

	LinearEquationsSys(int size, int option, int offset);
	LinearEquationsSys(const LinearEquationsSys& linearSys);

	float** getSysCoeffs() const;
	float* getConstTerms() const;

	int getSize() const;

protected:

	int size_, option_;

	float** matrix;
	float* constantTerms;

	friend struct PrintToFile;

private:

	float TenToPow(int power);
	void generateConstantTerms(int offset);
};

class GaussianElimination : public LinearEquationsSys {
public:
	GaussianElimination(const LinearEquationsSys& linearSys);
	void firstStep();
	void triangularForm();
private:
	float* approximateDecision;
};