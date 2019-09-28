#include "PrintToFile.h"
#include "LinearEquationsSys.h"

void PrintToFile::operator() (LinearEquationsSys *system, const std::string preName) {
	std::string fileName = preName + "Op" + std::to_string(system->option_) + ".txt";
	std::ofstream out(fileName);

	for (int i = 0; i < system->size_; ++i) {
		for (int j = 0; j < system->size_; ++j) {
			out << std::fixed << std::setprecision(4) << std::setw(9) << system->matrix[i][j];
		}
		out << std::fixed << std::setprecision(4) << std::setw(9) << '\t' << system->constantTerms[i] << '\n';
	}
}