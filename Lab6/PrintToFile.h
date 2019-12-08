#pragma once
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

class Matrix;

struct PrintToFile {
	static void printMatrix(Matrix&, std::string);

	static void printEigen(float, std::vector<float>, std::vector<float>, float, const std::string&);
};