#include"LinearEquationsSys.h"

LinearEquationsSys::LinearEquationsSys(int size, int option, int offset) : size_(size), option_(option) {
	//std::srand(std::time(0));
	matrix = new float*[size_];

	for (int i = 0; i < size_; ++i) {
		matrix[i] = new float[size_];
	}

	for (int i = 0; i < size_; ++i) {
		int sum = 0;
		for (int j = 0; j < size_; ++j) {
			matrix[i][j] = std::rand() % 5 - 4;
			sum += matrix[i][j];
		}
		sum -= matrix[i][i];
		matrix[i][i] = -1 * sum;
	}

	matrix[0][0] += TenToPow(option_);

	generateConstantTerms(offset);
}

LinearEquationsSys::LinearEquationsSys(const LinearEquationsSys& linearSys) : size_(linearSys.size_), option_(linearSys.option_) {
	matrix = new float*[size_];
	constantTerms = new float[size_];

	for (int i = 0; i < size_; ++i) {
		matrix[i] = new float[size_];
		constantTerms[i] = linearSys.constantTerms[i];
		for (int j = 0; j < size_; ++j) {
			matrix[i][j] = linearSys.matrix[i][j];
		}
	}
}

float** LinearEquationsSys::getSysCoeffs() const {
	float** a = new float*[size_];
	for (int i = 0; i < size_; ++i) {
		a[i] = new float[size_];
		for (int j = 0; j < size_; ++j) {
			a[i][j] = matrix[i][j];
		}
	}
	return a;
}

float* LinearEquationsSys::getConstTerms() const {
	float* b = new float[size_];
	for (int i = 0; i < size_; ++i) {
		b[i] = constantTerms[i];
	}
	return b;
}

int LinearEquationsSys::getSize() const {
	return size_;
}

void LinearEquationsSys::generateConstantTerms(int offset) {
	constantTerms = new float[size_];
	for (int i = 0; i < size_; ++i) {
		constantTerms[i] = 0;
		for (int j = 0; j < size_; ++j) {
			constantTerms[i] += (j + offset) * matrix[i][j];
		}
	}
}

float LinearEquationsSys::TenToPow(int power) {
	float ans = 1;
	for (int i = 0; i < power; ++i) {
		ans /= 10;
	}
	return ans;
}

GaussianElimination::GaussianElimination(const LinearEquationsSys& linearSys) : LinearEquationsSys(linearSys) {
	approximateDecision = new float[size_];
}

void GaussianElimination::firstStep() {
	int k = 0;
	for (int i = k + 1; i < size_; ++i) {
		float l = matrix[i][k] / matrix[k][k];
		matrix[i][k] = 0;
		constantTerms[i] -= l * constantTerms[k];
		for (int j = k + 1; j < size_; ++j) {
			matrix[i][j] -= l * matrix[k][j];
		}
	}
}

void GaussianElimination::triangularForm() {
	for (int k = 0; k < size_ - 1; ++k) {
		for (int i = k + 1; i < size_; ++i) {
			float l = matrix[i][k] / matrix[k][k];
			matrix[i][k] = 0;
			constantTerms[i] -= l * constantTerms[k];
			for (int j = k + 1; j < size_; ++j) {
				matrix[i][j] -= l * matrix[k][j];
			}
		}
	}
}