#include "PrintToFile.h"
#include "Matrix.h"

void PrintToFile::printMatrix(Matrix& matrix, std::string nameOfFile) {
  int w;
  std::ofstream out("countings/" + nameOfFile + ".txt");

  w = 4;

  int size = matrix.size();
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      out << std::setw(w) << matrix[i][j] << " &";
    }

    out << " \\\\\n";
  }

  out.flush();
}

void PrintToFile::printEigen(float eigenVal, std::vector<float> eigenVec, std::vector<float> errorVec, float error, const std::string& nameOfFile) {
  int w, pr;
  int size = eigenVec.size();
  std::ofstream out("countings/" + nameOfFile + ".txt");

  w = 12;
  pr = 7;

  out << "Eigen value: " << std::fixed << std::setprecision(pr) << eigenVal << "\n\nEigen vector:\n";

  for (int i = 0; i < size; ++i) {
    out << std::fixed << std::setprecision(pr) << eigenVec[i] << " \\\\\n";
  }

  out << "\nError vector:\n";
  for (int i = 0; i < size; ++i) {
    out << std::fixed << std::setprecision(pr) << errorVec[i] << " \\\\\n";
  }

  out << "\nError: " << std::fixed << std::setprecision(pr) << error;
}