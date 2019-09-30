#include "LES.h"
#include "PrintToFile.h"

void PrintToFile::operator() (LES& les) {
	int pr = 2, w = 9;
	std::string nameOfFile; 
	nameOfFile = "Countings\\" + les.state + ".txt";
	std::ofstream out(nameOfFile);

	if (les.state.find("ApproximateSolution") != std::string::npos) {
		pr = 6;
		w = 13;
		for (int i = 0; i < les.approximateSol.height_; ++i) {
			out << std::fixed << std::setprecision(pr) << std::setw(w) << les.approximateSol[i][0] << std::endl;
		}
	}
	else {
		if (les.state == "LinearEquationsSystem") {
			pr = 0;
			w = 7;
		}

		for (int i = 0; i < les.coefs.height_; ++i) {
			for (int j = 0; j < les.coefs.height_; ++j) {
				out << std::fixed << std::setprecision(pr) << std::setw(w) << les.coefs[i][j];
			}
			out << "\t\t" << std::fixed << std::setprecision(pr) << std::setw(w) << les.constTerms[i][0] << std::endl;
		}

	}
}