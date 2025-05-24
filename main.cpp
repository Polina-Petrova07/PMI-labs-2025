#include "SLAY.h"


int main() {
    int n;
    std::cout << "Введите размер матрицы: ";
    std::cin >> n;

    Matrix<double> A(n, n);
    std::cin >> A;

    Vector<double> b(n);
    std::cin >> b;

    SLAY<double> solver(A);
    Vector<double> solution_1 = solver.solve(b);

    std::cout  << "x: "; solution_1.print();

    return 0;
}
