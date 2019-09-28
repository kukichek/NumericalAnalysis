#pragma once
#include <string>
#include <fstream>
#include <iomanip>

class LinearEquationsSys;

struct PrintToFile {
	void operator() (LinearEquationsSys *system, const std::string preName);
};
