#include "gauss.h"  


int main() {
    int n;
    std::cout << "Введите размер массива:";
    std::cin >> n;
    matrix<double> A(n, n);
    vector<double> b(n);
    std::cout << "Заполните матрицу решений:\n";
    for (int i = 0; i < n; i++) {
        std::cout << "Введите строку " << i + 1 << "\n";
        for (int j = 0; j < n; j++) {
            std::cin >> A[i][j];
        }
    }
    std::cout << "Заполните вектор решений:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    SLU<double> solver(A, b);
    vector<double> solution = solver.get_solution();
    std::cout << A << "x:" << solution;
}