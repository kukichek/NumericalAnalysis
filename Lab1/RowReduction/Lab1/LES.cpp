#include "LES.h"

LES::LES(int size, int offset, int option) : coefs(size, size), constTerms(1, size), approximateSol(1, size), offset_(offset), option_(option) {
	generateCoefs(option);
	generateCTerms(offset);

	state = "LinearEquationsSystem";
}

void LES::firstStep() {
	int k = 0;
	for (int i = k + 1; i < coefs.height_; ++i) {
		float l = coefs[i][k] / coefs[k][k];
		coefs[i][k] = 0;
		constTerms[i][0] -= l * constTerms[k][0];
		for (int j = k + 1; j < coefs.height_; ++j) {
			coefs[i][j] -= l * coefs[k][j];
		}
	}

	state = "FirstStep";
}

void LES::triangleForm() {
	if (state != "FirstStep") {
		firstStep();
	}
	for (int k = 1; k < coefs.height_ - 1; ++k) {
		for (int i = k + 1; i < coefs.height_; ++i) {
			float l = coefs[i][k] / coefs[k][k];
			coefs[i][k] = 0;
			constTerms[i][0] -= l * constTerms[k][0];
			for (int j = k + 1; j < coefs.height_; ++j) {
				coefs[i][j] -= l * coefs[k][j];
			}
		}
	}

	state = "TriangleForm";
}

void LES::findSolution() {
	for (int i = coefs.height_ - 1; i >= 0; --i) {
		approximateSol[i][0] = constTerms[i][0];
		for (int j = i + 1; j < coefs.height_; ++j) {
			approximateSol[i][0] -= coefs[i][j] * approximateSol[j][0];
		}
		approximateSol[i][0] /= coefs[i][i];
	}

	state = "ApproximateSolution";
}

void LES::generateCoefs(int option) {
	//std::srand(std::time(0));

	for (int i = 0; i < coefs.height_; ++i) {
		int sum = 0;
		for (int j = 0; j < coefs.height_; ++j) {
			coefs[i][j] = std::rand() % 5 - 4;
			sum += coefs[i][j];
		}
		sum -= coefs[i][i];
		coefs[i][i] = -1 * sum;
	}

	(option == 0) ? coefs[0][0] += 1 : coefs[0][0] += 0.1;
}

void LES::generateCTerms(int offset) {
	for (int i = 0; i < constTerms.height_; ++i) {
		constTerms[i][0] = 0;
		for (int j = 0; j < constTerms.height_; ++j) {
			constTerms[i][0] += (j + offset) * coefs[i][j];
		}
	}
}

float LES::relativeError() {
	int maxI = 0;
	for (int i = 1; i < coefs.height_; ++i) {
		if (abs(approximateSol[i][0] - (i + offset_)) > abs(approximateSol[maxI][0] - (maxI + offset_))) {
			maxI = i;
		}
	}

	return abs(approximateSol[maxI][0] - (maxI + offset_)) / (coefs.height_ + offset_ - 1) * 100;
}