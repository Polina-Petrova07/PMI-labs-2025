#include "gauss.h"  


int main() {
    matrix<double> A(3, 3);
    A[0][0] = 2; A[0][1] = 1; A[0][2] = -1;
    A[1][0] = -3; A[1][1] = -1; A[1][2] = 2;
    A[2][0] = -2; A[2][1] = 1; A[2][2] = 2;

    vector<double> b(3);
    b[0] = 8;
    b[1] = -11;
    b[2] = -3;

    SLU<double> solver(A, b);
    vector<double> solution = solver.get_solution();
    std::cout << A << "x:" << solution;
}