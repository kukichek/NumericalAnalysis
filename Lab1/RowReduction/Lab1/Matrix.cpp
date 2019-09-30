#include "Matrix.h"

Matrix::Matrix(int w, int h) : width_(w), height_(h) {
	a = new float*[height_];

	for (int i = 0; i < height_; ++i) {
		a[i] = new float[width_];
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < height_; ++i) {
		delete[] a[i];
	}
	delete[] a;
}

float* Matrix::operator[] (int i) {
	return a[i];
}