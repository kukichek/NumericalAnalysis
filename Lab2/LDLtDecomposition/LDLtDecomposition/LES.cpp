#include "LES.h"

LES::LES(int size, int offset, int option) 
	: coefs(size, size), constTerms(1, size), offset_(offset), option_(option) {
	generateCoefs(option);
	generateCTerms(offset);

	state = "LinearEquationsSystem";
}

void LES::LDLtDecompos() {
	Matrix t(1, coefs.height_);
	for (int k = 0; k < coefs.height_ - 1; ++k) {
		for (int i = k + 1; i < coefs.height_; ++i) {
			t[i][0] = coefs[i][k];
			coefs[i][k] /= coefs[k][k];

			for (int j = k + 1; j <= i; ++j) {
				coefs[i][j] -= t[j][0] * coefs[i][k];
			}
		}
	}

	state = "LDLtDecompos";
}

void LES::findSolution() {
	findY();
	findZ();
	findX();

	state = "ApproximateSolution";
}

float LES::relativeError() {
	int maxI = 0;
	for (int i = 1; i < coefs.height_; ++i) {
		if (abs(constTerms[i][0] - (i + offset_)) > abs(constTerms[maxI][0] - (maxI + offset_))) {
			maxI = i;
		}
	}

	return abs(constTerms[maxI][0] - (maxI + offset_)) / (coefs.height_ + offset_ - 1) * 100;
}

void LES::generateCoefs(int option) {
	//std::srand(std::time(0));

	for (int i = 0; i < coefs.height_; ++i) {
		coefs[i][i] = 0;
		for (int j = i + 1; j < coefs.height_; ++j) {
			coefs[i][j] = std::rand() % 5 - 4;
			coefs[i][i] -= coefs[i][j];
		}
		for (int j = 0; j < i; ++j) {
			coefs[i][j] = coefs[j][i];
			coefs[i][i] -= coefs[i][j];
		}
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

void LES::findY() {
	for (int k = 0; k < coefs.height_ - 1; ++k) {
		for (int i = k + 1; i < coefs.height_; ++i) {
			constTerms[i][0] -= coefs[i][k] * constTerms[k][0];
		}
	}

	state = "Y";
}

void LES::findZ() {
	for (int i = 0; i < coefs.height_; ++i) {
		constTerms[i][0] /= coefs[i][i];
	}

	state = "Z";
}

void LES::findX() {
	for (int i = coefs.height_ - 1; i >= 0; --i) {
		for (int j = i + 1; j < coefs.height_; ++j) {
			constTerms[i][0] -= coefs[j][i] * constTerms[j][0];
		}
	}

	state = "X";
}