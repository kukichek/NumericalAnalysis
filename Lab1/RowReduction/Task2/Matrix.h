#pragma once

class Matrix {
public:

	const int width_, height_;

	Matrix(int w, int h);
	Matrix(const Matrix& m);
	~Matrix();

	float* operator[] (int i);

private:
	float** a;
};