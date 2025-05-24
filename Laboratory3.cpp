#include "Gauss.h"
int main() {
    size_t n;
    std::cout << "Enter the size of the matrix: ";
    std::cin >> n;

    SLAU<double> system(n);

    std::cout << "Fill in the matrix:\n";
    for (size_t i = 0; i < n; ++i) {
        std::cout << "Row " << (i + 1) << ": ";
        for (size_t j = 0; j < n; ++j)
            std::cin >> system[i][j];
    }

    char choice;
    do {
        Vector<double> b(n);
        std::cout << "Enter the vector of the right parts: ";
        std::cin >> b;

        Vector<double> x = system.solve(b);
        std::cout << "Solution: " << x << "\n";

        std::cout << "Continue with another vector b? (y/n): ";
        std::cin >> choice;
    } while (tolower(choice) == 'y');

    return 0;
}

