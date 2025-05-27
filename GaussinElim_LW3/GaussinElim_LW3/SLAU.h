#pragma once
#include "Matrix.h"
#include "Vector.h"

class SLAU : public Matrix<double> {
public:

    using Matrix::Matrix; // используем конструктор базового класса

    Vector<double> gauss(Vector<double> rhs) {
        int n = getSize();

        // Прямой ход
        for (int i = 0; i < n; ++i) {
            // Выбор главного элемента по модулю в i-м столбце
            int maxRow = i;
            for (int k = i + 1; k < n; ++k) {
                if (std::abs((*this)[k][i]) > std::abs((*this)[maxRow][i])) {
                    maxRow = k;
                }
            }

            // Обмен строк
            swapRows(i, maxRow);
            rhs.swap(i, maxRow);

            double pivot = (*this)[i][i];
            if (pivot == 0.0) {
                // Проверим: вся строка — нули, а правая часть не ноль ? несовместна
                bool allZero = true;
                for (int j = 0; j < n; ++j) {
                    if ((*this)[i][j] != 0.0) {
                        allZero = false;
                        break;
                    }
                }

                if (allZero && rhs[i] != 0.0) {
                    std::cerr << "Система несовместна: строка " << i << " содержит только нули, но правая часть = " << rhs[i] << "\n";
                    exit(1);
                }
                else if (allZero && rhs[i] == 0.0) {
                    // Бесконечно много решений — строка вида 0 = 0
                    std::cerr << "Система имеет бесконечно много решений (недоопределена).\n";
                    exit(1);
                }
                else {
                    std::cerr << "Система вырождена или плохо обусловлена (pivot = 0).\n";
                    exit(1);
                }
            }

            // Нормализация строки
            for (int j = i; j < n; ++j) {
                (*this)[i][j] /= pivot;
            }
            rhs[i] /= pivot;

            // Обнуляем нижние строки
            for (int k = i + 1; k < n; ++k) {
                double factor = (*this)[k][i];
                for (int j = i; j < n; ++j) {
                    (*this)[k][j] -= factor * (*this)[i][j];
                }
                rhs[k] -= factor * rhs[i];
            }
        }

        // Обратный ход
        Vector<double> result(n);
        for (int i = n - 1; i >= 0; --i) {
            result[i] = rhs[i];
            for (int j = i + 1; j < n; ++j) {
                result[i] -= (*this)[i][j] * result[j];
            }
        }

        return result;
    }
};