#include "LES.h"
#include "PrintToFile.h"

void PrintToFile::operator() (LES& les) {
	int pr, w;
	std::string nameOfFile = "Countings\\" + les.state + ".txt";
	std::ofstream out(nameOfFile);

	if (les.state == "ApproximateSolution") {
		pr = 9;
		w = 14;

		for (int i = 0; i < les.n_; ++i) {
			out << std::fixed << std::setprecision(pr) << std::setw(w) << les.constTerms[i][0] << " \\\\\n";
		}

		out.flush();
		return;
	}

	if (les.state == "ForwardSweep") {
		pr = 4;
		w = 9;
		for (int i = 0; i < les.n_; ++i) {
			for (int j = 0; j < i; ++j) {
				out << " &";
			}

			//out << " 1" << std::fixed << std::setprecision(pr) << std::setw(w) << les.coefs[i][2];
			for (int j = 1; j < 3; ++j) {
				out << std::fixed << std::setprecision(pr) << std::setw(w) << les.coefs[i][j];
			}

			for (int j = i + 2; j < les.n_; ++j) {
				out << " &";
			}

			out << std::fixed << std::setprecision(pr) << std::setw(w) << les.constTerms[i][0] << " \\\\\n";
		}

		out.flush();
		return;
	}

	pr = 0;
	w = 5;

	for (int i = 0; i < les.n_; ++i) {
		for (int j = 0; j < i - 1; ++j) {
			out << " &";
		}
		for (int j = 0; j < 3; ++j) {
			out << std::fixed << std::setprecision(pr) << std::setw(w) << les.coefs[i][j];
		}
		for (int j = i + 2; j < les.n_; ++j) {
			out << " &";
		}

		out << std::fixed << std::setprecision(pr) << std::setw(w) << les.constTerms[i][0] << " \\\\\n";
	}
	
	out.flush();
	return;
}