#include "LES.h"

LES::LES(int size, int m, int k) 
	: n_(size), coefs(3, n_), constTerms(1, n_), k_(k), m_(m) {
	generateCoefs();
	generateCTerms();

	state = "LinearEquationsSystem";
}

void LES::forwardSweep() {
	for (int i = 0; i < n_ - 1; ++i) {
		constTerms[i][0] /= coefs[i][1];

		coefs[i][2] /= coefs[i][1];
		coefs[i][1] = 1;

		coefs[i + 1][1] -= coefs[i][2] * coefs[i + 1][0];
		constTerms[i + 1][0] -= constTerms[i][0] * coefs[i + 1][0];
	}

	constTerms[n_ - 1][0] /= coefs[n_ - 1][1];

	state = "ForwardSweep";
}

void LES::backSubstitution() {
	for (int i = n_ - 1; i > 0; --i) {
		constTerms[i - 1][0] -= coefs[i - 1][2] * constTerms[i][0];
	}

	state = "ApproximateSolution";
}

float LES::relativeError() {
	float num = 0, den = 0;

	for (int i = 0; i < n_; ++i) {
		num += abs(constTerms[i][0] - (1 + i));
		den += (1 + i);
	}

	return num / den * 100;
}

void LES::generateCoefs() {
	//coefs[0][0] = 0;
	coefs[0][1] = m_;
	coefs[0][2] = m_ - 1;

	for (int i = 1; i < n_; ++i) {
		coefs[i][0] = -k_;
		coefs[i][1] = m_ + k_ + i - 1;
		coefs[i][2] = m_ + i - 1;
	}

	coefs[n_ - 1][2] = 0;
}

void LES::generateCTerms() {
	for (int i = 0; i < n_ - 1; ++i) {
		constTerms[i][0] = i * coefs[i][0] + (i + 1) * coefs[i][1] + (i + 2) * coefs[i][2];
	}

	constTerms[n_ - 1][0] = coefs[n_ - 1][0] * (n_ - 1) + coefs[n_ - 1][1] * n_;
}