#include "main.h"


int main() {
    std::vector<std::vector<int> > mat1 = cmatrix(500);
    std::vector<std::vector<int> > mat2 = cmatrix(500);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int> > mat = matmul(mat1, mat2);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "N=500:" << duration << std::endl;
    mat1 = cmatrix(512);
    mat2 = cmatrix(512);
    t1 = std::chrono::high_resolution_clock::now();
    mat = matmul(mat1, mat2);
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "N=512:" << duration << std::endl;
    mat1 = cmatrix(1000);
    mat2 = cmatrix(1000);
    t1 = std::chrono::high_resolution_clock::now();
    mat = matmul(mat1, mat2);
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "N=1000:" << duration << std::endl;
    mat1 = cmatrix(1024);
    mat2 = cmatrix(1024);
    t1 = std::chrono::high_resolution_clock::now();
    mat = matmul(mat1, mat2);
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "N=1024:" << duration << std::endl;
    mat1 = cmatrix(2000);
    mat2 = cmatrix(2000);
    t1 = std::chrono::high_resolution_clock::now();
    mat = matmul(mat1, mat2);
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "N=2000:" << duration << std::endl;
    mat1 = cmatrix(2048);
    mat2 = cmatrix(2048);
    t1 = std::chrono::high_resolution_clock::now();
    mat = matmul(mat1, mat2);
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "N=2048:" << duration << std::endl;
    return 0;
}
