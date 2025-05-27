#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "SLAU.h"

int main() {
    setlocale(LC_ALL, "Ru");

    int n;
    std::cout << "Введите размер системы (n): ";
    std::cin >> n;

    SLAU system(n);
    Vector<double> rhs(n);  // правая часть уравнений

    std::cout << "Введите коэффициенты матрицы (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double value;
            std::cin >> value;
            system[i][j] = value;
        }
    }

    std::cout << "Введите правую часть (" << n << " значений):\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> rhs[i];
    }

    Vector<double> solution = system.gauss(rhs);

    std::cout << "Решение:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "x[" << i << "] = " << solution[i] << "\n";
    }

    return 0;
}
