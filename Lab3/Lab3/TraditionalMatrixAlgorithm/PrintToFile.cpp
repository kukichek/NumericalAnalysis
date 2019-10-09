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
			for (int j = 0; j < les.n_; ++j) {
				if ((j - i) == 1) {
					out << std::fixed << std::setprecision(pr) << std::setw(w) << les.coefs[i][j];
				}
				else {
					if (j == i) {
						out << " 1";
					}
				}

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
		for (int j = 0; j < les.n_; ++j) {
			if (abs(j - i) <= 1) {
				out << std::fixed << std::setprecision(pr) << std::setw(w) << les.coefs[i][j];
			}

			out << " &";
		}

		out << std::fixed << std::setprecision(pr) << std::setw(w) << les.constTerms[i][0] << " \\\\\n";
	}
	
	out.flush();
	return;
}