#ifndef HPC_HW2_H
#define HPC_HW2_H
#include "iostream"
#include "vector"
#include "chrono"

std::vector<std::vector<int>> cmatrix(int n);
std::vector<std::vector<int>>  matmul(std::vector<std::vector<int>> mat1, std::vector<std::vector<int>> mat2);
#endif
