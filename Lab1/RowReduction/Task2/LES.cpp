#include "LES.h"
#include<iostream>

LES::LES(int size, int offset) : coefs(size, size), constTerms(1, size), approximateSol(1, size), offset_(offset) {
	generateCoefs();
	generateCTerms(offset);

	state = "LinearEquationsSystem";
}

LES::LES(const LES& les) : coefs(les.coefs), constTerms(les.constTerms), approximateSol(les.approximateSol), offset_(les.offset_) {
	state = les.state;
}

void LES::firstStepPartialPivoting() {
	int k = 0;
	int colNum = k;

	for (int i = k + 1; i < coefs.height_; ++i) {
		if (abs(coefs[i][k]) > abs(coefs[colNum][k])) {
			colNum = i; 
		}
	}

	for (int j = 0; j < coefs.height_; ++j) {
		std::swap(coefs[colNum][j], coefs[k][j]);
	}
	std::swap(constTerms[colNum][0], constTerms[k][0]);

	for (int i = k + 1; i < coefs.height_; ++i) {

		float l = coefs[i][k] / coefs[k][k];
		coefs[i][k] = 0;
		constTerms[i][0] -= l * constTerms[k][0];
		for (int j = k + 1; j < coefs.height_; ++j) {
			coefs[i][j] -= l * coefs[k][j];
		}
	}

	state = "firstStepPartialPivoting";
}

void LES::triangleFormPartialPivoting() {
	if (state != "firstStepPartialPivoting") {
		firstStepPartialPivoting();
	}
	for (int k = 1; k < coefs.height_ - 1; ++k) {
		int colNum = k;

		for (int i = k + 1; i < coefs.height_; ++i) {
			if (abs(coefs[i][k]) > abs(coefs[colNum][k])) {
				colNum = i;
			}
		}

		for (int j = 0; j < coefs.height_; ++j) {
			std::swap(coefs[colNum][j], coefs[k][j]);
		}
		std::swap(constTerms[colNum][0], constTerms[k][0]);

		for (int i = k + 1; i < coefs.height_; ++i) {

			float l = coefs[i][k] / coefs[k][k];
			coefs[i][k] = 0;
			constTerms[i][0] -= l * constTerms[k][0];
			for (int j = k + 1; j < coefs.height_; ++j) {
				coefs[i][j] -= l * coefs[k][j];
			}
		}
	}

	state = "triangleFormPartialPivoting";
}

void LES::firstStepWithoutPivoting() {
	int k = 0;
	for (int i = k + 1; i < coefs.height_; ++i) {
		float l = coefs[i][k] / coefs[k][k];
		coefs[i][k] = 0;
		constTerms[i][0] -= l * constTerms[k][0];
		for (int j = k + 1; j < coefs.height_; ++j) {
			coefs[i][j] -= l * coefs[k][j];
		}
	}

	state = "firstStepWithoutPivoting";
}

void LES::triangleFormWithoutPivoting() {
	if (state != "firstStepWithoutPivoting") {
		firstStepWithoutPivoting();
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

	state = "triangleFormWithoutPivoting";
}

void LES::findSolution() {
	for (int i = coefs.height_ - 1; i >= 0; --i) {
		approximateSol[i][0] = constTerms[i][0];
		for (int j = i + 1; j < coefs.height_; ++j) {
			approximateSol[i][0] -= coefs[i][j] * approximateSol[j][0];
		}
		approximateSol[i][0] /= coefs[i][i];
	}

	(state == "triangleFormPartialPivoting")? state = "ApproximateSolutionPartialPivoting" : state = "ApproximateSolutionWithoutPivoting";
}

void LES::generateCoefs() {
	//std::srand(std::time(0));

	for (int i = 0; i < coefs.height_; ++i) {
		for (int j = 0; j < coefs.height_; ++j) {
			coefs[i][j] = std::rand() % 201 - 100;
		}
	}
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
