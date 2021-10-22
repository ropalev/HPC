#include "main.h"
std::vector<std::vector<int>> cmatrix(int n) {
  std::vector<std::vector<int>> mat(n, std::vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      mat[i][j] = (rand() % 10);
    }
  }
  return mat;
}


std::vector<std::vector<int>> matmul(std::vector<std::vector<int>> mat1, std::vector<std::vector<int>> mat2) {
  std::vector<std::vector<int>> mat(mat1.size(), std::vector<int>(mat1.size()));
  for (int i = 0; i < mat1.size(); i++) {
    for (int j = 0; j < mat1.size(); j++) {
      mat[i][j] = 0;
      for (int k = 0; k < mat1.size(); k++) {
        mat[i][j] += mat1[i][k] * mat2[k][j];
      }
    }
  }
  return mat;
}
