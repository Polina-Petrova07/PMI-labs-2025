#include "pch.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <limits>


template <typename T>
class Vector : public std::vector<T> {
public:
	using std::vector<T>::vector;

	friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
		os << "[";
		for (size_t i = 0; i < vec.size(); ++i) {
			os << std::fixed << std::setprecision(4) << vec[i];
			if (i < vec.size() - 1) {
				os << ", ";
			}
		}
		os << "]";
		return os;
	}
};

template <typename T>
class SquareMatrix {
protected:
	Vector<Vector<T>> matrix;
	size_t size;

public:
	SquareMatrix() : size(0) {}

	explicit SquareMatrix(size_t n) : size(n) {
		matrix.resize(n, Vector<T>(n, 0));
	}

	size_t getSize() const {
		return size;
	}

	Vector<T>& operator[](size_t index) {
		if (index >= size) throw std::out_of_range("Индекс строки матрицы вне диапазона");
		return matrix[index];
	}

	const Vector<T>& operator[](size_t index) const {
		if (index >= size) throw std::out_of_range("Индекс строки матрицы вне диапазона");
		return matrix[index];
	}

	void swapRows(size_t row1, size_t row2) {
		if (row1 < size && row2 < size) {
			std::swap(matrix[row1], matrix[row2]);
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const SquareMatrix<T>& mat) {
		for (size_t i = 0; i < mat.getSize(); ++i) {
			for (size_t j = 0; j < mat.getSize(); ++j) {
				os << std::setw(10) << std::fixed << std::setprecision(4) << mat[i][j];
			}
			os << std::endl;
		}
		return os;
	}
};

template <typename T>
class SLAE : public SquareMatrix<T> {
public:
	using SquareMatrix<T>::SquareMatrix;

	Vector<T> gaussMethod(Vector<T>& b) {
		if (this->size != b.size()) {
			throw std::invalid_argument("Размер вектора правой части не совпадает с размером матрицы.");
		}

		SquareMatrix<T> temp_matrix = *this;
		Vector<T> temp_b = b;
		size_t n = this->size;

		for (size_t i = 0; i < n; ++i) {
			size_t pivot_row = i;
			for (size_t k = i + 1; k < n; ++k) {
				if (std::abs(temp_matrix[k][i]) > std::abs(temp_matrix[pivot_row][i])) {
					pivot_row = k;
				}
			}

			temp_matrix.swapRows(i, pivot_row);
			std::swap(temp_b[i], temp_b[pivot_row]);

			if (std::abs(temp_matrix[i][i]) < 1e-12) {
				throw std::runtime_error("Матрица вырождена или близка к вырожденной. Решений нет или их бесконечно много.");
			}

			for (size_t k = i + 1; k < n; ++k) {
				T factor = temp_matrix[k][i] / temp_matrix[i][i];
				for (size_t j = i; j < n; ++j) {
					temp_matrix[k][j] -= factor * temp_matrix[i][j];
				}
				temp_b[k] -= factor * temp_b[i];
			}
		}

		Vector<T> solution(n);
		for (int i = n - 1; i >= 0; --i) {
			T sum = 0;
			for (size_t j = i + 1; j < n; ++j) {
				sum += temp_matrix[i][j] * solution[j];
			}
			solution[i] = (temp_b[i] - sum) / temp_matrix[i][i];
		}

		return solution;
	}
};

void read_value(double& value) {
	while (!(std::cin >> value)) {
		std::cout << "  Ошибка: Введите корректное число. Попробуйте еще раз: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

int main() {
	setlocale(LC_ALL, "Russian");

	int n;
	std::cout << "1. Введите размер квадратной матрицы: ";
	std::cin >> n;
	while (std::cin.fail() || n <= 0) {
		std::cout << "  Ошибка: Введите положительное целое число. Попробуйте еще раз: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> n;
	}

	SLAE<double> slae(n);
	Vector<double> b(n);

	std::cout << "\n2. Введите матрицу коэффициентов A:" << std::endl;
	for (int i = 0; i < n; ++i) {
		std::cout << "   Строка " << i + 1 << ": ";
		for (int j = 0; j < n; ++j) {
			read_value(slae[i][j]);
		}
	}

	std::cout << "\n3. Введите вектор свободных членов b: ";
	for (int i = 0; i < n; ++i) {
		read_value(b[i]);
	}

	std::cout << "\n--- Введенная СЛАУ ---" << std::endl;
	std::cout << "Матрица A:" << std::endl;
	std::cout << slae;
	std::cout << "Вектор b: " << b << std::endl;

	try {
		Vector<double> solution = slae.gaussMethod(b);
		std::cout << "\n--- Результат ---" << std::endl;
		std::cout << "Вектор решения x: " << solution << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "\nОшибка при решении: " << e.what() << std::endl;
	}
	return 0;
}